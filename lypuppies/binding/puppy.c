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
  napi_status status;
  size_t argc = 2;
  napi_value argv[2];
  Type t;

  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to retrieve argument from method");
  }

  char * name = malloc(sizeof(char) * 1024);
  size_t nameLen;
  status = napi_get_value_string_utf8(env, argv[0], name, charLen, &nameLen);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to parse dog name. Check name param");
  }

  char * type = malloc(sizeof(char) * 1024);
  size_t typeLen;
  status = napi_get_value_string_utf8(env, argv[1], type, charLen, &typeLen);

  if (status != napi_ok) {
    t = chihuaha;
  } else {
    t = getTypeFromStr(type);
  }

  Dog * dog = generateUniquePuppy(name, t);
  
  napi_value doggie = getDogJSObj(env, dog); 
  free(name);
  free(type);

  return doggie;
}

napi_value PuppyBark(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value argv[1];

  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  if (status != napi_ok) {
    return NULL;
  }

  napi_value name;
  napi_value age;
  napi_value undefined;

  napi_get_undefined(env, &undefined);

  status = napi_get_named_property(env, argv[0], "name", &name);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to retrieve name");
  }

  status = napi_get_named_property(env, argv[0], "age", &age);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to retrieve type");
  }

  char * nameStr = malloc(sizeof(char) * 1024);
  size_t nameLen;
  napi_get_value_string_utf8(env, name, nameStr, charLen, &nameLen);
  uint32_t ageValue;
  napi_get_value_uint32(env, age, &ageValue);

  puppyBark(nameStr, (uint8_t) ageValue);

  return undefined;
}

napi_value GetPuppyExpectedLife(napi_env env, napi_callback_info info) {
  napi_status status;
  size_t argc = 1;
  napi_value argv[1];

  napi_value typeStr;
  napi_value jsAge;

  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to retrieve params");
  }

  status = napi_get_named_property(env, argv[0], "type", &typeStr);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to retrieve type of dog");
  }

  char * type = malloc(sizeof(char) * 1024);
  size_t typeLen;
  status = napi_get_value_string_utf8(env, typeStr, type, charLen, &typeLen);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to retrieve the type of the dog from napi value");
  }

  Type t = getTypeFromStr(type);
  uint8_t maxAge = getDogLifeMedianExpectancy(t);

  napi_create_uint32(env, maxAge, &jsAge);
  return jsAge;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  // define method
  napi_property_descriptor desc[] = {
    DECLARE_NAPI_METHOD("GenerateUniquePuppy", GenerateUniquePuppy),
    DECLARE_NAPI_METHOD("PuppyBark", PuppyBark),
    DECLARE_NAPI_METHOD("GetPuppyExpectedLife", GetPuppyExpectedLife)
  };

  status = napi_define_properties(env, exports, sizeof(desc) / sizeof(*desc), desc);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to create binding");
  }


  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);
