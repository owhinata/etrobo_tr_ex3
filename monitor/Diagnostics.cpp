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
    uint16_t r, g, b;
    int8_t brightness;
  } color;
  struct {
    uint16_t angle, rate;
  } gyro;
  struct {
    uint16_t distance;
  } ultrasonic;
  struct {
    int count, power;
  } left_motor, right_motor;
  int invalidate;
  uint32_t elapsed;
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
  strftime(file, sizeof(file), "EtRobo_%F_%T.log", localtime(&now));
#else
  snprintf(ctx_->key, sizeof(ctx_->key), "%s", "\"EtRobo\"");
  snprintf(file, sizeof(file), "%s.log", "EtRobo");
#endif
  ctx_->fp = fopen(file, "w");
  printf("%p\n", ctx_->fp);
  get_tim(&ctx_->start);
}

Diagnostics::~Diagnostics() {
  if (ctx_->fp) {
    fclose(ctx_->fp);
  }
  delete ctx_;
}

void Diagnostics::init(ColorSensorMode mode) {}

void Diagnostics::Commit() {
  if (ctx_->invalidate) {
    if (ctx_->fp) {
      fprintf(ctx_->fp,
              "XADD %s * AA %lu BA %u BB %u BC %u BD %d "
              "CA %u CB %u DA %u EA %d EB %d FA %d FB %d\n",
              ctx_->key, ctx_->elapsed, ctx_->color.r, ctx_->color.g,
              ctx_->color.b, ctx_->color.brightness, ctx_->gyro.angle,
              ctx_->gyro.rate, ctx_->ultrasonic.distance,
              ctx_->left_motor.count, ctx_->left_motor.power,
              ctx_->right_motor.count, ctx_->right_motor.power);
    }
  }
  ctx_->invalidate = 0;
}

void Diagnostics::Invalidate() { ++ctx_->invalidate; }

void Diagnostics::update(uint32_t uptime) {
  ctx_->elapsed = uptime;
  ctx_->invalidate = 0;
}

void Diagnostics::MonitorColorSensor(ColorSensorMode mode) {
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
}

void Diagnostics::MonitorGyroSensor() {
  if (ev3_sensor_get_type(kGyroSensorPort) == GYRO_SENSOR) {
    ctx_->gyro.angle = ev3_gyro_sensor_get_angle(kGyroSensorPort);
    ctx_->gyro.rate = ev3_gyro_sensor_get_rate(kGyroSensorPort);
    Invalidate();
  }
}

void Diagnostics::MonitorSonarSensor() {
  if (ev3_sensor_get_type(kSonarSensorPort) == ULTRASONIC_SENSOR) {
    ctx_->ultrasonic.distance =
        ev3_ultrasonic_sensor_get_distance(kSonarSensorPort);
    Invalidate();
  }
}

void Diagnostics::MonitorMotors() {
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
}
