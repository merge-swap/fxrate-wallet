FROM alpine:3.6 
LABEL maintainer="Aviator" \
      discord="Aviator#1024"

ENV DB_VERSION=4.8.30.NC 
RUN deps="alpine-sdk curl autoconf automake libtool boost-dev openssl-dev libevent-dev git libbsd-dev" && \
  apk add --no-cache -U $deps dumb-init boost boost-program_options libevent libssl1.0 && \
  curl -L http://download.oracle.com/berkeley-db/db-$DB_VERSION.tar.gz \
  | tar zx && \
  cd /db-$DB_VERSION/build_unix && \
  ../dist/configure \
  --prefix=/opt/db \
  --enable-cxx \
  --disable-shared \
  --with-pic && \
  make install && \
  mkdir /wallet &&\
  cd /wallet && \
  git clone https://github.com/merge-swap/fxrate-wallet.git . &&\   
  ./autogen.sh && \ 
  ./configure LDFLAGS=-L/opt/db/lib CPPFLAGS=-I/opt/db/include && \ 
  make install && \ 
  strip /usr/local/bin/fxrated &&\ 
  strip /usr/local/bin/fxrate-cli &&\ 
  rm /usr/local/bin/fxrate-tx &&\ 
  rm /usr/local/bin/test_fxrate &&\ 
  adduser -D wallet && \ 
  apk del $deps && \
  rm -r /opt/db/docs /var/cache/apk/* /wallet /db-$DB_VERSION 

VOLUME ["/home/wallet/.fxrate"]
EXPOSE 34222/tcp 
USER wallet 
CMD fxrated -printtoconsole