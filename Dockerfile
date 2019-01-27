FROM ubuntu:16.04
LABEL maintainer="Aviator" \
      discord="Aviator#1024"

RUN apt-get update &&\
    apt-get install -y wget libboost-system1.58.0 libboost-filesystem1.58.0 libboost-program-options1.58.0 unzip\
    libboost-thread1.58.0 libboost-chrono1.58.0 libevent-2.0-5 libevent-pthreads-2.0-5 &&\
    wget https://github.com/merge-swap/fxrate-wallet/releases/download/1.0.0.1/FXRateCoin_v1.0.0.1_linux.zip -O /tmp/fxrate.zip &&\
    unzip /tmp/fxrate.zip -d /usr/local/bin &&\
    rm /usr/local/bin/fxrate-qt &&\ 
    rm /usr/local/bin/fxrate-tx && \
    chmod +x /usr/local/bin/fxrated &&\
    chmod +x /usr/local/bin/fxrate-cli &&\
    apt-get purge -y wget  &&\
    rm -rf /tmp/* &&\
    rm -rf /var/lib/apt/lists/* &&\
    apt-get clean &&\
    useradd -ms /bin/bash wallet

VOLUME ["/home/wallet/.fxrate"]
EXPOSE 34222/tcp 
USER wallet 
CMD fxrated -printtoconsole
