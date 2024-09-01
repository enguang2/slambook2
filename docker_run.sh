#docker is at https://github.com/Dylancer1998/slam14-docker
#for Gao Xiang slambook
#Use this script to start docker elegeantly after you pull the image
echo "please make sure running this script in root dir of slambook2, also you need to ignore code not built by you, this is a borrowed docker images from https://github.com/Dylancer1998/slam14-docker/  Current working dir: $PWD"
docker run -it \
-e DISPLAY=$DISPLAY -v /tmp/.X11-unix:/tmp/.X11-unix \
-v "$PWD":/usr/games \
--network host \
--name slambook2 \
bodcoder2/slam14:latest \
/bin/bash
