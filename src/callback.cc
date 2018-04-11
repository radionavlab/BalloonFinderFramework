#include <opencv2/opencv.hpp>
#include <vector>

#include "callback.h"
#include "sensorParams.h"

/*
* Process a single image and return a vector of observations.  Observations are
* defined by the struct BalloonInfo. Look how BalloonInfo is defined in
* include/callback.h
*/
const std::vector<BalloonInfo> processImage(const cv::Mat& img) {
    /* Sensor params in: sensorParams */
    /* Example: cv::Mat cameraMatrixMat = sensorParams.camera_matrix; */
    /* Look at the available sensor params in include/sensorParams.h */

    /* 
    * YOUR CODE GOES HERE
    */

    return std::vector<BalloonInfo>();
}
