/******************************************************************************
 *  ScenarioReader.cpp (for LEGO Mindstorms EV3)
 *  Copyright (c) 2023 Emtechs Inc.
 *****************************************************************************/

#include "ScenarioReader.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include "mjson.h"

//struct WalkerParam {
//  char key[32];
//  double value;
//};

struct ScenarioReader::Context {
  int scenesNum;
  Scene* scenes;
  Context() : scenesNum(), scenes() {}
};

int ScenarioReader::get_num_params(const char* params, int len) {
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

WalkerParams ScenarioReader::parse_to_params(const char* params, int len, int num) {
  WalkerParams result;
  int koff, klen, voff, vlen, vtype, off;
  result.reserve(num);
  for (off = 0; (off = mjson_next(params, len, off, &koff, &klen,
                                  &voff, &vlen, &vtype)) != 0;) {
    if (vtype == MJSON_TOK_NUMBER) {
      //printf("  key: %.*s, value: %.*s\n", klen, params + koff, vlen, params + voff);
      char value[32];
      snprintf(value, sizeof(value), "%.*s", vlen, params + voff);
      result.add(params + koff, klen, atof(value));
    }
  }
  return result;
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
          int num = get_num_params(s1, n1);
          if (num > 0) {
            p[i].params = parse_to_params(s1, n1, num);
          }
          // printf("  num_params: %d\n", num);
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
    free(setting);
  }
}

ScenarioReader::~ScenarioReader() {
  // mContext->scens[i].params
  free(mContext->scenes);
  delete mContext;
}