/******************************************************************************
 *  ScenarioParams.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_APP_SCENARIO_PARAMS_H_
#define EV3_APP_SCENARIO_PARAMS_H_

class ScenarioParams {
public:
  ScenarioParams();
  ~ScenarioParams();

  bool get(const char* key, double* value) const;

  void reserve(int num);
  void add(const char* key, double value);

private:
  void* mParams;
  int mParamsNum;
  int mParamsCapacity;

  ScenarioParams(const ScenarioParams&);
  ScenarioParams& operator=(const ScenarioParams&);
};

#endif  // EV3_APP_SCENARIO_PARAMS_H_