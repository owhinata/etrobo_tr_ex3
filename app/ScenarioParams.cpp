/******************************************************************************
 *  ScenarioParams.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "ScenarioParams.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct ScenarioParam {
  char key[32];
  double value;
};

ScenarioParams::ScenarioParams() : mParams(), mParamsNum(), mParamsCapacity() {}

ScenarioParams::~ScenarioParams() { free(mParams); }

void ScenarioParams::reserve(int num) {
  if (void* p = calloc(num, sizeof(ScenarioParam))) {
    if (mParamsNum > 0 && mParams) {
      if (mParamsNum > num) {
        memcpy(p, mParams, num * sizeof(ScenarioParam));
        mParamsNum = num;
      } else {
        memcpy(p, mParams, mParamsNum * sizeof(ScenarioParam));
      }
      free(mParams);
    }
    mParams = p;
    mParamsCapacity = num;
  }
}

void ScenarioParams::add(const char* key, double value) {
  printf(" * key: \"%s\" val: %f\n", key, value);
  if (mParamsNum < mParamsCapacity) {
    ScenarioParam* p = (ScenarioParam*)mParams;
    memset(p[mParamsNum].key, 0, sizeof(p[mParamsNum].key));
    strncpy(p[mParamsNum].key, key, sizeof(p[mParamsNum].key) - 1);
    p[mParamsNum++].value = value;
  }
}

bool ScenarioParams::get(const char* key, double* value) const {
  // printf("ScenarioParams::get(\"%s\")> num=%d\n", key, mParamsNum);
  // for (int i = 0; i < mParamsNum; ++i) {
  //   ScenarioParam* p = (ScenarioParam*)mParams;
  //   printf("ScenarioParams::get(\"%s\")> * key: \"%s\" val: %f\n",
  //          key, p[i].key, p[i].value);
  // }
  for (int i = 0; i < mParamsNum; ++i) {
    ScenarioParam* p = (ScenarioParam*)mParams;
    if (strcmp(p[i].key, key) == 0) {
      *value = p[i].value;
      return true;
    }
  }
  return false;
}