/******************************************************************************
 *  ScenarioReader.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_UNIT_SCENARIO_READER_H_
#define EV3_UNIT_SCENARIO_READER_H_

#include "WalkerParams.h"

struct Scene {
  char klass[32];
  WalkerParams params;
  double runLength;
};

class ScenarioReader {
public:
  ScenarioReader();
  ~ScenarioReader();

private:
  struct Context;
  Context* mContext;

  // TODO: Refactoring
  int get_num_params(const char* params, int len);
  WalkerParams parse_to_params(const char* params, int len, int num);
  int get_num_scene(const char* scenario);
  Scene* parse_to_scenes(const char* scenario, int num);

  ScenarioReader(const ScenarioReader&);
  ScenarioReader& operator=(const ScenarioReader&);
};

#endif // EV3_UNIT_SCENARIO_READER_H_