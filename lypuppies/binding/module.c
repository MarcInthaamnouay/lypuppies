#include <node_api.h>
#include <stdlib.h>
#include "dog.h"

napi_value SayHello(napi_env env, napi_callback_info info) {
  napi_status status;

  // define the argument for the method
  size_t argc = 1;
  napi_value argv[1];
  status = napi_get_cb_info(env, info, &argc, argv, NULL, NULL);

  char * str = malloc(sizeof(char) * 1024);
  char * yay = "yay"; 
  size_t len;
  status = napi_get_value_string_utf8(env, argv[0], str, 1024, &len);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Invalid argument pass to method SayHello");
  }

  char * newStr = malloc(sizeof(char) * 1024 + 3);
  strcpy(newStr, str);
  strcpy(newStr, yay);

  napi_value strResult;
  status = napi_create_string_utf8(env, newStr, 1027, &strResult);

  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Error while creating new type");
  }

  return strResult;
}

napi_value Init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value func;

  status = napi_create_function(env, NULL, 0, SayHello, NULL, &func);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to wrap a native method");
  }

  status = napi_set_named_property(env, exports, "SayHello", func);
  if (status != napi_ok) {
    napi_throw_error(env, NULL, "Unable to populate exports");
  }

  return exports;
}


NAPI_MODULE(NODE_GYP_MODULE_NAME, Init);

