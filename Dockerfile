FROM ros:noetic

RUN echo "deb https://mirror.aarnet.edu.au/pub/ubuntu/archive/ focal main restricted universe multiverse\n\
    deb https://mirror.aarnet.edu.au/pub/ubuntu/archive/ focal-updates main restricted universe multiverse\n\
    deb https://mirror.aarnet.edu.au/pub/ubuntu/archive/ focal-security main restricted universe multiverse\n" > /etc/apt/sources.list

WORKDIR /dependencies

# Extra dependencies that are needed.
RUN apt-get update && apt-get install -y \
    git python3-pip \
    ros-noetic-nlopt libnlopt-cxx-dev \
    wget ros-noetic-rviz ros-noetic-kdl-parser \
    ros-noetic-trac-ik ros-noetic-trac-ik-lib \
    gazebo9 libgazebo9-dev && \
    apt-get remove -y ros-noetic-fcl && \
    rm -rf /var/lib/apt/lists/*

# Copy OPPT
WORKDIR /app
COPY . .