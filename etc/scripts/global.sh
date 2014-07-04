#!/bin/sh

############################################################
# global.sh - correct enviroment helper for automatization #
############################################################

# include kernel config
. /etc/scripts/config.sh

# include profile variables
. /etc/profile

# set default variables
wan_if="eth2.2"
real_wan_if="eth2.2"
lan_if="br0"
lan2_if="br0:9"
vpn_if="ppp0"
vpn_def_if="ppp0"

# phys names
phys_lan_if="eth2.1"
phys_wan_if="eth2.2"

# set some constatns
mcast_net="224.0.0.0/4"
upmpm_net="239.0.0.0/8"
txqueuelen="1000"

# first get operation mode and wan mode  dns mode and relay mode vpn mode and type
eval `nvram_buf_get 2860 OperationMode wanConnectionMode wan_ipaddr wan_static_dns \
	WLAN_MAC_ADDR WLAN2_MAC_ADDR WAN_MAC_ADDR LAN_MAC_ADDR \
	dnsPEnabled UDPXYMode UDPXYPort igmpEnabled \
	vpnEnabled vpnPurePPPOE vpnType vpnDGW \
	radvdEnabled ipv6_mode \
	ApCliBridgeOnly \
	MODEMENABLED \
	QoSEnable simple_qos`

# name/mask for first wlanmodule used in system logic
getFirstWlanIfName() {
    if [ "$CONFIG_RT2860V2_AP" != "" ]; then
	first_wlan_root_if="ra0"			# is first root interface name
	first_wlan="ra"					# this is mask name vifs for first wlan module
	if [ "$CONFIG_RT2860V2_AP_MBSS" != "" ]; then
	    first_wlan_mbss="ra"			# this is mask name vifs for first mbss wlan module
	fi
	if [ "$CONFIG_RT2860V2_AP_APCLI" != "" ]; then
	    first_wlan_apcli="apcli0"			# this is name vif for first acli wlan module
	fi
	if [ "$CONFIG_RT2860V2_AP_WDS" != "" ]; then
	    first_wlan_wds="wds"			# this is mask name vifs for first wds wlan module
	fi
	if [ "$CONFIG_RT2860V2_STA_MESH" != "" ] || [ "$CONFIG_RT2860V2_AP_MESH" != "" ]; then
	    first_wlan_mesh="mesh0"			# this is name vif for first mesh wlan module
	fi
    fi
}

# this if flag say second physical wlan module exist
# and name/mask for second wlanmodule used in system logic
getSecWlanIfName() {
    if [ "$CONFIG_RT3090_AP" != "" ]; then
	second_wlan_root_if="rai0"			# is root interface name
	second_wlan="rai"				# this is mask name vifs for second wlan module
	if [ "$CONFIG_RT3090_AP_MBSS" != "" ]; then
	    second_wlan_mbss="rai"			# this is mask name vifs for second mbss wlan module
	fi
	if [ "$CONFIG_RT3090_AP_APCLI" != "" ]; then
	    second_wlan_apcli="apclii0"			# this is name vif for first acli wlan module
	fi
	if [ "$CONFIG_RT3090_AP_WDS" != "" ]; then
	    second_wlan_wds="wdsi"			# this is mask name vifs for second wds wlan module
	fi
    fi
}

# LAN interface name -> $lan_if
getLanIfName() {
    # phys port names
    if [ "$CONFIG_RT_3052_ESW" = "y" ]; then
	# internal switch support
	phys_lan_if="eth2.1"
    elif [ "$CONFIG_RAETH_GMAC2" = "y" ]; then
	# external switch support
	phys_lan_if="eth2"
    else
	# this is stub
	# support only switched devices
	phys_lan_if="eth2.1"
    fi
    # logical names
    if [ "$OperationMode" = "2" ]; then
	lan_if="eth2"
	lan2_if="eth2:9"
    else
	lan_if="br0"
	lan2_if="br0:9"
    fi
}

# VPN interface name -> $vpn_if
getVpnIfName() {
    if [ -f /tmp/vpn_if_name ]; then
	if_tmp=`grep -v "^$" < /tmp/vpn_if_name`
	if [ "$if_tmp" != "" ]; then
	    vpn_if="$if_tmp"
	fi
    fi
}

# WAN interface name -> $wan_if
getWanIfName() {
    # phys wan name
    if [ "$CONFIG_RT_3052_ESW" != "" ] || [ "$CONFIG_RAETH_ROUTER" != "" ]; then
	# internal switch support
	phys_wan_if="eth2.2"
    elif [ "$CONFIG_MAC_TO_MAC_MODE" != "" ] && [ "$CONFIG_RAETH_GMAC2" = "" ]; then
	# external one phy switch support
	phys_wan_if="eth2.2"
    elif [ "$CONFIG_MAC_TO_MAC_MODE" != "" ] && [ "$CONFIG_RAETH_GMAC2" != "" ]; then
	# external dual phy switch support
	phys_wan_if="eth3"
    else
	# this is stub support only switched devices !!!
	phys_wan_if="eth2.2"
    fi
    # real wan name
    if [ "$OperationMode" = "0" ] || [ "$ApCliBridgeOnly" = "1" ]; then
	wan_if="br0"
    elif [ "$OperationMode" = "1" ] || [ "$OperationMode" = "4" ]; then
	wan_if="$phys_wan_if"
    elif [ "$OperationMode" = "2" ]; then
	wan_if="$first_wlan_root_if"
    elif [ "$OperationMode" = "3" ]; then
	if [ "$first_wlan_apcli" != "" ]; then
	    wan_if="$first_wlan_apcli"
	elif [ "$second_wlan_apcli" != "" ]; then
	    wan_if="$second_wlan_apcli"
	else
	    echo "Driver not support APCLI mode."
	    wan_if="$phys_wan_if"
	fi
    elif [ "$OperationMode" = "4" ]; then
	    wan_if="$phys_wan_if"
    fi
    # services wan name
    if [ "$vpnEnabled" = "on" -a  "$vpnDGW" = "1" ] || [ "$MODEMENABLED" = "1" ]; then
	get_ppp_wan_if=`ls /proc/sys/net/ipv4/conf/ | grep ppp | tail -q -n1`
	if [ "$get_ppp_wan_if" != "" ]; then
    	    real_wan_if="$get_ppp_wan_if"
	else
    	    real_wan_if="$vpn_if"
	fi
    else
        real_wan_if="$wan_if"
    fi
}

getTunIfName() {
    if [ "$ipv6_mode" = "6RD" ]; then
	tunif="tun6to4"
    elif [ "$ipv6_mode" = "6TO4" ]; then
	tunif="sit0"
    elif [ "$ipv6_mode" = "NATIVE" ]; then
	tunif="$real_wan_if"
    fi
}

getWanIpaddr() {
    # always return physical wan ip
    if [ "$wanConnectionMode" != "STATIC" ] || [ "$wan_ipaddr" = "" ]; then
	wan_ipaddr=`ip -4 addr show dev $wan_if | awk '/inet / {print $2}' | cut -f1 -d"/"` > /dev/null 2>&1
    fi

    # return vpn or physical wan ip
    real_wan_ipaddr=`ip -4 addr show dev $real_wan_if | awk '/inet / {print $2}' | cut -f1 -d"/"` > /dev/null 2>&1
    if [ "$real_wan_ipaddr" = "" ]; then
	real_wan_ipaddr="$wan_ipaddr"
    fi

}

# reconnect to AP
wifi_reconnect() {
    if [ "$OperationMode" = "2" ]; then
	staCur_SSID=`nvram_get 2860 staCur_SSID`
	if [ "$staCur_SSID" != "" ]; then
	    # Reconnect to STA
	    iwpriv $first_wlan_root_if set SSID="$staCur_SSID"
	    usleep 500000
	fi
    elif [ "$OperationMode" = "3" ]; then
	# Reenable apcli for reconnect
	iwpriv $first_wlan_apcli set ApCliEnable=0
        usleep 100000
	iwpriv $first_wlan_apcli set ApCliEnable=1
	usleep 500000
    fi
}

# wait connect to AP
wait_connect() {
    if [ "$OperationMode" = "2" ]; then
	# Get connection status
	connected=`iwpriv $first_wlan_root_if connStatus | grep Connected -c`
	if [ "$connected" = "0" ] || [ ! -f /tmp/sta_connected ]; then
	    exit 1
	fi
    elif [ "$OperationMode" = "3" ] && [ "$ApCliBridgeOnly" != "1" ]; then
	# Get connection status
	notconnected=`iwconfig $first_wlan_apcli | grep -c "Not-Associated"`
	if [ "$noconnected" = "1" ]; then
	    exit 1
	fi
    fi
}

# conntrack and route table/caches flush
flush_net_caches() {
    ip route flush cache > /dev/null 2>&1
    echo 1 > /proc/sys/net/nf_conntrack_table_flush
}

# flush arp cache in switch
flush_arp_cache() {
    if [ -e /bin/switch ]; then
	switch clear > /dev/null 2>&1
    fi
}

delif_from_br() {
    ip addr flush dev $1 > /dev/null 2>&1
    if [ -d /proc/sys/net/ipv6 ]; then
        ip -6 addr flush dev $1 > /dev/null 2>&1
    fi
    ip link set $1 down > /dev/null 2>&1
    brctl delif br0 $1 > /dev/null 2>&1
}

readdif_to_br() {
    delif_from_br $1
    brctl addif br0 $1
    ip link set $1 up
}

# get params
getFirstWlanIfName
getSecWlanIfName
getLanIfName
getWanIfName
getVpnIfName
getTunIfName
getWanIpaddr
