#include <node_api.h>
#include <string.h>
#include <stdlib.h>
#include "puppy.h"
#include "util.h"
#include "dog.h"

#define DECLARE_NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }

static void assignJSObj(napi_value * jsObj, PuppyType t, char * type, void * ptr, napi_env env) {
  napi_status status;
  napi_value value;

  if (t == number) {
    uint8_t v = *(uint8_t *) ptr;
    status = napi_create_uint32(env, v, &value);
  } else if (t == string) {
    char * s = (char *) ptr;
    status = napi_create_string_utf8(env, s, strlen(s), &value);
  } else {
    return;
  }
  
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create type");
  }

  status = napi_set_named_property(env, *jsObj, type, value);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to assign value");
  }
}

static napi_value getDogJSObj(napi_env env, Dog * dog) {
  napi_status status;
  napi_value jsDogObj;

  status = napi_create_object(env, &jsDogObj);

  if (dog == NULL) {
    return jsDogObj;
  }

  char * strDogType = getStrTypeFromType(dog->type);

  assignJSObj(&jsDogObj, string, "type", strDogType, env);
  assignJSObj(&jsDogObj, string, "name", dog->name, env);
  assignJSObj(&jsDogObj, string, "alias", dog->alias, env);
  assignJSObj(&jsDogObj, number, "age", &dog->age, env);

  free(dog);

  return jsDogObj;
}

napi_value GenerateUniquePuppy(napi_env env, napi_callback_info info) {
  const size_t charLen = 1024;
  napi_status status;
  size_t argc = 2;
  napi_value argv[2];

  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to retrieve argument from method");
  }

  char * name = malloc(sizeof(char) * 1024);
  size_t nameLen;
  status = napi_get_value_string_utf8(env, argv[0], name, charLen, &nameLen);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to parse the name");
  }

  char * type = malloc(sizeof(char) * 1024);
  size_t typeLen;
  status = napi_get_value_string_utf8(env, argv[1], type, charLen, &typeLen);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create a new JS object");
  }

  Type t = getTypeFromStr(type);
  Dog * dog = generateUniquePuppy(name, t);
  
  napi_value doggie = getDogJSObj(env, dog); 
  free(name);
  free(type);

  return doggie;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  // define method
  napi_property_descriptor desc = DECLARE_NAPI_METHOD("GenerateUniquePuppy", GenerateUniquePuppy);
  status = napi_define_properties(env, exports, 1, &desc);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create binding");
  }

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
