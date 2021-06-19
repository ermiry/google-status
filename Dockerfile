ARG CERVER_VERSION=2.0b-36

ARG BUILD_DEPS='wget unzip libssl-dev'
ARG RUNTIME_DEPS='libssl-dev'

FROM gcc as builder

WORKDIR /opt

ARG BUILD_DEPS
RUN apt-get update && apt-get install -y ${BUILD_DEPS}

# build cerver with production flags
ARG CERVER_VERSION
RUN mkdir /opt/cerver && cd /opt/cerver \
    && wget -q --no-check-certificate https://github.com/ermiry/cerver/archive/${CERVER_VERSION}.zip \
    && unzip ${CERVER_VERSION}.zip \
    && cd cerver-${CERVER_VERSION} \
    && make TYPE=production -j4 && make TYPE=production install

RUN ldconfig

# google
WORKDIR /opt/google
COPY . .
RUN make TYPE=production -j4

############
FROM ubuntu:bionic

ARG RUNTIME_DEPS
RUN apt-get update && apt-get install -y ${RUNTIME_DEPS}

# cerver
ARG CERVER_VERSION
COPY --from=builder /opt/cerver/cerver-${CERVER_VERSION}/bin/libcerver.so /usr/local/lib/
COPY --from=builder /opt/cerver/cerver-${CERVER_VERSION}/include/cerver /usr/local/include/cerver

RUN ldconfig

# google
WORKDIR /home/google
COPY ./start.sh .
COPY --from=builder /opt/google/bin ./bin

CMD ["/bin/bash", "start.sh"]