/******************************************************************************
 *  PoseEstimator.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "PoseEstimator.h"

#include <math.h>

class PoseEstimator::Impl {
  ev3api::Motor& left;
  ev3api::Motor& right;
  ev3api::GyroSensor& gyro;
  Diagnostics* diag;

  double radius;
  double tread;

  Pose pose;
  double distance;
  double lc0, rc0;
  double yaw0;

public:
  Impl(ev3api::Motor& _left, ev3api::Motor& _right, ev3api::GyroSensor& _gyro,
       Diagnostics* _diag)
    : left(_left), right(_right), gyro(_gyro), diag(_diag) {}

  void init(const ScenarioParams& params) {
    #define GET(a, b, c) params.get(a, &val) ? b(val) : c
    double val;
    radius = GET("radius", double, 0.049);
    tread = GET("tread", double, 0.1317);
    printf("PoseEstimator\n"
           "  radius: %f\n"
           "  tread:  %f\n",
           radius, tread);
    left.reset();
    right.reset();
    gyro.reset();
    lc0 = float(left.getCount());
    rc0 = float(right.getCount());
    yaw0 = -float(gyro.getAngle()),
    distance = 0.0;
    pose.px = pose.py = pose.rz = 0.0;
  }

  static double normalize(double angle, double base) {
    double min = base - 180.0;
    angle = fmod(angle - min, 360) + min;
    if (angle < min) {
      angle += 360;
    }
    return angle;
  }

  bool update() {
    double lc = float(left.getCount()),
           rc = float(right.getCount()),
           yaw = -float(gyro.getAngle()),
           w = float(gyro.getAnglerVelocity());

    double dl = M_PI * radius * (lc - lc0) / 180.0,
           dr = M_PI * radius * (rc - rc0) / 180.0,
           d = (dr + dl) / 2.0;

    distance += d;

    double rz = pose.rz + (dr - dl) / tread,
           px = pose.px + d * cos(rz),
           py = pose.py + d * sin(rz);

    pose.px = px;
    pose.py = py;
    pose.rz = rz;
    lc0 = lc;
    rc0 = rc;

    yaw = normalize(yaw, yaw0);
    yaw0 = yaw;
    yaw *= M_PI / 180.0;

    diag->setMeasure(lc, rc, yaw, w, px, py, rz, distance);

    return true;
  }

  Pose getPose() { return pose; }

  double getDistance() { return distance; }
};

PoseEstimator::PoseEstimator(ev3api::Motor& left, ev3api::Motor& right,
                             ev3api::GyroSensor& gyro, Diagnostics* diag)
  : mImpl(new Impl(left, right, gyro, diag)) {}

PoseEstimator::~PoseEstimator() { delete mImpl; }

const char* PoseEstimator::getClassName() const { return "PoseEstimator"; }

void PoseEstimator::init(const ScenarioParams& params) {
  mImpl->init(params);
}

bool PoseEstimator::update() { return mImpl->update(); }

Pose PoseEstimator::getPose() const { return mImpl->getPose(); }

double PoseEstimator::getDistance() const { return mImpl->getDistance(); }
