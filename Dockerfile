FROM ros:noetic

RUN rm /etc/apt/sources.list.d/ros1-latest.list

RUN apt update && apt install -y curl

WORKDIR /app
COPY ./install_dependencies.sh ./install_dependencies.sh
RUN ./install_dependencies.sh

WORKDIR /dependencies

# Recreate the ROS key and source list for Noetic (Ubuntu 20.04)
RUN mkdir -p /etc/apt/keyrings && \
    curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | gpg --dearmor -o /etc/apt/keyrings/ros.gpg && \
    echo "deb [signed-by=/etc/apt/keyrings/ros.gpg] http://packages.ros.org/ros/ubuntu focal main" \
        > /etc/apt/sources.list.d/ros1-latest.list && \
    apt-get update

# Extra dependencies that are needed.
RUN apt update && apt install -y git ros-noetic-nlopt libnlopt-cxx-dev wget ros-noetic-rviz ros-noetic-kdl-parser ros-noetic-trac-ik ros-noetic-trac-ik-lib && \
    rm -rf /var/lib/apt/lists/*

# We need a specific version of FCL, so we will build from scratch
RUN apt remove -y ros-noetic-fcl libfcl-dev && \
    cd /app && \
    git clone https://github.com/flexible-collision-library/fcl && \
    cd fcl && git checkout fcl-0.5 && \
    mkdir build && \
    cd build && \
    cmake .. && \
    make && \
    sudo make install

# Install spatialindex
RUN wget http://download.osgeo.org/libspatialindex/spatialindex-src-1.8.5.tar.gz && \
    tar zxfv spatialindex-src-1.8.5.tar.gz && \ 
    cd spatialindex-src-1.8.5 && \
    mkdir build && cd build && \
    cmake -DCMAKE_INSTALL_PREFIX=/usr/local .. && \
    make -j2 && sudo make install

# Finally, make and install oppt
WORKDIR /app
COPY . .

RUN . /opt/ros/noetic/setup.sh && \
    cd /app/src/ && \
    mkdir build && cd build && \
    cmake -DCMAKE_BUILD_TYPE=RELEASE -DCMAKE_INSTALL_PREFIX=. .. && \
    make && make install && \
    echo 'source /app/oppt/src/build/share/oppt/setup.sh' >> ~/.bashrc 