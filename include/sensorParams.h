#pragma once
#include <Eigen/Core>
#include <opencv2/core/core.hpp>

typedef struct {
    /* Position of the camera with respect to body origin in body frame */
    Eigen::Vector3d rcB;

    /* Position of primary with respect to body origin in body frame */
    Eigen::Vector3d rpB;

    /* Position of reference antenna with respect to ECEF origin in ECEF frame */
    Eigen::Vector3d rrG;

    /* Position of inertial origin with respect to ECEF origin in ECEF frame */
    Eigen::Vector3d riG;

    // Camera matrix used for undistort
    // https://docs.opencv.org/3.4.1/da/d54/group__imgproc__transform.html#ga69f2545a8b62a6b0fc2ee060dc30559d
    cv::Mat camera_matrix;

    /* Distortion coefficient */
    // https://docs.opencv.org/3.4.1/da/d54/group__imgproc__transform.html#ga69f2545a8b62a6b0fc2ee060dc30559d
    // k1, k2, p1, p2, k3
    cv::Mat dist_coeffs;

    // Pitch of the camera. Angled 30 degrees down.
    double camera_angle;

    // Focal length in pixels
    double focal_length;

} SensorParams;

extern SensorParams sensorParams;
