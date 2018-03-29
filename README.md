# Balloon Finder Framework


## Pre-install Requirements
``` 
sudo apt-get install cmake 
sudo apt-get install build-essential
sudo apt-get install cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev
sudo apt-get install python-dev python-numpy libtbb2 libtbb-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev libdc1394-22-dev
```

## Install OpenCV C++
```
cd ~
git clone https://github.com/opencv/opencv.git
cd opencv
mkdir build-release
cd build-release
cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
sudo make all -j4 install
```

## Build and Run
## Change to BalloonFinderFramework directory
Go to wherever this project was cloned.

### Make a build directory
```
mkdir build-release
```

### Make the project
```
cd build-release
cmake ..
make all -j4
```

### Run the project
```
cd build-release
./main
```
