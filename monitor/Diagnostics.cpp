/******************************************************************************
 *  Diagnostics.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Diagnostics.h"

#include <stdio.h>
#include <string.h>
#ifdef MAKE_RASPIKE
#include <time.h>
#endif

#include "ev3api.h"

static const sensor_port_t kColorSensorPort = EV3_PORT_2;
static const sensor_port_t kGyroSensorPort = EV3_PORT_4;
static const sensor_port_t kSonarSensorPort = EV3_PORT_3;
static const motor_port_t kLeftMotorPort = EV3_PORT_C;
static const motor_port_t kRightMotorPort = EV3_PORT_B;

struct Diagnostics::Context {
  struct {
    double r, g, b;
    double h, s, v, y;
  } color;
  struct {
    double yaw, w;
  } gyro;
  struct {
    double distance;
  } ultrasonic;
  struct {
    double count, power;
  } left_motor, right_motor;
  struct {
    double px, py, rz, distance;
  } pose;
  int invalidate;
  double elapsed;
  SYSTIM start;
  FILE *fp;
  char key[29];
};

Diagnostics::Diagnostics() : ctx_(new Context) {
  char file[36];
  memset(ctx_, 0, sizeof(*ctx_));
#ifdef MAKE_RASPIKE
  time_t now = time(0);
  strftime(ctx_->key, sizeof(ctx_->key), "\"EtRobo %F %T\"", localtime(&now));
  strftime(file, sizeof(file), "EtRobo_%F_%H.%M.%S.csv", localtime(&now));
#else
  snprintf(ctx_->key, sizeof(ctx_->key), "%s", "\"EtRobo\"");
  snprintf(file, sizeof(file), "%s.csv", "EtRobo");
#endif
  ctx_->fp = fopen(file, "w");
  if (ctx_->fp) {
    fprintf(ctx_->fp, ",distance,r,g,b,h,s,v,y,foward,turn,w,yaw,lc,rc,px,py,rz\n");
  }
  get_tim(&ctx_->start);
}

Diagnostics::~Diagnostics() {
  if (ctx_->fp) {
    fclose(ctx_->fp);
  }
  delete ctx_;
}

void Diagnostics::Commit() {
  if (ctx_->fp && ctx_->invalidate) {
    fprintf(ctx_->fp, "%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f,%f\n",
            ctx_->elapsed, ctx_->pose.distance,
            ctx_->color.r, ctx_->color.g, ctx_->color.b,
            ctx_->color.h, ctx_->color.s, ctx_->color.v, ctx_->color.y,
            (ctx_->right_motor.power + ctx_->left_motor.power) / 2.0,
            ctx_->right_motor.power - ctx_->left_motor.power,
            ctx_->gyro.w, ctx_->gyro.yaw,
            ctx_->left_motor.count, ctx_->right_motor.count,
            ctx_->pose.px, ctx_->pose.py, ctx_->pose.rz);
  }
  ctx_->invalidate = 0;
}

void Diagnostics::update(double uptime) {
  ctx_->elapsed = uptime;
  ctx_->invalidate = 0;
}

void Diagnostics::setColor(double rgb[3], double hsv[3], double y) {
  ctx_->color.r = rgb[0];
  ctx_->color.g = rgb[1];
  ctx_->color.b = rgb[2];
  ctx_->color.h = hsv[0];
  ctx_->color.s = hsv[1];
  ctx_->color.v = hsv[2];
  ctx_->color.y = y;
  ++ctx_->invalidate;
}

void Diagnostics::setMeasure(double leftWheelCount, double rightWheelCount,
                             double yaw, double anglVel,
                             double px, double py, double rz, double distance) {
  ctx_->left_motor.count = leftWheelCount;
  ctx_->right_motor.count = rightWheelCount;
  ctx_->gyro.yaw = yaw;
  ctx_->gyro.w = anglVel;
  ctx_->pose.px = px;
  ctx_->pose.py = py;
  ctx_->pose.rz = rz;
  ctx_->pose.distance = distance;
  ++ctx_->invalidate;
}

void Diagnostics::setDriveParam(double leftPower, double rightPower) {
  ctx_->left_motor.power = leftPower;
  ctx_->right_motor.power = rightPower;
  ++ctx_->invalidate;
}

void Diagnostics::MonitorColorSensor(ColorSensorMode mode) {
#if 0
  if (ev3_sensor_get_type(kColorSensorPort) == COLOR_SENSOR) {
    if (mode == kColorSensorModeReflect) {
      ctx_->color.brightness = ev3_color_sensor_get_reflect(kColorSensorPort);
      Invalidate();
    } else if (mode == kColorSensorModeRgbRaw) {
      rgb_raw_t color = {};
      ev3_color_sensor_get_rgb_raw(kColorSensorPort, &color);
      ctx_->color.r = color.r;
      ctx_->color.g = color.g;
      ctx_->color.b = color.b;
      Invalidate();
    }
  }
#endif
}

void Diagnostics::MonitorGyroSensor() {
#if 0
  if (ev3_sensor_get_type(kGyroSensorPort) == GYRO_SENSOR) {
    ctx_->gyro.angle = ev3_gyro_sensor_get_angle(kGyroSensorPort);
    ctx_->gyro.rate = ev3_gyro_sensor_get_rate(kGyroSensorPort);
    Invalidate();
  }
#endif
}

void Diagnostics::MonitorSonarSensor() {
#if 0
  if (ev3_sensor_get_type(kSonarSensorPort) == ULTRASONIC_SENSOR) {
    ctx_->ultrasonic.distance =
        ev3_ultrasonic_sensor_get_distance(kSonarSensorPort);
    Invalidate();
  }
#endif
}

void Diagnostics::MonitorMotors() {
#if 0
  if (ev3_motor_get_type(kLeftMotorPort) == LARGE_MOTOR) {
    ctx_->left_motor.count = ev3_motor_get_counts(kLeftMotorPort);
    ctx_->left_motor.power = ev3_motor_get_power(kLeftMotorPort);
    Invalidate();
  }
  if (ev3_motor_get_type(kRightMotorPort) == LARGE_MOTOR) {
    ctx_->right_motor.count = ev3_motor_get_counts(kRightMotorPort);
    ctx_->right_motor.power = ev3_motor_get_power(kRightMotorPort);
    Invalidate();
  }
#endif
}
