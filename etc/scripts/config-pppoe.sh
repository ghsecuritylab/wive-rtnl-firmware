#!/bin/sh

###################################################
# config-pppoe.sh - configure PPPOE client helper #
###################################################

# include global config
. /etc/scripts/global.sh

# stop all pppd/xl2tpd daemons
service vpnhelper killall_vpn

LOG="logger -t vpnhelper-pppoe"

get_param() {
    eval `nvram_buf_get 2860 vpnAc vpnService vpnUser vpnPassword vpnMTU vpnMPPE vpnPeerDNS vpnDebug vpnInterface \
	    vpnAuthProtocol vpnEnableLCP vpnLCPFailure vpnLCPInterval`
    OPTFILE="/etc/ppp/options.pppoe"
}

check_param() {
    if [ "$vpnUser" = "" ] || [ "$vpnPassword" = "" ]; then
	$LOG "Username or password not set. Exit..."
	exit 1
    fi
}

load_modules() {
    if [ ! -d /sys/module/pppoe ]; then
	mod="ppp_generic pppox pppoe"
	for module in $mod
	do
    	    modprobe -q $module
	done
    fi
}

echo "==================START-PPPOE-CLIENT======================="
get_param
check_param
load_modules

if [ "$vpnInterface" = "WAN" ]; then
    vpnInterface="$wan_if"
elif [ "$vpnInterface" = "LAN" ]; then
    vpnInterface="$lan_if"
else
    vpnInterface="br0"
fi

IN_BR=`brctl show | grep $vpnInterface -c`
if [ "$vpnInterface" != "br0" ] && [ "$IN_BR" = "1" ]; then
    PPPOE_vpnInterface="br0"
    $LOG "$PPPOE_vpnInterface in bridge. Set pppoe interface to br0"
fi

if [ "$vpnAc" != "" ]; then
    vpnAc="rp_pppoe_ac $vpnAc"
else
    vpnAc=""
fi

if [ "$vpnService" != "" ]; then
    vpnService="rp_pppoe_service $vpnService"
else
    vpnService=""
fi

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
    pppoedbg="rp_pppoe_verbose 1"
else
    vpnDebug=""
    pppoedbg=""
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

# Standard PPP options we always use
PPP_STD_OPTIONS="noipdefault noauth persist $vpnPeerDNS ifname $vpn_def_if -detach $vpnDebug"
# PPPoE invocation
PPPOE_CMD="$vpnInterface $vpnAc $vpnService user $vpnUser password $vpnPassword $pppoedbg"

$LOG "Start pppd at $vpnInterface to $vpnAc $vpnService mode PPPOE"
FULLOPT="file $OPTFILE $vpnMTU $vpnMRU $vpnMPPE $PPP_STD_OPTIONS plugin /lib/rp-pppoe.so $PPPOE_CMD"
pppd $FULLOPT &
