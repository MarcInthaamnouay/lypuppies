#include <node_api.h>
#include <string.h>
#include <stdlib.h>
#include "util.h"
#include "dog.h"

#define DECLARE_NAPI_METHOD(name, func) { name, 0, func, 0, 0, 0, napi_default, 0 }

static napi_value getDogJSObj(napi_env env, Dog * dog) {
  napi_status status;
  napi_value jsDogObj;

  status = napi_create_object(env, &jsDogObj);

  if (dog == NULL) {
    return jsDogObj;
  }

  napi_value name;
  napi_value type;
  napi_value alias;
  napi_value age;

  // @TODO simplify this...
  char * strDogType = getStrTypeFromType(dog->type);
  status = napi_create_string_utf8(env, strDogType, strlen(strDogType), &type);
  if (status != napi_ok) napi_throw_error(env, NULL, "Unable to create type str");

  status = napi_create_string_utf8(env, dog->name, strlen(dog->name), &name);
  if (status != napi_ok) napi_throw_error(env, NULL, "Unable to create name str");
  
  status = napi_create_string_utf8(env, dog->alias, strlen(dog->alias), &alias);
  if (status != napi_ok) napi_throw_error(env, NULL, "Unable to create alias str");
  
  status = napi_create_uint32(env, dog->age, &age);
  if (status != napi_ok) napi_throw_error(env, NULL, "Unable to create age uint");
  
  status = napi_set_named_property(env, jsDogObj, "type", type);
  if (status != napi_ok)
    napi_throw_error(env, NULL, "Unable to set dog's type");

  status = napi_set_named_property(env, jsDogObj, "name", name);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to set dog's name");
  }

  status = napi_set_named_property(env, jsDogObj, "alias", alias);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to set dog's alias");
  }

  status = napi_set_named_property(env, jsDogObj, "age", age);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to set dog's age");
  }

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
  
  free(name);
  free(type);

  return getDogJSObj(env, dog); 
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
