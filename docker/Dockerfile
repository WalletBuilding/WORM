#FROM debian:stretch
FROM ubuntu:18.04
LABEL maintainer="The Wormcore Developers <sales@mealworms.biz>"
LABEL description="Dockerised Wormcore, built from Travis"

RUN apt-get update && apt-get install -y software-properties-common unzip
RUN apt-get install -y wget

RUN wget https://github.com/WORM-Core/worm/releases/download/v5.2.3/worm-qt-linux-18.zip
RUN unzip worm-qt-linux-18.zip
RUN cp wormd /usr/local/bin

VOLUME ["/opt/worm"]

EXPOSE 9888
EXPOSE 9888
EXPOSE 9777
EXPOSE 9777

CMD ["wormd", "--conf=/opt/worm/worm.conf", "--printtoconsole"]