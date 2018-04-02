#include <cstdlib>
#include <string>
#include <iostream>
#include <fstream>
#include <experimental/filesystem>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "sensorParams.h"
#include "callback.h"

namespace fs = std::experimental::filesystem;

/* Extern variables */
SensorParams sensorParams;

int main() {

    /* Fill in sensor params */
    sensorParams.f = 1600.0;
    sensorParams.k1 = -0.02;
    sensorParams.imageWidth = 3840;
    sensorParams.imageHeight = 2176;

    /* Output file */
    std::ofstream output("../images/balloon_positions.txt");

    /* Process images */
    const std::string imageDirPath = "../images/";
    for(const auto& de: fs::directory_iterator(imageDirPath)){
        const std::string imagePath = de.path().string();

        // Only pull in files with extension ".jpg"
        if(imagePath.find(".jpg") == std::string::npos) { continue; }

        // Load image
        cv::Mat inputImg = cv::imread(imagePath, CV_LOAD_IMAGE_COLOR);

        // Find balloons
        std::vector<BalloonInfo> balloonInfoVec = processImage(inputImg);

        if(!balloonInfoVec.empty()) {
            const BalloonInfo info = balloonInfoVec[0];
            if(info.color == blue) { continue; }
            
            output << de.path().filename().string() 
                   << " " 
                   << (info.balloonLocation(0) - sensorParams.imageWidth / 2) 
                   << " " 
                   << -(info.balloonLocation(1) - sensorParams.imageHeight / 2)
                   << "\n";
        }

    }


    return EXIT_SUCCESS;
}
