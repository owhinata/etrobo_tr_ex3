/******************************************************************************
 *  ScenarioReader.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_UNIT_SCENARIO_READER_H_
#define EV3_UNIT_SCENARIO_READER_H_

#include "ScenarioParams.h"

struct Scene {
  char klass[32];
  ScenarioParams params;
  double runLength;
};

class ScenarioReader {
public:
  ScenarioReader();
  ~ScenarioReader();

  const ScenarioParams& getMonitorParams(const char* name) const;

private:
  struct Context;
  Context* mContext;

  // TODO: Refactoring
  static int get_num_scene(const char* scenario);
  static Scene* parse_to_scenes(const char* scenario, int num);

  static void parse_to_monitors(const char* setting, Context* ctx);

  ScenarioReader(const ScenarioReader&);
  ScenarioReader& operator=(const ScenarioReader&);
};

#endif // EV3_UNIT_SCENARIO_READER_H_