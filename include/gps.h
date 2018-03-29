#pragma once

#include <atomic>
#include <vector>

typedef struct {
    std::vector<float> P;
    double rxRov;
    double ryRov;
    double rzRov;
} SingleBaselineRTK;

typedef struct {
    std::vector<float> P;
    double azAngle;
    double elAngle;
    double azSigma;
    double elSigma;
} Attitude2D;


// Position of primary antenna with respect to reference in ECEF
// Position is in meters
// Pose is in radians
typedef struct {
    std::atomic<double> x;
    std::atomic<double> y;
    std::atomic<double> z;
    std::atomic<float> posCov[6];

    std::atomic<double> az;
    std::atomic<double> el;
    std::atomic<double> elSigma;
    std::atomic<double> azSigma;
    std::atomic<float> attCov[6];
} GPSSolution;

extern GPSSolution gpsSolution;

/* Roll variance. Set so +-3 sigma is 15 degrees */
const double rollVar = 0.007615435;

void positionMessageHandler(const SingleBaselineRTK msg);
void attitudeMessageHandler(const Attitude2D msg);
