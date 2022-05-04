FROM docker.io/library/alpine:3.10

# This file is broken up to make rebuilds fast
# by reusing previous layers that take a while to run.

WORKDIR /opt/code

RUN \
       apk --no-cache update \
    && apk add build-base=0.5-r1 curl tar xz \
    && mkdir -p /opt/dietlibc \
    && curl -o /tmp/dietlibc.tar.xz https://www.fefe.de/dietlibc/dietlibc-0.34.tar.xz \
    && xz -d /tmp/dietlibc.tar.xz \
    && tar xf /tmp/dietlibc.tar -C /opt/dietlibc/ --strip 1 \
    && ( cd /opt/dietlibc && make && install bin-x86_64/diet /usr/local/bin ) \
    && rm -rf /tmp/* /var/cache/apk/*

COPY *.c *.h Makefile ./

RUN CC="diet cc" make