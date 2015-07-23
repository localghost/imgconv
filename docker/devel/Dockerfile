FROM ubuntu:15.04

ENV DEBIAN_FRONTEND noninteractive 

RUN apt-get update
RUN apt-get install -y g++
RUN apt-get install -y cmake
RUN apt-get install -y pkg-config
RUN apt-get install -y qt5-default
RUN apt-get install -y libmagickcore-dev
RUN apt-get install -y libboost-dev
RUN apt-get install -y libboost-system-dev
RUN apt-get install -y libboost-filesystem-dev

RUN apt-get install -y wget
RUN apt-get install -y libxslt1.1
RUN apt-get install -y libpulse0

RUN wget http://download.qt.io/official_releases/qtcreator/3.4/3.4.2/qt-creator-opensource-linux-x86_64-3.4.2.run -O /tmp/qtcreator.run --no-verbose
RUN chmod +x /tmp/qtcreator.run
RUN /tmp/qtcreator.run --runoperation Mkdir /opt/qtcreator
RUN /tmp/qtcreator.run --runoperation Extract installer://org.qtproject.qtcreator.application/3.4.2qt-creator-installer-archive.7z /opt/qtcreator
RUN /tmp/qtcreator.run --runoperation InstallIcons /opt/qtcreator/share/icons
RUN /tmp/qtcreator.run --runoperation CreateDesktopEntry QtProject-qtcreator.desktop Type=Application
RUN rm -f /tmp/qtcreator.run

RUN apt-get install -y libdrm-nouveau2
RUN apt-get install -y xserver-xorg-video-nouveau

RUN adduser me

CMD /opt/qtcreator/bin/qtcreator
