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
  struct Scenes {
    char klass[32];
    ScenarioParams params;
    struct Detector {
      char klass[32];
      ScenarioParams params;
      Detector() : params() { memset(klass, 0, sizeof(klass)); }
    } detector;
    Scenes() : params(), detector() { memset(klass, 0, sizeof(klass)); }
  } *scenes;

  int monitorsNum;
  struct Monitors {
    char klass[32];
    ScenarioParams params;
    Monitors() : params() { memset(klass, 0, sizeof(klass)); }
  } *monitors;

  const ScenarioParams defaultParams;

  Context() : scenesNum(), scenes(), monitorsNum(), monitors() {}
  ~Context() {
    delete[] scenes;
    delete[] monitors;
  }
};

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

static void parse_params(const char* json, int len, ScenarioParams& params) {
  int koff, klen, voff, vlen, vtype, off;
  for (off = 0; (off = mjson_next(json, len, off, &koff, &klen,
                                  &voff, &vlen, &vtype)) != 0;) {
    if (vtype == MJSON_TOK_NUMBER) {
      // printf("  key: %.*s, value: %.*s\n",
      //        klen, json + koff, vlen, json + voff);
      char key[32], value[32];
      snprintf(key, sizeof(key), "%.*s", klen - 2, json + koff + 1);
      snprintf(value, sizeof(value), "%.*s", vlen, json + voff);
      params.add(key, atof(value));
    }
  }
}

static char* select_course_json(const char* setting) {
  char key[24];
  double no = mjson_get_number(setting, strlen(setting), "$.no", &no) ? no : 0;
  snprintf(key, sizeof(key), "$.courses[%d]", int(no));
  char name[16] = {};
  const char *s = 0, *s1 = 0; int n = 0, n1 = 0;
  if (mjson_find(setting, strlen(setting), key, &s, &n) != MJSON_TOK_OBJECT) {
    printf("**** NO COURSE AVAILABLE (no=%d) ****\n", int(no));
    printf(" * %s is not json object\n", key);
  } else if (mjson_get_string(s, n, "$.name", name, sizeof(name)) <= 0) {
    printf("**** NO COURSE AVAILABLE (no=%d) ****\n", int(no));
    printf(" * %s.name is not json string\n", key);
  } else if (mjson_find(s, n, "$.scenes", &s1, &n1) != MJSON_TOK_ARRAY) {
    printf("**** NO COURSE AVAILABLE (no=%d) ****\n", int(no));
    printf(" * %s.scenes is not json arry\n", key);
  } else {
    printf("**** %s ****\n", name);
    return strndup(s1, n1);
  }
  return 0;
}

void ScenarioReader::parse_scenes(const char* course, Context* ctx) {
  ctx->scenesNum = get_array_num(course, strlen(course), "$");
  // printf("scenesNum=%d\n", ctx->scenesNum);
  if (ctx->scenesNum <= 0) return;
  ctx->scenes = new Context::Scenes[ctx->scenesNum];

  for (int i = 0; i < ctx->scenesNum; ++i) {
    char elem[24];
    const char *s = 0, *s1 = 0, *s2 = 0; int n = 0, n1 = 0, n2 = 0;
    snprintf(elem, sizeof(elem), "$[%d]", i);
    Context::Scenes* p = ctx->scenes;
    if (mjson_find(course, strlen(course), elem, &s, &n) != MJSON_TOK_OBJECT) {
      printf(" * $.scenes[%d] is not json object\n", i);
    } else if (mjson_get_string(s, n, "$.class", p[i].klass, sizeof(p[i].klass)) <= 0) {
      printf(" * $.scenes[%d].class is not json string", i);
    } else {
      printf("$.scenes[%d].class %s\n", i, p[i].klass);
      if (mjson_find(s, n, "$.params", &s1, &n1) == MJSON_TOK_OBJECT) {
        p[i].params.reserve(get_num_params(s1, n1));
        parse_params(s1, n1, p[i].params);
      }
      if (mjson_find(s,n, "$.detector", &s1, &n1) == MJSON_TOK_OBJECT &&
          mjson_get_string(s1, n1, "$.class", p[i].detector.klass,
                           sizeof(p[i].detector.klass)) > 0) {
        printf("$.scenes[%d].detector.class %s\n", i, p[i].detector.klass);
        if (mjson_find(s1, n1, "$.params", &s2, &n2) == MJSON_TOK_OBJECT) {
          p[i].detector.params.reserve(get_num_params(s2, n2));
          parse_params(s2, n2, p[i].detector.params);
        }
      }
    }
  }
}

void ScenarioReader::parse_monitors(const char* setting, Context* ctx) {
  ctx->monitorsNum = get_array_num(setting, strlen(setting), "$.monitors");
  // printf("monitorsNum=%d\n", ctx->monitorsNum);
  if (ctx->monitorsNum <= 0) return;
  ctx->monitors = new Context::Monitors[ctx->monitorsNum];

  for (int i = 0; i < ctx->monitorsNum; ++i) {
    char elem[24];
    const char *s = 0, *s1 = 0; int n = 0, n1 = 0;
    snprintf(elem, sizeof(elem), "$.monitors[%d]", i);
    Context::Monitors* p = ctx->monitors;
    if (mjson_find(setting, strlen(setting), elem, &s, &n) != MJSON_TOK_OBJECT) {
      printf(" * %s is not json object\n", elem);
    } else if (mjson_get_string(s, n, "$.class", p[i].klass, sizeof(p[i].klass)) <= 0) {
      printf(" * %s.class is not found\n", elem);
    } else {
      printf("%s.class %s\n", elem, p[i].klass);
      if (mjson_find(s, n, "$.params", &s1, &n1) == MJSON_TOK_OBJECT) {
        p[i].params.reserve(get_num_params(s1, n1));
        parse_params(s1, n1, p[i].params);
      }
    }
  }
}

static long fsize(FILE* fp) {
  if (fseek(fp, 0L, SEEK_END) == 0) {
    long pos = ftell(fp);
    rewind(fp);
    return pos;
  }
  return 0;
}

static char* read_setting(const char* file) {
  char* ret = 0;
  FILE* fp = fopen(file, "r");
  if (fp) {
    long sz = fsize(fp) + 1;
    if (void* p = calloc(1, sz)) {
      fread(p, sz, 1, fp);
      ret = (char*)p;
    }
    fclose(fp);
  } else {
    printf("Error: fopen(%s) = %d\n", file, errno);
  }
  return ret;
}

ScenarioReader::ScenarioReader(const char* file) : mContext(new Context) {
  if (char* setting = read_setting(file)) {
    if (char* course = select_course_json(setting)) {
      // printf("%s\n", course);
      parse_scenes(course, mContext);
      free(course);
    }
    parse_monitors(setting, mContext);
    free(setting);
  }
}

ScenarioReader::~ScenarioReader() { delete mContext; }

const ScenarioParams& ScenarioReader::getMonitorParams(const char* name) const {
  for (int i = 0; i < mContext->monitorsNum; ++i) {
    if (strcmp(mContext->monitors[i].klass, name) == 0) {
      return mContext->monitors[i].params;
    }
  }
  return mContext->defaultParams;
}

const char* ScenarioReader::getSceneWalker(int index) const {
  if (index >= 0 && index < mContext->scenesNum) {
    return mContext->scenes[index].klass;
  }
  return 0;
}

const ScenarioParams& ScenarioReader::getSceneWalkerParams(int index) const {
  if (index >= 0 && index < mContext->scenesNum) {
    return mContext->scenes[index].params;
  }
  return mContext->defaultParams;
}

const char* ScenarioReader::getSceneDetector(int index) const {
  if (index >= 0 && index < mContext->scenesNum) {
    return mContext->scenes[index].detector.klass;
  }
  return 0;
}

const ScenarioParams& ScenarioReader::getSceneDetectorParams(int index) const {
  if (index >= 0 && index < mContext->scenesNum) {
    return mContext->scenes[index].detector.params;
  }
  return mContext->defaultParams;
}