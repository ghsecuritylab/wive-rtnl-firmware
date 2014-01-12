#############################################################################################################
# Qos helper script for Wive-NG-RTNL									    #
#############################################################################################################

# include global
. /etc/scripts/global.sh

LOG="logger -t Complex QoS"

# get config
eval `nvram_buf_get 2860 lan_ipaddr vpnPurePPPOE igmpEnabled \
    QoS_rate_down QoS_rate_limit_down QoS_rate_up QoS_rate_limit_up \
    QoS_rate_vpn_up QoS_rate_vpn_limit_up`

# get users prio ports
QoS_high_pp=`nvram_get 2860 QoS_high_pp | awk '{ gsub(" ",","); print }'`
QoS_low_pp=`nvram_get 2860 QoS_low_pp | awk '{ gsub(" ",","); print }'`

IPTSCR="/etc/qos_firewall"
INCOMING="iptables -A shaper_pre -t mangle"
OUTGOING="iptables -A shaper_post -t mangle"

qos_lm() {
    # Load modules
    if [ ! -d /sys/modules/sch_esfq ]; then
	modprobe -q sch_esfq
    fi
    if [ ! -d /sys/modules/sch_sfq ]; then
	modprobe -q sch_sfq
    fi
    if [ ! -d /sys/modules/xt_mark ]; then
	modprobe -q xt_mark
    fi
    if [ ! -d /sys/modules/xt_MARK ]; then
	modprobe -q xt_MARK
    fi
    if [ ! -d /sys/modules/xt_length ]; then
	modprobe -q xt_length
    fi
}

qos_nf() {
    ##################################################################################################################################
    # BUILD CHAINS
    ##################################################################################################################################
    $LOG "Generate $IPTSCR"
    echo "$LOG add qos netfilter rules" >> $IPTSCR
    echo "iptables -N shaper_pre -t mangle > /dev/null 2>&1" >> $IPTSCR
    echo "iptables -F shaper_pre -t mangle > /dev/null 2>&1" >> $IPTSCR
    echo "iptables -N shaper_post -t mangle > /dev/null 2>&1" >> $IPTSCR
    echo "iptables -F shaper_post -t mangle > /dev/null 2>&1" >> $IPTSCR
    echo "iptables -A PREROUTING -t mangle ! -d 224.0.0.0/4 -j shaper_pre > /dev/null 2>&1" >> $IPTSCR
    echo "iptables -A POSTROUTING -t mangle ! -s 224.0.0.0/4 -j shaper_post > /dev/null 2>&1" >> $IPTSCR
}

qos_nf_if() {
    ##################################################################################################################################
    # SET MARKERS
    ##################################################################################################################################
    # first always high prio ports
    echo "$INCOMING -i $wan_if -p tcp --dport 0:1024 -j MARK --set-mark 20" >> $IPTSCR
    echo "$INCOMING -i $wan_if -p tcp --sport 0:1024 -j MARK --set-mark 20" >> $IPTSCR
    echo "$INCOMING -i $wan_if -p udp --dport 0:1024 -j MARK --set-mark 21" >> $IPTSCR
    echo "$INCOMING -i $wan_if -p udp --sport 0:1024 -j MARK --set-mark 21" >> $IPTSCR
    echo "$INCOMING -i $wan_if -p tcp --syn -j MARK --set-mark 20" >> $IPTSCR
    echo "$INCOMING -i $wan_if -p icmp -m mark --mark 0 -j MARK --set-mark 20" >> $IPTSCR
    echo "$INCOMING -i $wan_if -p tcp -m length --length :64 -j MARK --set-mark 20" >> $IPTSCR

    # second user high prio ports
    if [ "$QoS_high_pp" != "" ]; then
	echo "$INCOMING -i $wan_if -p tcp -m multiport --dport $QoS_high_pp -j MARK --set-mark 20" >> $IPTSCR
	echo "$INCOMING -i $wan_if -p udp -m multiport --dport $QoS_high_pp -j MARK --set-mark 20" >> $IPTSCR
    fi
    if [ "$QoS_low_pp" != "" ]; then
	echo "$INCOMING -i $wan_if -p tcp -m multiport --dport $QoS_low_pp  -j MARK --set-mark 21" >> $IPTSCR
	echo "$INCOMING -i $wan_if -p udp -m multiport --dport $QoS_low_pp  -j MARK --set-mark 21" >> $IPTSCR
    fi

    # all others set as low prio
    echo "$INCOMING -i $wan_if -p tcp -m mark --mark 0 -j MARK --set-mark 22" >> $IPTSCR
    echo "$INCOMING -i $wan_if -p udp -m mark --mark 0 -j MARK --set-mark 22" >> $IPTSCR

    # first always high prio ports
    echo "$OUTGOING -o $wan_if -p tcp --dport 0:1024 -j MARK --set-mark 23" >> $IPTSCR
    echo "$OUTGOING -o $wan_if -p udp --dport 0:1024 -j MARK --set-mark 23" >> $IPTSCR
    echo "$OUTGOING -o $wan_if -p tcp --sport 0:1024 -j MARK --set-mark 23" >> $IPTSCR
    echo "$OUTGOING -o $wan_if -p udp --sport 0:1024 -j MARK --set-mark 23" >> $IPTSCR
    echo "$OUTGOING -o $wan_if -p icmp -m mark --mark 0 -j MARK --set-mark 23" >> $IPTSCR
    echo "$OUTGOING -o $wan_if -p tcp -m length --length :64 -j MARK --set-mark 23" >> $IPTSCR

    # second user high prio ports
    if [ "$QoS_high_pp" != "" ]; then
	echo "$OUTGOING -o $wan_if -p tcp -m multiport --dport $QoS_high_pp -j MARK --set-mark 23" >> $IPTSCR
	echo "$OUTGOING -o $wan_if -p udp -m multiport --dport $QoS_high_pp -j MARK --set-mark 23" >> $IPTSCR
    fi
    if [ "$QoS_low_pp" != "" ]; then
	echo "$OUTGOING -o $wan_if -p tcp -m multiport --dport $QoS_low_pp -j MARK --set-mark 24" >> $IPTSCR
	echo "$OUTGOING -o $wan_if -p udp -m multiport --dport $QoS_low_pp -j MARK --set-mark 24" >> $IPTSCR
    fi

    # all others set as low prio
    echo "$OUTGOING -o $wan_if -p tcp -m mark --mark 0 -j MARK --set-mark 24" >> $IPTSCR
    echo "$OUTGOING -o $wan_if -p udp -m mark --mark 0 -j MARK --set-mark 24" >> $IPTSCR
}

qos_tc_lan() {
    ##################################################################################################################################
    # FROM UPLINK TO LAN. BIND AT LAN_IF
    ##################################################################################################################################
    $LOG "All incoming $lan_if rate: normal $QoS_rate_limit_down , maximum $QoS_rate_down (kbit/s)"
    tc qdisc add dev $lan_if root handle 1: htb default 22
    tc class add dev $lan_if parent 1:  classid 1:1 htb rate 90mbit quantum 1500 burst 500k
    tc class add dev $lan_if parent 1:1 classid 1:2 htb rate ${QoS_rate_down}kbit quantum 1500 burst 100k
    tc class add dev $lan_if parent 1:1 classid 1:3 htb rate 80 ceil 90mbit prio 0 quantum 1500 burst 100k

    tc class add dev $lan_if parent 1:2 classid 1:20 htb rate ${QoS_rate_limit_down}kbit ceil ${QoS_rate_down}kbit prio 1 quantum 1500
    tc class add dev $lan_if parent 1:2 classid 1:21 htb rate ${QoS_rate_limit_down}kbit ceil ${QoS_rate_down}kbit prio 2 quantum 1500
    tc class add dev $lan_if parent 1:2 classid 1:22 htb rate ${QoS_rate_limit_down}kbit ceil ${QoS_rate_down}kbit prio 3 quantum 1500

    tc qdisc add dev $lan_if parent 1:3 handle 3: esfq perturb 10 hash dst quantum 1500
    tc qdisc add dev $lan_if parent 1:20 handle 20: esfq perturb 10 hash dst quantum 1500
    tc qdisc add dev $lan_if parent 1:21 handle 21: esfq perturb 10 hash dst quantum 1500
    tc qdisc add dev $lan_if parent 1:22 handle 22: esfq perturb 10 hash dst quantum 1500

    # filters for marked in prerouting
    tc filter add dev $lan_if parent 1:0 prio 1 protocol ip handle 20 fw flowid 1:20
    tc filter add dev $lan_if parent 1:0 prio 2 protocol ip handle 21 fw flowid 1:21
    tc filter add dev $lan_if parent 1:0 prio 3 protocol ip handle 22 fw flowid 1:22

    # local connections to router must be overheaded
    tc filter add dev $lan_if parent 1:0 protocol ip prio 0 u32 match ip src $lan_ipaddr flowid 1:3
    if [ "$igmpEnabled" != "0" ]; then
	# mcast network to
	tc filter add dev $lan_if parent 1:0 protocol ip prio 0 u32 match ip src $mcast_net flowid 1:3
    fi
}

gos_tc_wan() {
    ##################################################################################################################################
    # FROM LAN TO UPLINK. BIND AT WAN_IF
    ##################################################################################################################################
    $LOG "All outgoing $wan_if rate: normal $QoS_rate_limit_up , maximum $QoS_rate_up (kbit/s)"
    tc qdisc add dev $wan_if root handle 1: htb default 24
    tc class add dev $wan_if parent 1:  classid 1:1 htb rate ${QoS_rate_up}kbit quantum 1500 burst 50k

    tc class add dev $wan_if parent 1:1 classid 1:23 htb rate ${QoS_rate_limit_up}kbit ceil ${QoS_rate_up}kbit prio 0 quantum 1500
    tc class add dev $wan_if parent 1:1 classid 1:24 htb rate ${QoS_rate_limit_up}kbit ceil ${QoS_rate_up}kbit prio 1 quantum 1500

    tc qdisc add dev $wan_if parent 1:23 handle 23: sfq perturb 10 quantum 1500
    tc qdisc add dev $wan_if parent 1:24 handle 24: sfq perturb 10 quantum 1500

    tc filter add dev $wan_if parent 1:0 prio 0 protocol ip handle 23 fw flowid 1:23
    tc filter add dev $wan_if parent 1:0 prio 1 protocol ip handle 24 fw flowid 1:24
}

# tune netdev
qos_lm
# create target
qos_nf
# add netsched rules
qos_tc_lan

if [ "$vpnPurePPPOE" != "1" ]; then
    # add rules for target
    qos_nf_if
    gos_tc_wan
fi

# add rules for vpn wan to
if [ "$vpnEnabled" = "on" ] && [ "$vpnPurePPPOE" != "1" ] && [ "$wan_if" != "$real_wan_if" ]; then
    wan_if="$real_wan_if"
    QoS_rate_up="$QoS_rate_vpn_up"
    QoS_rate_limit_up="$QoS_rate_vpn_limit_up"
    qos_nf_if
    gos_tc_wan
fi
