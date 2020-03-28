# use of ubuntu 19.10 linux/AMD64
FROM ubuntu:eoan@sha256:7ce552ad1c3e94a5c3d2bb24c07000c34a4bb43fd9b379652b2c80593a018e80

WORKDIR /home/dev

RUN apt-get update \
    && apt-get install -y --no-install-recommends \
    cmake=3.13.4-1build1 \
    libc6-i386 \
    wget \
    bzip2 \
    build-essential \
    doxygen \
    lcov \
    graphviz \
    git \
    ca-certificates \
    && rm -rf /var/lib/apt/lists/* \
    && cmake --version \
    && export GCC_URL="https://developer.arm.com/-/media/Files/downloads/gnu-rm/9-2019q4/RC2.1/gcc-arm-none-eabi-9-2019-q4-major-x86_64-linux.tar.bz2?revision=6e63531f-8cb1-40b9-bbfc-8a57cdfc01b4&la=en&hash=F761343D43A0587E8AC0925B723C04DBFB848339" \
    && wget -O "gcc.tar.bz2" "$GCC_URL" \
    && tar -jxf gcc.tar.bz2 --strip=1 \
    && rm -f gcc.tar.bz2 \
    && rm -rf share/doc \
    && apt-get purge -y \
    wget \
    bzip2

ENV PATH "/home/dev/bin:$PATH"

WORKDIR /usr/project

CMD ["cmake"]
