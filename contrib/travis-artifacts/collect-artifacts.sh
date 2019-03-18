#!/bin/bash -ex

if [ $# -lt 5 ] ; then
    echo "Usage: $0 basedir outdir releasedir commit host"
    exit 1
fi

BASEDIR=$1
OUTDIR=$2
RELEASEBASE=$3
COMMIT=$4
HOST=$5

RELEASEDIR=$BASEDIR/$RELEASEBASE/$COMMIT/$HOST

cd $BASEDIR/worm-$HOST

mkdir -p $RELEASEDIR
ZIPFILES=$(ls $OUTDIR/bin/* || true)

echo "make zip file"

# Linux artifacts
[ -z "$ZIPFILES" ] || \
       zip -uj $RELEASEDIR/bitcoin-$COMMIT.zip ${ZIPFILES}

echo "copy mac qt to zip file"

# MaxOSX artifacts
cp -a *.dmg $RELEASEDIR || true
echo "copy win qt to zip file"
# Windows artifacts
cp -a *.exe $RELEASEDIR || true

find $RELEASEDIR
