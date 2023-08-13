/******************************************************************************
 *  ScenarioReader.h (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#ifndef EV3_APP_SCENARIO_READER_H_
#define EV3_APP_SCENARIO_READER_H_

#include "ScenarioParams.h"

class ScenarioReader {
public:
  ScenarioReader(const char* file);
  ~ScenarioReader();

  const ScenarioParams& getMonitorParams(const char* name) const;

  const char* getSceneWalker(int index) const;

  const ScenarioParams& getSceneWalkerParams(int index) const;

  const char* getSceneDetector(int index) const;

  const ScenarioParams& getSceneDetectorParams(int index) const;

private:
  ScenarioReader(const ScenarioReader&);
  ScenarioReader& operator=(const ScenarioReader&);

  struct Context;

  static void parse_scenes(const char* course, Context* ctx);
  static void parse_monitors(const char* setting, Context* ctx);

  Context* mContext;
};

#endif // EV3_APP_SCENARIO_READER_H_