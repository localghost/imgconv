FROM ubuntu:15.10

ENV DEBIAN_FRONTEND noninteractive 

RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y cmake
RUN apt-get install -y pkg-config
RUN apt-get install -y qt5-default
RUN apt-get install -y qtdeclarative5-dev
RUN apt-get install -y qtdeclarative5-window-plugin
RUN apt-get install -y qtdeclarative5-controls-plugin
RUN apt-get install -y qtdeclarative5-dialogs-plugin
RUN apt-get install -y libmagickcore-dev
RUN apt-get install -y libboost-dev
RUN apt-get install -y libboost-system-dev
RUN apt-get install -y libboost-filesystem-dev
RUN apt-get install -y libboost-test-dev

RUN apt-get install -y qtcreator

RUN adduser me

CMD /opt/qtcreator/bin/qtcreator
