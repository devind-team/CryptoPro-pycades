FROM python:3.9.10 AS build

# Установка необходимых пакетов для сборки
RUN set -ex; \
    apt-get update; \
    apt-get install -y --no-install-recommends \
        cmake \
        build-essential \
        libboost-all-dev \
        python3-dev \
        unzip; \
    rm -rf /var/lib/apt/lists/*

# Устанавливаем timezone
ENV TZ="Europe/Moscow" \
    docker="1"

RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && \
    echo $TZ > /etc/timezone

COPY ./dist /cprocsp

WORKDIR /cprocsp

RUN set -ex && \
    tar xvf linux-amd64_deb.tgz && \
    ./linux-amd64_deb/install.sh && \
    apt-get install ./linux-amd64_deb/lsb-cprocsp-devel_*.deb

RUN set -ex && \
    mkdir ./cades-linux-amd64 && \
    tar xvf cades-linux-amd64.tar.gz -C ./cades-linux-amd64 && \
    apt-get install ./cades-linux-amd64/cprocsp-pki-cades-*amd64.deb

RUN set -ex && \
    cd /cprocsp; \
    unzip pycades.zip;

ENV PYCADES="pycades_0.1.30636"

RUN set -ex; \
    cd /cprocsp/$PYCADES; \
    mkdir build; \
    cd build; \
    cmake ..; \
    make -j4

FROM python:3.9.10

ENV PYCADES="pycades_0.1.30636"

COPY --from=build /cprocsp/$PYCADES/pycades.so /usr/local/lib/python3.9/pycades.so

COPY --from=build /opt/cprocsp /opt/cprocsp/

COPY --from=build /var/opt/cprocsp /var/opt/cprocsp/

COPY --from=build /etc/opt/cprocsp /etc/opt/cprocsp/

ADD scripts /scripts

# делаем симлинки
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

