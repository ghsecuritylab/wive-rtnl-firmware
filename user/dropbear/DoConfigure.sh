#!/bin/bash

echo "==================CONFIGURE-DROPBEAR==========================="
APROOTDIR=`pwd`

if [ ! -f $APROOTDIR/configure ]; then
    aclocal
    autoconf
fi
if [ ! -f $APROOTDIR/Makefile ]; then
    automake
fi

CONFOPTS="--host=mipsel-linux --disable-zlib --disable-openpty"
CONFOPTS="$CONFOPTS --disable-shadow --disable-pam"
CONFOPTS="$CONFOPTS --disable-lastlog --disable-utmp --disable-utmpx"
CONFOPTS="$CONFOPTS --disable-wtmp --disable-wtmpx --disable-loginfunc"
CONFOPTS="$CONFOPTS --disable-pututline --disable-pututxline"
CONFOPTS="$CONFOPTS --prefix=$APROOTDIR/filesystem"

./configure $CONFOPTS
