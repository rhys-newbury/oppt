FROM ros:noetic

RUN rm /etc/apt/sources.list.d/ros1-latest.list

RUN echo "deb https://mirror.aarnet.edu.au/pub/ubuntu/archive/ focal main restricted universe multiverse\n\
    deb https://mirror.aarnet.edu.au/pub/ubuntu/archive/ focal-updates main restricted universe multiverse\n\
    deb https://mirror.aarnet.edu.au/pub/ubuntu/archive/ focal-security main restricted universe multiverse\n" > /etc/apt/sources.list

RUN apt update && apt install -y curl

WORKDIR /dependencies

# Recreate the ROS key and source list for Noetic (Ubuntu 20.04)
RUN mkdir -p /etc/apt/keyrings && \
    curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | gpg --dearmor -o /etc/apt/keyrings/ros.gpg && \
    echo "deb [signed-by=/etc/apt/keyrings/ros.gpg] http://packages.ros.org/ros/ubuntu focal main" \
        > /etc/apt/sources.list.d/ros1-latest.list && \
    apt-get update



# Extra dependencies that are needed.
RUN apt-get update && apt-get install -y \
    git python3-pip \
    ros-noetic-nlopt libnlopt-cxx-dev \
    wget ros-noetic-rviz ros-noetic-kdl-parser \
    ros-noetic-trac-ik ros-noetic-trac-ik-lib \
    gazebo9 libgazebo9-dev && \
    rm -rf /var/lib/apt/lists/*

RUN git clone https://github.com/ignitionrobotics/ign-math -b ign-math4 && \
    cmake -S ign-math -B ign-math/build -DCMAKE_INSTALL_PREFIX=/usr && \
    cmake --build ign-math/build --target install --parallel


# We need a specific version of FCL, so we will build from scratch
RUN apt remove -y ros-noetic-fcl && \
    git clone https://github.com/flexible-collision-library/fcl && \
    cd fcl && git checkout fcl-0.5 && \
    cmake -S . -B build && \
    cmake --build build --parallel && \
    cmake --install build


# Copy OPPT
WORKDIR /app
COPY . .