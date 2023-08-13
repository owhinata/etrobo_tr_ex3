/******************************************************************************
 *  ScenarioReader.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "ScenarioReader.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "mjson.h"

struct ScenarioReader::Context {
  int scenesNum;
  Scene* scenes;
  int monitorsNum;
  struct Monitors {
    char klass[32];
    ScenarioParams params;
  } *monitors;
  const ScenarioParams defaultParams;
  Context() : scenesNum(), scenes(), monitorsNum(), monitors() {}
};

static int get_num_params(const char* params, int len) {
  int koff, klen, voff, vlen, vtype, off, num = 0;
  for (off = 0; (off = mjson_next(params, len, off, &koff, &klen,
                                  &voff, &vlen, &vtype)) != 0;) {
    // printf("  key: %.*s, value: %.*s\n", klen, params + koff, vlen, params + voff);
    if (vtype == MJSON_TOK_NUMBER) {
      ++num;
    }
  }
  return num;
}

static void parse_to_params(const char* json, int len, ScenarioParams& params) {
  int koff, klen, voff, vlen, vtype, off;
  for (off = 0; (off = mjson_next(json, len, off, &koff, &klen,
                                  &voff, &vlen, &vtype)) != 0;) {
    if (vtype == MJSON_TOK_NUMBER) {
      // printf("  key: %.*s, value: %.*s\n",
      //        klen, json + koff, vlen, json + voff);
      char key[32], value[32];
      snprintf(key, sizeof(key), "%.*s", klen, json + koff);
      snprintf(value, sizeof(value), "%.*s", vlen, json + voff);
      params.add(key, atof(value));
    }
  }
}

int ScenarioReader::get_num_scene(const char* scenario) {
  for (int i = 0;; ++i) {
    char path[8];
    snprintf(path, sizeof(path), "$[%d]", i);
    const char* s; int n;
    char klass[32];
    if (mjson_find(scenario, strlen(scenario), path, &s, &n) == MJSON_TOK_OBJECT &&
        mjson_get_string(s, n, "$.class", klass, sizeof(klass)) >= 0) {
      continue;
    }
    return i;
  }
  return 0;
}

Scene* ScenarioReader::parse_to_scenes(const char* scenario, int num) {
  if (Scene* p = (Scene*)calloc(num, sizeof(Scene))) {
    for (int i = 0; i < num; ++i) {
      char path[8];
      snprintf(path, sizeof(path), "$[%d]", i);
      const char *s, *s1; int n, n1;
      if (mjson_find(scenario, strlen(scenario), path, &s, &n) == MJSON_TOK_OBJECT &&
          mjson_get_string(s, n, "$.class", p[i].klass, sizeof(p[i].klass)) >= 0) {
        printf("class: %s\n", p[i].klass);
        if (mjson_find(s, n, "$.params", &s1, &n1) == MJSON_TOK_OBJECT) {
          p[i].params.reserve(get_num_params(s1, n1));
          parse_to_params(s1, n1, p[i].params);
        }
        double length;
        if (mjson_get_number(s, n, "$.runLength", &length)) {
          p[i].runLength = length;
        }        
      }
    }
    return p;
  }
  return NULL;
}

static long fsize(FILE* fp) {
  if (fseek(fp, 0L, SEEK_END) == 0) {
    long pos = ftell(fp);
    rewind(fp);
    return pos;
  }
  return 0;
}

static char* read_setting() {
  char* ret = 0;
  FILE* fp = fopen("scenario.json", "r");
  if (fp) {
    long sz = fsize(fp) + 1;
    if (void* p = calloc(1, sz)) {
      fread(p, sz, 1, fp);
      ret = (char*)p;
    }
    fclose(fp);
  } else {
    printf("Error: fopen(scenario.json) = %d\n", errno);
  }
  return ret;
}

static char* parse_to_scenario(const char* setting) {
  char key[24];
  double no = mjson_get_number(setting, strlen(setting), "$.no", &no) ? no : 0;
  snprintf(key, sizeof(key), "$.course[%d]", int(no));
  char name[16] = {};
  const char *s = 0, *s1 = 0; int n = 0, n1 = 0;
  if (mjson_find(setting, strlen(setting), key, &s, &n) == MJSON_TOK_OBJECT &&
      mjson_get_string(s, n, "$.name", name, sizeof(name)) >= 0 &&
      mjson_find(s, n, "$.scenario", &s1, &n1) == MJSON_TOK_ARRAY) {
    printf("**** %s ****\n", name);
    return strndup(s1, n1);
  }
  printf("**** NO COURSE AVAILABLE (no=%d) ****\n", int(no));
  printf(" * %s: %.*s\n", key, n, s);
  printf(" * $.name: %s\n", name);
  printf(" * $.scenario: %.*s\n", n1, s1);
  return 0;
}

static int get_array_num(const char* json, int json_len, const char* key) {
  const char *s = 0, *s1 = 0; int n = 0, n1 = 0, i = 0;
  char elem[16];
  if (mjson_find(json, json_len, key, &s, &n) == MJSON_TOK_ARRAY) {
    for (i = 0;; ++i) {
      snprintf(elem, sizeof(elem), "$[%d]", i);
      if (mjson_find(s, n, elem, &s1, &n1) <= 0) {
        return i;
      }
    }
  }
  return 0;
}

void ScenarioReader::parse_to_monitors(const char* setting, Context* ctx) {
  ctx->monitorsNum = get_array_num(setting, strlen(setting), "$.monitors");
  // printf("monitorsNum=%d\n", ctx->monitorsNum);
  if (ctx->monitorsNum <= 0) return;

  ctx->monitors =
      (Context::Monitors*)calloc(ctx->monitorsNum, sizeof(*ctx->monitors));
  if (ctx->monitors == 0) {
    printf("Error: Fail to parse_to_monitors\n");
    ctx->monitorsNum = 0;
    return;
  }

  for (int i = 0; i < ctx->monitorsNum; ++i) {
    char elem[24];
    const char *s = 0, *s1 = 0; int n = 0, n1 = 0;
    snprintf(elem, sizeof(elem), "$.monitors[%d]", i);
    if (mjson_find(setting, strlen(setting), elem, &s, &n)
        != MJSON_TOK_OBJECT) {
      printf("Error: %s is not json object\n", elem);
    } else if (mjson_get_string(s, n, "$.class",
                                ctx->monitors[i].klass,
                                sizeof(ctx->monitors[i].klass)) <= 0) {
      printf("Error: %s is not include class element\n", elem);
    } else {
      printf("class %s\n", ctx->monitors[i].klass);
      if (mjson_find(s, n, "$.params", &s1, &n1) == MJSON_TOK_OBJECT) {
        ctx->monitors[i].params.reserve(get_num_params(s1, n1));
        parse_to_params(s1, n1, ctx->monitors[i].params);
      }
    }
  }
}

ScenarioReader::ScenarioReader() : mContext(new Context) {
  if (char* setting = read_setting()) {
    if (char* scenario = parse_to_scenario(setting)) {
      // printf("%s\n", scenario);
      int num = get_num_scene(scenario);
      if (num > 0 && (mContext->scenes = parse_to_scenes(scenario, num))) {
        mContext->scenesNum = num;
      } else {
        printf("**** NO SCENE AVAILABLE\n");
      }
      free(scenario);
    }
    parse_to_monitors(setting, mContext);
    free(setting);
  }
}

ScenarioReader::~ScenarioReader() {
  // mContext->scens[i].params
  free(mContext->scenes);
  delete mContext;
}

const ScenarioParams& ScenarioReader::getMonitorParams(const char* name) const {
  for (int i = 0; i < mContext->monitorsNum; ++i) {
    if (strcmp(mContext->monitors[i].klass, name) == 0) {
      return mContext->monitors[i].params;
    }
  }
  return mContext->defaultParams;
}