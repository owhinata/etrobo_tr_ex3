/******************************************************************************
 *  WalkerParams.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "WalkerParams.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct WalkerParam {
  char key[32];
  double value;
};

WalkerParams::WalkerParams() : mParams(), mParamsNum() {}

void WalkerParams::reserve(int num) {
  if (WalkerParam* p = (WalkerParam*)calloc(num, sizeof(WalkerParam))) {
    if (mParamsNum > 0 && mParams) {
      if (mParamsNum > num) {
        memcpy(p, mParams, num * sizeof(WalkerParam));
        mParamsNum = num;
      } else {
        memcpy(p, mParams, mParamsNum * sizeof(WalkerParam));
      }
      free(mParams);
    }
    mParams = p;
    mParamsCapacity = num;
  }
}

bool WalkerParams::get(const char* key, int keyLength, double* value) const {
  for (int i = 0; i < mParamsNum; ++i) {
    unsigned len = strnlen(mParams[i].key, 32);
    if (strnlen(key, keyLength) == len && memcmp(mParams[i].key, key, len) == 0) {
      *value = mParams[i].value;
      return true;
    }
  }
  return false;
}

void WalkerParams::add(const char* key, int keyLength, double value) {
  printf(" * key: %.*s val: %f\n", keyLength, key, value);
  if (mParamsNum < mParamsCapacity) {
    int limit = sizeof(mParams[mParamsNum].key);
    memset(mParams[mParamsNum].key, 0, limit);
    int len = keyLength > limit ? limit : keyLength;
    strncpy(mParams[mParamsNum].key, key, len);
    mParams[mParamsNum++].value = value;
  }
}