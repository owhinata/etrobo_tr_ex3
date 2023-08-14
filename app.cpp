/******************************************************************************
 *  app.cpp (for LEGO Mindstorms EV3)
 *  Created on: 2015/01/25
 *  Implementation of the Task main_task
 *  Author: Kazuhiro.Kawachi
 *  Copyright (c) 2015 Embedded Technology Software Design Robot Contest
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "app.h"

#include "ColorSensor.h"
#include "GyroSensor.h"
#include "SonarSensor.h"
#include "TouchSensor.h"
#include "Motor.h"
//#include "Clock.h"

#include "ScenarioWalker.h"
#include "Cockpit.h"
#include "Diagnostics.h"

// デストラクタ問題の回避
// https://github.com/ETrobocon/etroboEV3/wiki/problem_and_coping
// void *__dso_handle=0;

// using宣言
using ev3api::ColorSensor;
using ev3api::GyroSensor;
using ev3api::SonarSensor;
using ev3api::TouchSensor;
using ev3api::Motor;
//using ev3api::Clock;

// Device objects
// オブジェクトを静的に確保する
ColorSensor gColorSensor(PORT_2);
GyroSensor  gGyroSensr(PORT_4);
SonarSensor gSonarSensor(PORT_3);
TouchSensor gTouchSensor(PORT_1);
Motor       gLeftWheel(PORT_C);
Motor       gRightWheel(PORT_B);
//Clock       gClock;

static int diag_exit_;

// オブジェクトの定義
static Diagnostics     *gDiagnostics;
static ScenarioReader  *gScenarioReader;

static LineMonitor     *gLineMonitor;
static Cockpit         *gCockpit;

static Walkers          gWalkers;
static Starter         *gStarter;

static ScenarioWalker  *gScenarioWalker;

/**
 * EV3システム生成
 */
static void user_system_create() {
    // [TODO] タッチセンサの初期化に2msのdelayがあるため、ここで待つ
    tslp_tsk(2U * 1000U);

    // オブジェクトの作成
    gDiagnostics     = new Diagnostics();
    gScenarioReader  = new ScenarioReader();

    gLineMonitor = new LineMonitor(gColorSensor, gDiagnostics);

    Monitor* monitors[] = {
        gLineMonitor,
    };

    gCockpit = new Cockpit(gLineMonitor,
                           gLeftWheel, gRightWheel);

    Walkers walkers = {
        .lineWalker = new LineWalker(gCockpit),
        .sampleWalker = new SampleWalker(gCockpit),
    };
    gWalkers = walkers;

    gStarter = new Starter(gTouchSensor);

    gScenarioWalker = new ScenarioWalker(gScenarioReader,
            monitors, sizeof(monitors) / sizeof(monitors[0]),
            walkers, gStarter);

    // 初期化完了通知
    ev3_led_set_color(LED_ORANGE);
}

/**
 * EV3システム破棄
 */
static void user_system_destroy() {
    gLeftWheel.reset();
    gRightWheel.reset();

    delete gScenarioWalker;
    delete gStarter;
    delete gWalkers.lineWalker;
    delete gWalkers.sampleWalker;
    delete gCockpit;
    delete gLineMonitor;
    delete gScenarioReader;
    delete gDiagnostics;
}

/**
 * メインタスク
 */
void main_task(intptr_t unused) {
    user_system_create();  // センサやモータの初期化処理
    sta_cyc(CYC_TRACER);  // 周期ハンドラ開始
    slp_tsk();  // バックボタンが押されるまで待つ

    // 周期ハンドラ停止
    stp_cyc(CYC_TRACER);

    ++diag_exit_;
    wup_tsk(DIAGNOSTICS_TASK);
    tslp_tsk(10U * 1000U);

    user_system_destroy();  // 終了処理
    ext_tsk();
}

/**
 * ライントレースタスク
 */
void tracer_task(intptr_t exinf) {
    if (ev3_button_is_pressed(BACK_BUTTON)) {
        wup_tsk(MAIN_TASK);  // バックボタン押下
    } else {
        gScenarioWalker->run();  // 走行
        wup_tsk(DIAGNOSTICS_TASK);
    }
    ext_tsk();
}

void diagnostics_task(intptr_t exinf) {
    while (1) {
        slp_tsk();
        gDiagnostics->Commit();
    }
    ext_tsk();
}
