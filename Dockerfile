FROM ubuntu:22.04 as compiler

# https://mxe.cc/#requirements-debian
RUN apt-get update && apt-get install -y \
    autoconf \
    automake \
    autopoint \
    bash \
    bison \
    bzip2 \
    flex \
    g++ \
    g++-multilib \
    gettext \
    git \
    gperf \
    intltool \
    libc6-dev-i386 \
    libgdk-pixbuf2.0-dev \
    libltdl-dev \
    libssl-dev \
    libtool-bin \
    libxml-parser-perl \
    lzip \
    make \
    openssl \
    p7zip-full \
    patch \
    perl \
    python3 \
    python3-mako \
    ruby \
    sed \
    unzip \
    wget \
    xz-utils

# Fix python not found with symlink
RUN ln -s /usr/bin/python3 /usr/bin/python

# Build MXE from source
RUN git clone --depth 1 https://github.com/mxe/mxe.git /opt/mxe

WORKDIR /opt/mxe

ARG jobs=12

# Cache download
RUN make download-cmake download-qtbase --jobs=$jobs 
    
# Build
RUN make cmake --jobs=$jobs MXE_TARGETS="x86_64-w64-mingw32.static x86_64-w64-mingw32.shared"
RUN make qtbase --jobs=$jobs MXE_TARGETS="x86_64-w64-mingw32.static x86_64-w64-mingw32.shared"

# Clean out junk
RUN cd /opt/mxe && \
    make clean-junk && \
    rm -rf "/opt/mxe/pkg/*"

# Set environment variables to use MXE binaries
ENV PATH="/opt/mxe/usr/bin:${PATH}"

