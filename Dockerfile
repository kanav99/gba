FROM ubuntu:latest

RUN apt-get update && apt-get -y install make g++ --no-install-recommends
