FROM docker.io/library/ubuntu:22.04

# This file is broken up to make rebuilds fast
# by reusing previous layers that take a while to run.

WORKDIR /opt/code

RUN \
       apt-get update \
    && apt-get -y install "build-essential=12.9ubuntu3" \
    && rm -rf /tmp/* /var/cache/apt/*

COPY *.c *.h Makefile ./

RUN make