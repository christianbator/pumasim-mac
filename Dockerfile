#
# Dockerfile
#

#
# Base Image and X-Forwarded Graphics
#
FROM ubuntu:20.04
ENV DISPLAY=docker.for.mac.host.internal:0
ENV LIBGL_ALWAYS_INDIRECT=1
VOLUME /tmp/.X11-unix:/tmp/.X11-unix

#
# Dependencies
#
RUN apt-get update
RUN DEBIAN_FRONTEND=noninteractive apt-get install -y tzdata
RUN apt-get install -y build-essential mesa-utils libgl1-mesa-glx libglu-dev libxmu-dev libnewmat10-dev libqhull-dev libopencv-dev cmake libsoil1 libglew2.1 gnuplot

#
# Puma Simulator
#
COPY pumasimulator /pumasimulator
RUN cd /pumasimulator && ./install.sh
