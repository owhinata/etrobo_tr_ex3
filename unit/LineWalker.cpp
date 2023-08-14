/******************************************************************************
 *  LineWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Implementation of the Class LineWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "LineWalker.h"
#include "Walker.h"

#include "ev3api.h"

// 定数宣言
const int LineWalker::RIGHT_EDGE  = 1;      // 左エッジ
const int LineWalker::LEFT_EDGE   = -1;     // 右エッジ
const int LineWalker::WHITE_BRIGHTNESS  = 140;      // カラーセンサの輝度設定用
const int LineWalker::BLACK_BRIGHTNESS  = 10;      // カラーセンサの輝度設定用
const float LineWalker::STEERING_COEF  = 0.3;      // ステアリング操舵量の係数
const int LineWalker::BASE_SPEED  = 30;      // 走行標準スピード

/**
 * コンストラクタ
 * @param leftWheel  左モータ
 * @param rightWheel 右モータ
 */
LineWalker::LineWalker(Cockpit* cockpit)
    : Walker(cockpit),
      mEdge(LEFT_EDGE),
      mIsInitialized(false) {
}

LineWalker::~LineWalker() {}

const char* LineWalker::getClassName() const { return "LineWalker"; }

/**
 * 走行する
 */
void LineWalker::run() {
    if (mIsInitialized == false) {
        this->init();
        mIsInitialized = true;
    }

    // 反射光の強さを取得する
    this->setCommand();

    // 走行を行う
    int16_t steeringAmount = this->steeringAmountCalculation();
    int leftMotorPower, rightMotorPower;  // 左右モータ設定パワー

    /* 左右モータ駆動パワーの計算 */
    leftMotorPower = (int)(BASE_SPEED + (steeringAmount * mEdge));
    rightMotorPower = (int)(BASE_SPEED - (steeringAmount * mEdge));

    /* 左右モータ駆動パワーの設定 */
    setDriveParam(leftMotorPower, rightMotorPower);
}

/**
 * 走行に必要なものをリセットする
 */
void LineWalker::init() {
    // モータをリセットする
    // mLeftWheel.reset();
    // mRightWheel.reset();
}

/**
 * 反射光の強さを設定する
 * @param brightness 反射光の強さ
 */
void LineWalker::setCommand() {
    mBrightness = (int)getBrightness();
}

/**
 * ステアリング操舵量の計算をする
 * @return ステアリング操舵量
 */
int16_t LineWalker::steeringAmountCalculation() {

    int targetBrightness;      // 目標輝度値
    float32_t diffBrightness;  // 目標輝度との差分値
    int16_t steeringAmount;    // ステアリング操舵量

    /* 目標輝度値の計算 */
    targetBrightness = (WHITE_BRIGHTNESS - BLACK_BRIGHTNESS) / 2;

    /* 目標輝度値と反射光の強さの差分を計算 */
    diffBrightness = (float32_t)(targetBrightness - mBrightness);
    //printf("mBrightness=%d\n", mBrightness);

    /* ステアリング操舵量を計算 */
    steeringAmount = (int16_t)(diffBrightness * STEERING_COEF);

    return steeringAmount;
}