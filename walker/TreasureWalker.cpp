/******************************************************************************
 *  TreasureWalker.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2023/07/22
 *  Implementation of the Class TreasureWalker
 *  Author: Risei Kodo
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "TreasureWalker.h"

// 定数宣言
static const double RIGHT_EDGE  = 1.0;      // 左エッジ
static const double LEFT_EDGE   = -1.0;     // 右エッジ
static const double WHITE_BRIGHTNESS  = 100.0;      // カラーセンサの輝度設定用
static const double BLACK_BRIGHTNESS  = 0.0;      // カラーセンサの輝度設定用
static const double STEERING_COEF  = 0.5;      // ステアリング操舵量の係数
static const double DIFFERENTIAL_COEF = 0.08;   // D制御の係数
static const double INTEGRAL_COEF = 0.0;       // I制御の係数
static const double BASE_SPEED  = 50.0;      // 走行標準スピード

/**
 * コンストラクタ
 * @param armMotor  アームモータ
 */
TreasureWalker::TreasureWalker(ev3api::Motor& armMotor)
    : mArmMotor(armMotor) {
        TreasureWalker::reset();
}

TreasureWalker::~TreasureWalker() {}

const char* TreasureWalker::getClassName() const { return "TreasureWalker"; }

/* 未実装 */
void TreasureWalker::reset() {
    int32_t angle;
    int32_t prevAngle = 0;
    int i = 0;
    mArmMotor.setPWM(-30);
    while (i < 5) {
        angle = mArmMotor.getCount();
        if (angle == prevAngle) {
            i++;
        } else {
            i = 0;
        }
        prevAngle = angle;
    }
    mArmMotor.stop();
    mArmMotor.reset();
}

bool TreasureWalker::execute() {
    double angle = (float)mArmMotor.getCount();
    // printf("angle=%f\n", angle);
    if (angle < 20) {
        mArmMotor.setPWM(30);
    } else {
        mArmMotor.stop();
    }

    return true;
}

Control TreasureWalker::get() { return Control(0.0, 0.0); }