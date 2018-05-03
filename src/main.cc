#include <cstdlib>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "sensorParams.h"
#include "callback.h"
#include "io.h"

namespace fs = std::experimental::filesystem;

/* Extern variables */
SensorParams sensorParams;

int main() {

    /* Fill in sensor params */
    sensorParams.rcB = Eigen::Vector3d(0.1159, -0.0004, -0.0435);
    sensorParams.rpB = Eigen::Vector3d(0.1013, -0.0004 , 0.0472);
    sensorParams.rrG = Eigen::Vector3d(-741990.536, -5462227.638, 3198019.45);
    sensorParams.riG = Eigen::Vector3d(-742018.3187986395, -5462218.0363918105, 3198014.2988005267);
    sensorParams.camera_matrix = (cv::Mat1d(3, 3) << 1691.0, 0, 1914.0, 0, 1697.0, 1074.0, 0, 0, 1);
    sensorParams.dist_coeffs = (cv::Mat1d(1, 5) << -0.06117476, 0.11208021, -0.00043455, -0.00232441, -0.06783447);

    /* Read in the measurement file */
    const std::string measurement_file_path = "../images/image_data_raw.txt";
    std::map<std::string, RawMeasurement> measurement_map = ParseMeasurementFile(measurement_file_path);

    /* Process images */
    const std::string image_dir_path = "../images/";
    std::map<std::string, Observation> database;
    
    for(const auto& de: fs::directory_iterator(image_dir_path)){
        const std::string image_path = de.path().string();
        const std::string image_name = de.path().filename().string();

        // Only pull in files with extension ".jpg"
        if(image_path.find(".jpg") == std::string::npos) { continue; }

        // Load image
        cv::Mat input_img = cv::imread(image_path, CV_LOAD_IMAGE_COLOR);

        // Find balloons
        std::vector<BalloonInfo> balloon_info_vec = processImage(input_img);

        // Draw circle around located balloons
        for(BalloonInfo& info: balloon_info_vec) {
            // Draw outer circle
            cv::circle(input_img, 
                cv::Point2d(info.balloonLocation(0), info.balloonLocation(1)),
                info.balloonRadius,
                cv::Scalar(0, 0, 0),
                5);

            // Draw inner circle
            cv::circle(input_img, 
                cv::Point2d(info.balloonLocation(0), info.balloonLocation(1)),
                5,
                cv::Scalar(0, 0, 0),
                5);
        }

        // Estimate the position of the balloons
        const RawMeasurement meas = measurement_map[image_name];
        Observation obs{
            balloon_info_vec, 
            meas.rpG,
            meas.RpG,
            Eigen::Vector3d(meas.el, meas.az, meas.roll),
            Eigen::Vector3d(
                std::pow(meas.el_sigma, 2), 
                std::pow(meas.az_sigma, 2), 
                std::pow(meas.roll_sigma, 2)).asDiagonal() 
            };
        database[image_name] = obs;
        std::cout << "Estimated Position: " << estimatePosition(database).at(red).transpose() << std::endl;

        // Display image
        cv::Mat displayImg = cv::Mat(960, 1280, 3);
        cv::resize(input_img, displayImg, displayImg.size());
        cv::imshow("Image", displayImg); 
        cv::waitKey(0);  
    }


    return EXIT_SUCCESS;
}
