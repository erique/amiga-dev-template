FROM ubuntu:22.04

RUN apt-get update
RUN apt-get install -y make wget git gcc g++ lhasa libgmp-dev libmpfr-dev libmpc-dev flex bison gettext texinfo ncurses-dev autoconf rsync

RUN git config --global pull.ff only

RUN mkdir -p /opt/amiga                                        && \
    cd /root                                                   && \
    git clone --depth 1 https://github.com/bebbo/amiga-gcc.git && \
    cd amiga-gcc                                               && \
    make update                                                && \
    make -j4 all                                               && \
    cd ..                                                      && \
    rm -rf amiga-gcc

ENV PATH /opt/amiga/bin:$PATH
