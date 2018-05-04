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

/*
* Take a database of image observations and estimate the 3D position of the balloons
*/
const std::map<Color, Eigen::Vector3d> estimatePosition(const std::vector<Observation>& database) {
    /* Sensor params in: sensorParams */
    /* Example: cv::Mat cameraMatrixMat = sensorParams.camera_matrix; */
    /* Look at the available sensor params in include/sensorParams.h */

    /* 
    * YOUR CODE GOES HERE
    */

    // Example code
    for(const Observation& obs: database) {
        for(const BalloonInfo& info: obs.info_vec) {
            std::cout << info.balloonLocation.transpose() << std::endl;
        }
    }
    std::cout << std::endl;

    // Example return
    std::map<Color, Eigen::Vector3d> balloon_positions;
    balloon_positions[red] = Eigen::Vector3d(0, 0, 0);
    return balloon_positions;
}
