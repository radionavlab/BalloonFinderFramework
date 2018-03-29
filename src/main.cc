#include <cstdlib>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "gps.h"
#include "sensorParams.h"
#include "callback.h"

namespace fs = std::experimental::filesystem;

/* Extern variables */
GPSSolution gpsSolution;
SensorParams sensorParams;

int main() {

    /* Fill in sensor params */
    sensorParams.rcB = Eigen::Vector3d(0.1159, -0.0004, -0.0435);
    sensorParams.rpB = Eigen::Vector3d(0.1013, -0.0004 , 0.0472);
    sensorParams.rrG = Eigen::Vector3d(-741990.536, -5462227.638, 3198019.45);
    sensorParams.riG = Eigen::Vector3d(-742015.136, -5462219.538, 3198014.35);
    sensorParams.f = 1600.0;
    sensorParams.k1 = -0.02;
    sensorParams.imageWidth = 3840;
    sensorParams.imageHeight = 2176;

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

        // Draw circle around located balloons
        for(BalloonInfo& info: balloonInfoVec) {
            // Draw outer circle
            cv::circle(inputImg, 
                cv::Point2d(info.balloonLocation(0), info.balloonLocation(1)),
                info.balloonRadius,
                cv::Scalar(0, 0, 0),
                5);

            // Draw inner circle
            cv::circle(inputImg, 
                cv::Point2d(info.balloonLocation(0), info.balloonLocation(1)),
                5,
                cv::Scalar(0, 0, 0),
                5);
        }

        // Display image
        cv::Mat displayImg = cv::Mat(960, 1280, 3);
        cv::resize(inputImg, displayImg, displayImg.size());
        cv::imshow("Image", displayImg); 
        cv::waitKey(0);  
    }


    return EXIT_SUCCESS;
}
