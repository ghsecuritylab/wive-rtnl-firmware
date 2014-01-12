#!/bin/bash

echo "=====================CONFIGURE-LIBCURL===================="
APROOTDIR=`pwd`
LIBDIR=$FIRMROOT/lib
BACKUPCFLAGS=$CFLAGS
BACKUPLDFLAGS=$LDFLAGS
ZLIB=$LIBDIR/include_shared
LIBSSL=$FIRMROOT/user/openssl

if [ ! -f $APROOTDIR/configure ]; then
    aclocal
    autoconf
    autoreconf
fi
if [ ! -f $APROOTDIR/Makefile.in ]; then
    automake
fi

CONFOPTS="--host=mipsel-linux --build=i686-pc-linux-gnu --without-random"
CONFOPTS="$CONFOPTS --without-ssl --disable-debug --disable-curldebug --disable-manual"
CONFOPTS="$CONFOPTS --disable-dependency-tracking --disable-verbose --disable-rtsp"
CONFOPTS="$CONFOPTS --prefix=$APROOTDIR/filesystem"
CFLAGS="-Os"
CPPFLAGS="$BACKUPCFLAGS -I$ZLIB -I$LIBSSL"
LDFLAGS="$BACKUPLDFLAGS -L$ZLIB -L$LIBSSL"

export CFLAGS LDFLAGS CPPFLAGS
./configure $CONFOPTS
