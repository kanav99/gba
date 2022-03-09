FROM ubuntu:20.04

RUN apt-get update && apt-get -y install make g++ z80asm --no-install-recommends
