#docker is at https://github.com/Dylancer1998/slam14-docker
#for Gao Xiang slambook
#Use this script to start docker elegeantly after you pull the image

# UI permisions
XSOCK=/tmp/.X11-unix
XAUTH=/tmp/.docker.xauth
touch $XAUTH
xauth nlist $DISPLAY | sed -e 's/^..../ffff/' | xauth -f $XAUTH nmerge -

xhost +local:docker

# Remove existing container
docker rm -f slambook2 &>/dev/null
[ -d "slambook2" ] && sudo rm -rf slambook2 && mkdir slambook2


echo "please make sure running this script in root dir of slambook2, also you need to ignore code not built by you, this is a borrowed docker images from https://github.com/Dylancer1998/slam14-docker/  Current working dir: $PWD"

# mount the KITTI dataset
# In docker, it's under /usr/games/ch11/dataset
docker run -it --privileged --net=host --ipc=host \
--name="slambook2" \
-e DISPLAY=$DISPLAY \
-v /tmp/.X11-unix:/tmp/.X11-unix \
-v /etc/group:/etc/group:ro \
-v "$PWD":/usr/games \
-v /home/ds/Research/lcd/orbslam3_docker/Datasets:/usr/games/ch11/dataset \
-v ~/ds/.ssh:/root/.ssh:ro \
bodcoder2/slam14:latest \
/bin/bash


# Install some missing lib
docker exec -it slambook2 bash -i -c "apt update && apt install cmake"

# Compile Ch11 for DBoW3 experiment
docker exec -it slambook2 bash -i -c "cd /usr/games/ch11 && mkdir build && cd build && cmake .. && make && cd .."
