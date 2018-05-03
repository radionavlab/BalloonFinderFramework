/* Author: Tucker Haydon */
#pragma once 

#include <Eigen/Core>
#include <iostream>
#include <fstream>
#include <map>
#include <string>

typedef struct {
    double az;                  // Azimuth in radians
    double el;                  // Elevation in radians
    double roll;                // Roll angle in radians
    double az_sigma;            // Standard deviation of azimuth
    double el_sigma;            // Standard deviation of elevation
    double roll_sigma;          // Standard deviation of roll
    Eigen::Vector3d rpG;        // Primary antenna in ECEF
    Eigen::Matrix3d RpG;        // Covariance of primary antenna
    Eigen::Matrix3d RbG;        // Covariance of baseline
} RawMeasurement;

inline std::map<std::string, RawMeasurement> ParseMeasurementFile(const std::string& filename) {

    std::map<std::string, RawMeasurement> measurement_map;

    std::ifstream f(filename);
    std::string line;
    while (getline(f, line)) {
        if(line.at(0) == '#') { continue; }

        std::stringstream ss(line);
        std::string imageName;
        double az;
        double el;
        double roll;
        double az_sigma;
        double el_sigma;
        double roll_sigma;
        Eigen::Vector3d rpG;
        Eigen::Matrix3d RpG;
        Eigen::Matrix3d RbG;
        
        ss >> imageName;
        ss >> rpG(0) >> rpG(1) >> rpG(2);
    
        // Covariance of primary
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i > j) { continue; }
                ss >> RpG(j, i);
                RpG(i, j) = RpG(j, i);
            }
        }

        // Attitude
        ss >> el >> az >> el_sigma >> az_sigma;
        roll = 0;
        roll_sigma = 10 * M_PI/180;

        // Covariance of baseline
        for(int i = 0; i < 3; i++) {
            for(int j = 0; j < 3; j++) {
                if(i > j) { continue; }
                ss >> RbG(j, i);
                RbG(i, j) = RbG(j, i);
            }
        }


        measurement_map[imageName] = RawMeasurement{az, el, roll, az_sigma, el_sigma, roll_sigma, rpG, RpG, RbG};
    }

    return measurement_map;

}
