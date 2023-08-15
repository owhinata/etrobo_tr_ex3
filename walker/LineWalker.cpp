/******************************************************************************
 *  LineWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Implementation of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "LineWalker.h"

#include <math.h>

// 定数宣言
static const double RIGHT_EDGE  = 1.0;      // 左エッジ
static const double LEFT_EDGE   = -1.0;     // 右エッジ
static const double WHITE_BRIGHTNESS  = 140.0;      // カラーセンサの輝度設定用
static const double BLACK_BRIGHTNESS  = 10.0;      // カラーセンサの輝度設定用
static const double STEERING_COEF  = 0.3;      // ステアリング操舵量の係数
static const double DIFFERENTIAL_COEF = 15;   // D制御の係数
static const double BASE_SPEED  = 30.0;      // 走行標準スピード

/**
 * コンストラクタ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 */
LineWalker::LineWalker(Driver* driver)
    : Walker(driver),
      mEdge(LEFT_EDGE),
      mWhilteBrightness(WHITE_BRIGHTNESS),
      mBlackBrightness(BLACK_BRIGHTNESS),
      mSteeringCoef(STEERING_COEF),
      mDifferentialCoef(DIFFERENTIAL_COEF),
      mPrevDiffBrightness(50.0),
      mBaseSpeed(BASE_SPEED) {
}

LineWalker::~LineWalker() {}

const char* LineWalker::getClassName() const { return "LineWalker"; }

void LineWalker::reset(const ScenarioParams& params) {
      #define GET(a, b, c) params.get(a, &val) ? b(val) : c
      double val;
      mEdge = GET("edge", double, LEFT_EDGE);
      mWhilteBrightness = GET("white", double, WHITE_BRIGHTNESS);
      mBlackBrightness = GET("black", double, BLACK_BRIGHTNESS);
      mSteeringCoef = GET("kp", double, STEERING_COEF);
      mBaseSpeed = GET("speed", double, BASE_SPEED);
      printf("  edge:  %f\n"
             "  white: %f\n"
             "  black: %f\n"
             "  kp:    %f\n"
             "  speed: %f\n",
             mEdge, mWhilteBrightness, mBlackBrightness,
             mSteeringCoef, mBaseSpeed);
}

/**
 * 走行する
 */
void LineWalker::run() {
    // 反射光の強さを取得する
    double brightness = getBrightness();

    // 走行を行う
    double steeringAmount = steeringAmountCalculation(brightness);
    int leftMotorPower, rightMotorPower;  // 左右モータ設定パワー

    /* 左右モータ駆動パワーの計算 */
    leftMotorPower = (int)round(mBaseSpeed + (steeringAmount * mEdge));
    rightMotorPower = (int)round(mBaseSpeed - (steeringAmount * mEdge));
    // printf(" l: %f r: %f",
    //        mBaseSpeed + (steeringAmount * mEdge),
    //        mBaseSpeed - (steeringAmount * mEdge));
    // printf(" left: %d right: %d\n", leftMotorPower, rightMotorPower);

    /* 左右モータ駆動パワーの設定 */
    setDriveParam(leftMotorPower, rightMotorPower);
}

/**
 * ステアリング操舵量の計算をする
 * @return ステアリング操舵量
 */
double LineWalker::steeringAmountCalculation(double brightness) {

    double targetBrightness;  // 目標輝度値
    double diffBrightness;    // 目標輝度との差分値
    double steeringAmount;    // ステアリング操舵量

    /* 目標輝度値の計算 */
    targetBrightness = (mWhilteBrightness - mBlackBrightness) / 2;

    /* 目標輝度値と反射光の強さの差分を計算 */
    diffBrightness = brightness - targetBrightness;

    /* ステアリング操舵量を計算 */
    steeringAmount = diffBrightness * mSteeringCoef + mDifferentialCoef * (diffBrightness - mPrevDiffBrightness);
    printf(" meas: %f tgt: %f steer: %f difdif: %f\n",
            brightness, targetBrightness, steeringAmount, diffBrightness-mPrevDiffBrightness);

    /* 今回の差分を格納 */
    mPrevDiffBrightness = diffBrightness;

    return steeringAmount;
}