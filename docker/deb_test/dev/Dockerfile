FROM ubuntu
LABEL maintainer="matus.chochlik@proton.me"

ARG DEBIAN_FRONTEND=noninteractive
RUN apt-get --yes update
RUN apt-get --yes upgrade
RUN apt-get --yes install pkgconf cmake make g++

RUN mkdir -p /tmp/eagine
COPY eagine-core-dev.deb eagine-shapes-dev.deb eagine-oglplus-dev.deb /tmp/
COPY entrypoint /tmp/eagine
COPY CMakeLists.txt /tmp/eagine
COPY example/* /tmp/eagine/example/


WORKDIR /tmp/eagine
ENTRYPOINT /bin/sh /tmp/eagine/entrypoint
