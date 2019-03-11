#!/usr/bin/env bash

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd $DIR/..

DOCKER_IMAGE=${DOCKER_IMAGE:-wormcore/worm}
DOCKER_TAG=${DOCKER_TAG:-latest}

BUILD_DIR=${BUILD_DIR:-.}

rm docker/bin/*
mkdir docker/bin
cp $BUILD_DIR/src/wormd docker/bin/
cp $BUILD_DIR/src/worm-cli docker/bin/
cp $BUILD_DIR/src/worm-tx docker/bin/
strip docker/bin/wormd
strip docker/bin/worm-cli
strip docker/bin/worm-tx

docker build --pull -t $DOCKER_IMAGE:$DOCKER_TAG -f docker/Dockerfile docker
