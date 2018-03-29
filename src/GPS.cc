#include "gps.h"
#include <cstdlib>

void attitudeMessageHandler(const Attitude2D msg) {
    const std::vector<float> P = msg.P;
    const double azAngle = msg.azAngle;
    const double elAngle = msg.elAngle;
    const double azSigma = msg.azSigma;
    const double elSigma = msg.elSigma;

    gpsSolution.el = elAngle;
    gpsSolution.az = azAngle;

    gpsSolution.elSigma = elSigma;
    gpsSolution.azSigma = azSigma;

    for(size_t i = 0; i < 6; i++) {
        gpsSolution.attCov[i] = P[i];
    }

    return;

}

void positionMessageHandler(const SingleBaselineRTK msg) {
    const double rxRov = msg.rxRov;
    const double ryRov = msg.ryRov;
    const double rzRov = msg.rzRov;
    const std::vector<float> P = msg.P;

    gpsSolution.x = rxRov;
    gpsSolution.y = ryRov;
    gpsSolution.z = rzRov;

    for(int i = 0; i < 6; i++) {
        gpsSolution.posCov[i] = P[i];
    }

    return;
}
