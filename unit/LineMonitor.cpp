/******************************************************************************
 *  LineMonitor.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Definition of the Class LineMonitor
 *  Author: Kazuhiro Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "LineMonitor.h"

// 定数宣言
const int8_t LineMonitor::INITIAL_THRESHOLD = 20;  // 黒色の光センサ値

/**
 * コンストラクタ
 * @param colorSensor カラーセンサ
 */
LineMonitor::LineMonitor(const ev3api::ColorSensor& colorSensor)
    : mColorSensor(colorSensor),
      mThreshold(INITIAL_THRESHOLD) {
}

/**
 * ライン上か否かを判定する
 * @retval true  ライン上
 * @retval false ライン外
 */
//bool LineMonitor::isOnLine() const {
//    // 光センサからの取得値を見て
//    // 黒以上であれば「true」を、
//    // そうでなければ「false」を返す
//    if (mColorSensor.getBrightness() >= mThreshold) {
//        return true;
//    } else {
//        return false;
//    }
//}

/**
 * ライン閾値を設定する
 * @param threshold ライン閾値
 */
//void LineMonitor::setThreshold(int8_t threshold) {
//    mThreshold = threshold;
//}

/**
 * カラーセンサから反射光の強さを取得する
 * @return 反射光の強さ（0-100）
 */
int LineMonitor::getBrightness() const {
    rgb_raw_t rgb;
    mColorSensor.getRawColor(rgb);
    return double(rgb.r + rgb.g + rgb.b) / 3.0;
}
