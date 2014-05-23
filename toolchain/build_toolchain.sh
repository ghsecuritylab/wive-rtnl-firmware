#!/bin/sh

CURDIR=`pwd`

KERNELHDRS=kernel-headers
BINUTILVER=binutils-2.24
UCLIBCVER=uClibc-0.9.28
GCCVER=gcc-4.8.3

INSTALL_DEP=NO
UNPACK=YES
HEADERS=YES
BINUTILS=YES
GCC=YES
UCLIB=YES
GCCCPP=YES

export LANGUAGE=en_EN.UTF-8:en

export LC_PAPER=en_EN.UTF-8
export LC_ADDRESS=en_EN.UTF-8
export LC_MONETARY=en_EN.UTF-8
export LC_TELEPHONE=en_EN.UTF-8
export LC_IDENTIFICATION=en_EN.UTF-8
export LC_MEASUREMENT=en_EN.UTF-8
export LC_NAME=en_EN.UTF-8

export LANG=C
export LC_COLLATE=C
export LC_MESSAGES=C
export LC_ALL=C

export LC_NUMERIC=
export LC_CTYPE=
export LC_TIME=

export WCURDIR=$CURDIR/tmp
export TARGET=mipsel-linux-uclibc
export PREFIX=$CURDIR
export ROOTCURDIR=$CURDIR

export TARGET_CURDIR=$WCURDIR/$TARGET-toolchain
export KERNEL_HEADERS=$TARGET_CURDIR/include
export REALKRNINC=${PREFIX}/../linux-2.6.21.x/include
export REALLIBINC=${PREFIX}/../lib/include
export PATH="${PATH}":${PREFIX}/bin:${PREFIX}/lib:${KERNEL_HEADERS}:${REALLIBINC}:${REALKRNINC}
export CC=gcc

#install need lib`s and headers
if [ -e /etc/release ] && [ "$INSTALL_DEP" = "YES" ]; then
    ISOPENMANDRIVA=`grep OpenMandriva -i -c < /etc/release`
    ISROSA=`grep ROSA -i -c < /etc/release`
    ISMAGEIA=`grep Mageia -i -c < /etc/release`
    if [ "$ISOPENMANDRIVA" = "1" ] || [ "$ISROSA" = "1" ]; then
	urpmi --auto -a flex --download-all --allow-force
	urpmi --auto -a make --download-all --allow-force
	urpmi --auto -ay gcc --download-all --allow-force
	urpmi --auto -ay glibc --download-all --allow-force
	urpmi --auto -ay bison --download-all --allow-force
	urpmi --auto -ay libtool --download-all --allow-force
	urpmi --auto -ay libgmpxx-devel --download-all --allow-force
	urpmi --auto -ay libmpc --download-all --allow-force
	urpmi --auto -ay mpfr --download-all --allow-force
	urpmi --auto -ay gcc-gfortran --download-all --allow-force
	urpmi --auto -ay texinfo --download-all --allow-force
	urpmi --auto -ay intltool --download-all --allow-force
    elif [ "$ISMAGEIA" = "1" ]; then
	urpmi --auto bc --download-all
	urpmi --auto flex --download-all
	urpmi --auto make --download-all
	urpmi --auto gcc --download-all
	urpmi --auto glibc-devel --download-all
	urpmi --auto binutils-devel --download-all
	urpmi --auto bison --download-all
	urpmi --auto libtool-devel --download-all
	urpmi --auto autoconf --download-all
	urpmi --auto automake --download-all
	urpmi --auto libgmpxx-devel --download-all
	urpmi --auto libmpc-devel --download-all
	urpmi --auto gcc-cpp --download-all
	urpmi --auto gcc-c++ --download-all
	urpmi --auto gcc-gfortran --download-all
	urpmi --auto gcc-plugins --download-all
	urpmi --auto colorgcc --download-all
	urpmi --auto texinfo --download-all
	urpmi --auto gettext --download-all
	urpmi --auto intltool --download-all
    else
	urpmi --auto -a flex --download-all --allow-force
	urpmi --auto -a make --download-all --allow-force
	urpmi --auto -a gcc- --download-all --allow-force
	urpmi --auto -a glibc- --download-all --allow-force
	urpmi --auto -a bison- --download-all --allow-force
	urpmi --auto -a libtool- --download-all --allow-force
	urpmi --auto -a libgmpxx-devel --download-all --allow-force
	urpmi --auto -a libmpc- --download-all --allow-force
	urpmi --auto -a mpfr- --download-all --allow-force
	urpmi --auto -a gcc-gfortran --download-all --allow-force
	urpmi --auto -a texinfo- --download-all --allow-force
	urpmi --auto -a intltool- --download-all --allow-force
    fi
fi

mkdir -p $WCURDIR

cd $WCURDIR
mkdir -p ${TARGET}-toolchain  && cd ${TARGET}-toolchain

##################################TUNE FOR CURRENT VERSION GCC BUILD####################################
HOSTGCCVER=`gcc -dumpversion | cut -f -2 -d .`
if [ "$HOSTGCCVER" = "4.5" ] || [ "$HOSTGCCVER" = "4.6" ] || [ "$HOSTGCCVER" = "4.7" ] || [ "$HOSTGCCVER" = "4.8" ]; then
    WARN_OPTS="-Wno-pointer-sign -Wno-unused-but-set-variable -Wno-trigraphs -Wno-format-security -Wno-long-long -Wno-sizeof-pointer-memaccess"
fi

export CFLAGS="-O2 $WARN_OPTS"

EXT_OPT="$EXT_OPT --disable-lto --enable-ld=yes --enable-gold=no --disable-sanity-checks --disable-werror"
if [ "$GCCVER" = "gcc-4.6.4" ] || [ "$GCCVER" = "gcc-4.7.4" ] || [ "$GCCVER" = "gcc-4.8.3" ]; then
    EXT_OPT="$EXT_OPT --disable-biendian --disable-softfloat --disable-libquadmath --disable-libquadmath-support"
fi
if [ "$GCCVER" = "gcc-4.8.3" ]; then
    EXT_OPT="$EXT_OPT --disable-libatomic --with-pic"
fi
#########################################################################################################

if [ "$UNPACK" = "YES" ]; then
    echo "=================REMOVE-OLD-BUILD-TREE=================="
    rm -rf build-*
    rm -rf $CURDIR/bin
    rm -rf $CURDIR/lib
    rm -rf $CURDIR/usr
    rm -rf $CURDIR/share
    rm -rf $CURDIR/libexec
    rm -rf $CURDIR/include
    rm -rf $CURDIR/mipsel-linux-uclibc
fi

if [ "$UNPACK" = "YES" ]; then
    echo "=================EXTRACT-KERNEL-HEADERS================="
    tar xjf $KERNELHDRS.tar.bz2
    echo "====================EXTRACT-BINUTILS===================="
    tar xjf $BINUTILVER.tar.bz2
    echo "=====================EXTRACT-UCLIBC====================="
    tar xjf $UCLIBCVER.tar.bz2
    echo "=======================EXTRACT-GCC======================"
    tar xjf $GCCVER.tar.bz2
fi

if [ "$HEADERS" = "YES" ]; then
    echo "=====================INSTALL-C-HEADERS===================="
    mkdir -p $CURDIR/usr
    rm -rf $CURDIR/usr/include
    cp -rf $KERNEL_HEADERS $CURDIR/usr
    ln -sf $CURDIR/usr/include $CURDIR/include
fi

if [ "$BINUTILS" = "YES" ]; then
    echo "=====================BUILD-BINUTILS====================="
    mkdir -p build-binutils && cd build-binutils
    (../$BINUTILVER/configure --target=$TARGET --prefix=$PREFIX --includedir=$KERNEL_HEADERS \
	--with-sysroot=$PREFIX --with-build-sysroot=$PREFIX \
	--disable-gold --disable-libquadmath --disable-libquadmath-support --disable-lto --disable-werror && \
    make -j4 KERNEL_HEADERS=$KERNEL_HEADERS && \
    make install) || exit 1
    cd ..
fi

if [ "$GCC" = "YES" ]; then
    echo "=====================BUILD-GCC-C========================"
    mkdir -p build-gcc-bootstrap && cd build-gcc-bootstrap
    (../$GCCVER/configure \
	--target=$TARGET --prefix=$PREFIX --includedir=$KERNEL_HEADERS \
	--with-gnu-ld --with-gnu-as \
	--disable-shared \
	--disable-tls --disable-libmudflap --disable-libssp \
	--disable-libgomp --disable-threads \
	--with-sysroot=$PREFIX \
	--enable-version-specific-runtime-libs --enable-languages=c \
	$EXT_OPT && \
    make -j4 && \
    make install) || exit 1
    cd ..
fi

if [ "$UCLIB" = "YES" ]; then
    echo "=====================BUILD-C-UCLIBC===================="
    cp -fv uclibc-config $UCLIBCVER/.config
    cd $UCLIBCVER
    (make oldconfig ROOTDIR="$CURDIR" && \
    make -j4 ROOTDIR="$CURDIR" && \
    make install) || exit 1
    cd ..
fi

if [ "$GCCCPP" = "YES" ]; then
    echo "====================BUILD-GCC-CPP======================="
    mkdir -p build-gcc-bootstrap-cpp && cd build-gcc-bootstrap-cpp
    (../$GCCVER/configure \
	--target=$TARGET --prefix=$PREFIX --includedir=$KERNEL_HEADERS \
	--with-gnu-ld --with-gnu-as \
	--disable-tls --disable-libmudflap --disable-libssp \
	--disable-libgomp --disable-threads \
	--with-sysroot=$PREFIX \
	--enable-version-specific-runtime-libs --enable-languages=c++ \
	$EXT_OPT && \
    make -j4 all-host all-target-libgcc all-target-libstdc++-v3  && \
    make install-host install-target-libgcc install-target-libstdc++-v3) || exit 1
    cd ..
fi

echo "====================All IS DONE!========================"
