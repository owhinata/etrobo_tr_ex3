/******************************************************************************
 *  WalkerParams.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_APP_WALKER_PARAMS_H_
#define EV3_APP_WALKER_PARAMS_H_

struct WalkerParam;

class WalkerParams {
public:
  WalkerParams();

  bool get(const char* key, int keyLength, double* value) const;

private:
  void reserve(int num);
  void add(const char* key, int keyLength, double value);

  WalkerParam* mParams;
  int mParamsNum;
  int mParamsCapacity;

  friend class ScenarioReader;
};

#endif  // EV3_UNIT_WALKER_PARAMS_H_