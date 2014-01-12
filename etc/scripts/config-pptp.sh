#!/bin/sh

#################################################
# config-pptp.sh - configure PPTP client helper #
#################################################

# include global
. /etc/scripts/global.sh

# stop all pppd/xl2tpd daemons
service vpnhelper killall_vpn

LOG="logger -t vpnhelper-pptp"

get_param() {
    eval `nvram_buf_get 2860 vpnServer vpnUser vpnPassword vpnMTU vpnMPPE vpnPeerDNS vpnDebug vpnAuthProtocol vpnEnableLCP \
	    vpnLCPFailure vpnLCPInterval vpnTestReachable wan_gateway`
    OPTFILE="/etc/ppp/options.pptp"
}

check_param() {
    if [ "$vpnServer" = "" ] || [ "$vpnUser" = "" ] || [ "$vpnPassword" = "" ]; then
	$LOG "Server adress, username or password not set. Exit..."
	exit 1
    fi
}

get_vpn_ip() {
    ##############################################
    # Check $vpnServer variable for ip/name set
    ##############################################
    is_ip=`ipcalc -sn $vpnServer`
    if [ "$is_ip" = "" ]; then
	##########################################
	##########TRY RESOLV SERVER IP############
	##########################################
	$LOG "Get vpn server $vpnServer ip adress"
	count=0
	resolved=0
	while [ $resolved -eq 0 ]; do
	    NS=`ipget $vpnServer | tail -q -n1`
	    if [ "$NS" != "" ]; then
		resolved=1
		SERVER="$NS"
	    fi
	    if [ "$count" = "10" ]; then
		resolved=1
    		SERVER="$vpnServer"
    		$LOG "Not resolve adress for $SERVER"
	    fi
	    usleep 500000
	    count="$(($count+1))"
	done
    else
	SERVER="$vpnServer"
    fi

    $LOG "Server adress is $SERVER"

    # always create /tmp/vpnip
    # fix if server string = IP
    echo "$SERVER" > /tmp/vpnip
}

load_modules() {
    if [ ! -d /sys/module/pptp ]; then
	mod="ppp_generic pppox pptp"
	for module in $mod
	do
	    modprobe -q $module
	done
    fi
}

echo "==================START-PPTP-CLIENT======================="
    get_param
    check_param
    get_vpn_ip
    reachable=0

    $LOG "Set route to vpn server."
    if [ "$wanConnectionMode" != "STATIC" ]; then
	if [ -f /tmp/default.gw ]; then
	    newdgw=`cat /tmp/default.gw`
	else
	    newdgw=""
	fi
    else
	newdgw="$wan_gateway"
	if [ "$newdgw" = "0.0.0.0" ]; then
	    newdgw=""
	fi
    fi

    if [ "$newdgw" != "" ] && [ "$newdgw" != "$SERVER" ]; then
	dgw_net=`ipcalc "$newdgw" -sn | cut -f 2- -d =`
	srv_net=`ipcalc "$SERVER" -sn | cut -f 2- -d =`
	if [ "$dgw_net" != "" ] && [ "$srv_net" != "" ] && [ "$dgw_net" != "$srv_net" ]; then
	    $LOG "Add route to $SERVER via $newdgw"
	    ip route replace $SERVER via $newdgw
	fi
    fi

    if [ "$vpnTestReachable" = "1" ]; then
	while [ $reachable -eq 0 ]; do
	    $LOG "Check for PPTP server $SERVER reachable"
    	    ping -q -c 1 $SERVER
    	    if [ "$?" -eq 0 ]; then
        	reachable=1
    	    else
    		$LOG "Server unreachable wait 30 sec."
        	sleep 30
		get_vpn_ip
        	reachable=0
    	    fi
        done
    fi

    # load ppp* modules
    load_modules

    if [ "$vpnPeerDNS" = "on" ]; then
	vpnPeerDNS=usepeerdns
    else
	vpnPeerDNS=
    fi

    if [ "$vpnMPPE" = "on" ]; then
	mod="crypto_algapi cryptomgr blkcipher ppp_mppe"
	for module in $mod
	do
	    modprobe -q $module
	done
        vpnMPPE="require-mppe-128"
    else
        vpnMPPE=""
    fi

    if [ "$vpnMTU" = "" ] || [ "$vpnMTU" = "AUTO" ]; then
        vpnMTU=""
        vpnMRU=""
    else
        vpnMRU="mru $vpnMTU"
        vpnMTU="mtu $vpnMTU"
    fi

    if [ "$vpnDebug" = "on" ]; then
        vpnDebug="debug"
    else
	vpnDebug=""
    fi

    if [ "$vpnAuthProtocol" = "1" ]; then
	PAP="require-pap"
	CHAP="refuse-chap"
	EAP="refuse-eap"
	MSCHAP="refuse-mschap"
	MSCHAP2="refuse-mschap-v2"
    elif [ "$vpnAuthProtocol" = "2" ]; then
	PAP="refuse-pap"
	CHAP="require-chap"
	EAP="refuse-eap"
	MSCHAP="refuse-mschap"
	MSCHAP2="refuse-mschap-v2"
    elif [ "$vpnAuthProtocol" = "3" ]; then
	PAP="refuse-pap"
	CHAP="refuse-chap"
	EAP="refuse-eap"
	MSCHAP="refuse-mschap"
	MSCHAP2="require-mschap-v2"
    else
	PAP=""
	CHAP=""
	EAP=""
	MSCHAP=""
	MSCHAP2=""
    fi

    if [ "$vpnEnableLCP" = "on" ]; then
        vpnEnableLCP="lcp-echo-adaptive"
    else
	vpnEnableLCP=""
    fi

    if [ "$vpnLCPFailure" = "" ] || [ "$vpnLCPInterval" = "" ]; then
	vpnLCPFailure=5
	vpnLCPInterval=30
    fi

    printf "
    lcp-echo-failure  $vpnLCPFailure
    lcp-echo-interval $vpnLCPInterval
    $vpnEnableLCP
    $PAP
    $CHAP
    $EAP
    $MSCHAP
    $MSCHAP2
    " > $OPTFILE

    $LOG "PPTP connect to $SERVER ....."
    PPPDOPT="file $OPTFILE ifname $vpn_def_if -detach noipdefault noauth persist $vpnPeerDNS $vpnDebug $vpnMTU $vpnMRU $vpnMPPE plugin"
    PLUGOPT="/lib/libpptp.so pptp_server $SERVER user $vpnUser password $vpnPassword"
    FULLOPT="$PPPDOPT $PLUGOPT"
    pppd $FULLOPT &
