FROM docker.io/library/alpine:3.10

ARG BUILD_MODE=build
ARG COMMANDS="chmod ln-s"

# This file is broken up to make rebuilds fast
# by reusing previous layers that take a while to run.

WORKDIR /opt/code

RUN \
       apk --no-cache update \
    && apk add build-base=0.5-r1 "bash=~5" \
    && rm -rf /tmp/* /var/cache/apk/*

COPY experiments/ experiments/
COPY Makefile Makefile.command-flags version.txt internal-docker-make.sh ./
COPY src/ src/
COPY tests/ tests/

ENV \
#    DEBUG=1 \
    BUILD_MODE=$BUILD_MODE \
    COMMANDS=$COMMANDS \
    UID1=1 \
    UID2=2 \
    GID1=1 \
    GID2=2

RUN    echo 'LIBNAME=musl' >> version.txt \
    && ./internal-docker-make.sh