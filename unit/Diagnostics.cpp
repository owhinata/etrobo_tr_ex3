/******************************************************************************
 *  Diagnostics.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "Diagnostics.h"

#ifdef MAKE_RASPIKE
#include <hiredis/hiredis.h>
#include <stdio.h>
#include <time.h>
#endif

#include "ev3api.h"

static constexpr sensor_port_t kColorSensorPort = EV3_PORT_2;
static constexpr sensor_port_t kGyroSensorPort = EV3_PORT_4;
static constexpr sensor_port_t kSonarSensorPort = EV3_PORT_3;
static constexpr motor_port_t kLeftMotorPort = EV3_PORT_C;
static constexpr motor_port_t kRightMotorPort = EV3_PORT_B;

struct Diagnostics::Context {
  struct {
    uint16_t r, g, b;
    int8_t brightness;
  } color = {};
  struct {
    uint16_t angle, rate;
  } gyro = {};
  struct {
    uint16_t distance;
  } ultrasonic = {};
  struct {
    int count, power;
  } left_motor = {}, right_motor = {};
  int invalidate = 0;
  uint32_t elapsed = 0;
  SYSTIM start = 0;
#ifdef MAKE_RASPIKE
  redisContext *redis = 0;
  char key[29] = {};
#endif
};

Diagnostics::Diagnostics() : ctx_(new Context) {
#ifdef MAKE_RASPIKE
  redisContext *c = redisConnect("localhost", 6379);
  if (c && c->err) {
    redisFree(c);
  } else {
    printf("Connect to redis\n");
    ctx_->redis = c;
  }
  time_t now = time(0);
  strftime(ctx_->key, sizeof(ctx_->key), R"("EtRobo %F %T")", localtime(&now));
#endif
  get_tim(&ctx_->start);
}

Diagnostics::~Diagnostics() {
#ifdef MAKE_RASPIKE
  if (ctx_->redis) {
    redisFree(ctx_->redis);
  }
  delete ctx_;
#endif
}

void Diagnostics::Commit() {
  if (ctx_->invalidate) {
#ifdef MAKE_RASPIKE
    if (ctx_->redis) {
      void *r =
          redisCommand(ctx_->redis, "XADD %s * AA %d BA %u BB %u BC %u BD %d "
                       "CA %u CB %u DA %u EA %d EB %d FA %d FB %d",
                       ctx_->key, ctx_->elapsed, ctx_->color.r, ctx_->color.g,
                       ctx_->color.b, ctx_->color.brightness, ctx_->gyro.angle,
                       ctx_->gyro.rate, ctx_->ultrasonic.distance,
                       ctx_->left_motor.count, ctx_->left_motor.power,
                       ctx_->right_motor.count, ctx_->right_motor.power);
      freeReplyObject(r);
    }
#endif
  }
  ctx_->invalidate = 0;
}

void Diagnostics::Invalidate() {
  if (!ctx_->invalidate) {
    SYSTIM now;
    get_tim(&now);
    ctx_->elapsed = static_cast<uint32_t>(now - ctx_->start);
    ++ctx_->invalidate;
  }
}

void Diagnostics::MonitorColorSensor(ColorSensorMode mode) {
  if (ev3_sensor_get_type(kColorSensorPort) == COLOR_SENSOR) {
    if (mode == ColorSensorMode::kReflect) {
      ctx_->color.brightness = ev3_color_sensor_get_reflect(kColorSensorPort);
      Invalidate();
    } else if (mode == ColorSensorMode::kRgbRaw) {
      rgb_raw_t color{};
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
