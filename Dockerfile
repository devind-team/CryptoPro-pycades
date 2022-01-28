FROM python:3.9.10 AS build

LABEL developer="Miloslavskiy Sergey"
LABEL maintainer="MiloslavskiySergey@yandex.ru"

# Installing required build packages
RUN set -ex && \
    apt-get update && \
    apt-get install -y --no-install-recommends \
        curl \
        cmake \
        build-essential \
        libboost-all-dev \
        python3-dev \
        unzip && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

# Set timezone
ENV TZ="Europe/Moscow"

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && \
    echo $TZ > /etc/timezone

# Copy files to install CryptoPro
COPY ./dist /cprocsp

# Choosing a working directory for installing CryptoPro
WORKDIR /cprocsp

# Download the archive from CryptoPro CSP (https://cryptopro.ru/products/csp/downloads#latest_csp50r2_linux), unpack this
# archive and install CryptoPro CSP
RUN set -ex && \
    tar xvf linux-amd64_deb.tgz && \
    ./linux-amd64_deb/install.sh && \
    # Install cprocsp-devel package
    apt-get install ./linux-amd64_deb/lsb-cprocsp-devel_*.deb

# Download the archive from the CruptoPro EDS SDK (https://cryptopro.ru/products/cades/downloads), unpack this archive
# and install the cprocsp-pki-cades package (version 2.0.14071 or later)
RUN set -ex && \
    curl -O https://cryptopro.ru/sites/default/files/products/cades/current_release_2_0/cades-linux-amd64.tar.gz && \
    mkdir ./cades-linux-amd64 && \
    tar xvf cades-linux-amd64.tar.gz -C ./cades-linux-amd64 && \
    apt-get install ./cades-linux-amd64/cprocsp-pki-cades-*amd64.deb

# Download and extract the pycades source archive
# (https://cryptopro.ru/sites/default/files/products/cades/pycades/pycades.zip)
RUN set -ex && \
    curl -O https://cryptopro.ru/sites/default/files/products/cades/pycades/pycades.zip && \
    unzip pycades.zip && \
    # Set the value of the Python_INCLUDE_DIR variable in the CMakeList.txt file (Python.h folder)
    sed -i '2c\SET(Python_INCLUDE_DIR "/usr/local/include/python3.9")' ./pycades_*/CMakeLists.txt

# ENV PYCADES="pycades_0.1.30636"

# Build extension pucades
RUN set -ex && \
    # cd /cprocsp/$PYCADES && \
    cd /cprocsp/pycades_* && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make -j4


FROM python:3.9.10 AS cryptopro-http
# Adding a new layer
# ENV PYCADES="pycades_0.1.30636"
# Copying CryptoPro and expanding pycades from the previous stage
COPY --from=build /cprocsp/pycades_*/pycades.so /usr/local/lib/python3.9/pycades.so

COPY --from=build /opt/cprocsp /opt/cprocsp/

COPY --from=build /var/opt/cprocsp /var/opt/cprocsp/

COPY --from=build /etc/opt/cprocsp /etc/opt/cprocsp/

# Installing the package for container operation via command line
RUN set -ex && \
    apt-get update && \
    apt-get install -y --no-install-recommends expect && \
    apt-get autoremove -y && \
    rm -rf /var/lib/apt/lists/*

# Copying bash scripts for container operation via command line
ADD scripts /scripts

# Creation of symbolic links in the contaioner so that CryptoPro functions can be performed via the command line
RUN cd /bin && \
    ln -s /opt/cprocsp/bin/amd64/certmgr && \
    ln -s /opt/cprocsp/bin/amd64/cpverify && \
    ln -s /opt/cprocsp/bin/amd64/cryptcp && \
    ln -s /opt/cprocsp/bin/amd64/csptest && \
    ln -s /opt/cprocsp/bin/amd64/csptestf && \
    ln -s /opt/cprocsp/bin/amd64/der2xer && \
    ln -s /opt/cprocsp/bin/amd64/inittst && \
    ln -s /opt/cprocsp/bin/amd64/wipefile && \
    ln -s /opt/cprocsp/sbin/amd64/cpconfig

#FROM cryptopro-http

#ADD ./http /http

#RUN cd /http \
#    apt-get update -y && \
#    pip install poetry --no-cache-dir && \
#    pip install --upgrade pip && \
#    poetry install && \
#    apt-get autoremove -y && \
#    rm -rf /var/lib/apt/lists/*
