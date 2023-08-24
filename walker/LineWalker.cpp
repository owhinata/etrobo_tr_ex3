/******************************************************************************
 *  LineWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Implementation of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "LineWalker.h"

// 定数宣言
static const double RIGHT_EDGE  = 1.0;      // 左エッジ
static const double LEFT_EDGE   = -1.0;     // 右エッジ
static const double WHITE_BRIGHTNESS  = 140.0;      // カラーセンサの輝度設定用
static const double BLACK_BRIGHTNESS  = 10.0;      // カラーセンサの輝度設定用
static const double STEERING_COEF  = 0.3;      // ステアリング操舵量の係数
static const double DIFFERENTIAL_COEF = 0.08;   // D制御の係数
static const double INTEGRAL_COEF = 0.25;       // I制御の係数
static const double BASE_SPEED  = 30.0;      // 走行標準スピード

/**
 * コンストラクタ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 */
LineWalker::LineWalker(Uptime* uptime, LineMonitor* lineMonitor)
    : mUptime(uptime),
      mLineMonitor(lineMonitor),
      mEdge(LEFT_EDGE),
      mWhilteBrightness(WHITE_BRIGHTNESS),
      mBlackBrightness(BLACK_BRIGHTNESS),
      mSteeringCoef(STEERING_COEF),
      mDifferentialCoef(DIFFERENTIAL_COEF),
      mIntegralCoef(INTEGRAL_COEF),
      mPrevDiffBrightness(50.0),
      mBaseSpeed(BASE_SPEED),
      mSteeringAmount(0.0) {
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
      mDifferentialCoef = GET("kd", double, DIFFERENTIAL_COEF);
      mIntegralCoef = GET("ki", double, INTEGRAL_COEF);
      mPrevDiffBrightness = 50.0;
      mPrevTime = mUptime->getUptime();
      mIntegral = 0.0;
      mBaseSpeed = GET("speed", double, BASE_SPEED);
      printf("  edge:  %f\n"
             "  white: %f\n"
             "  black: %f\n"
             "  kp:    %f\n"
             "  kd:    %f\n"
             "  ki:    %f\n"
             "  speed: %f\n",
             mEdge, mWhilteBrightness, mBlackBrightness,
             mSteeringCoef, mDifferentialCoef, mIntegralCoef,
             mBaseSpeed);
}

bool LineWalker::execute() {
    double targetBrightness;  // 目標輝度値
    double diffBrightness;    // 目標輝度との差分値
    double p, i, d;           // PIDの各計算値
    
    double now = mUptime->getUptime();    // 起動時間取得
    double duration = now - mPrevTime;   // 処理周期を計算
    mPrevTime = now;
    // printf("duration: %f\n", duration);

    // 反射光の強さを取得する
    double brightness = mLineMonitor->getBrightness();

    /* 目標輝度値の計算 */
    targetBrightness = (mWhilteBrightness - mBlackBrightness) / 2;

    /* 目標輝度値と反射光の強さの差分を計算 */
    diffBrightness = targetBrightness - brightness;

    /* 積分を求める */
    mIntegral += (diffBrightness + mPrevDiffBrightness) * duration / 2;
    // printf("Integral: %f\n", mIntegral);

    p = diffBrightness * mSteeringCoef;
    if (duration == 0) {
        d = 0;
    } else {
        d = mDifferentialCoef * (diffBrightness - mPrevDiffBrightness) / duration;
    }
    i = mIntegral * mIntegralCoef;

    /* ステアリング操舵量を計算 */
    mSteeringAmount = (p + i + d) * mEdge;
    // printf(" meas: %f tgt: %f steer: %f difdif: %f\n",
    //         brightness, targetBrightness, mSteeringAmount, diffBrightness-mPrevDiffBrightness);

    /* 今回の差分を格納 */
    mPrevDiffBrightness = diffBrightness;

    return true;
}

Control LineWalker::get() { return Control(mBaseSpeed, mSteeringAmount); }