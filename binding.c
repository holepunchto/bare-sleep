#include <assert.h>
#include <bare.h>
#include <errno.h>
#include <js.h>
#include <stdint.h>
#include <uv.h>

#if !defined(_WIN32) && !defined(__FREERTOS__)
#include <time.h>
#endif

static void
bare_sleep__sleep(uint64_t ns) {
#if defined(_WIN32) || defined(__FREERTOS__)
  uv_sleep((unsigned int) ((ns + 999999) / 1000000));
#else
  struct timespec remaining = {
    .tv_sec = (time_t) (ns / 1000000000),
    .tv_nsec = (long) (ns % 1000000000),
  };

  while (nanosleep(&remaining, &remaining) == -1 && errno == EINTR) {
  }
#endif
}

static js_value_t *
bare_sleep(js_env_t *env, js_callback_info_t *info) {
  int err;

  size_t argc = 1;
  js_value_t *argv[1];

  err = js_get_callback_info(env, info, &argc, argv, NULL, NULL);
  assert(err == 0);

  assert(argc == 1);

  uint64_t ns;
  err = js_get_value_bigint_uint64(env, argv[0], &ns, NULL);
  assert(err == 0);

  bare_sleep__sleep(ns);

  return NULL;
}

static void
bare_sleep_typed(js_value_t *receiver, uint64_t ns, js_typed_callback_info_t *info) {
  bare_sleep__sleep(ns);
}

static js_value_t *
bare_sleep_exports(js_env_t *env, js_value_t *exports) {
  int err;

#define V(name, untyped, signature, typed) \
  { \
    js_value_t *val; \
    if (signature) { \
      err = js_create_typed_function(env, name, -1, untyped, signature, typed, NULL, &val); \
      assert(err == 0); \
    } else { \
      err = js_create_function(env, name, -1, untyped, NULL, &val); \
      assert(err == 0); \
    } \
    err = js_set_named_property(env, exports, name, val); \
    assert(err == 0); \
  }

  V(
    "sleep",
    bare_sleep,
    &((js_callback_signature_t){
      .version = 0,
      .result = js_undefined,
      .args_len = 2,
      .args = (int[]){
        js_object,
        js_biguint64,
      },
    }),
    bare_sleep_typed
  );
#undef V

  return exports;
}

BARE_MODULE(bare_sleep, bare_sleep_exports)
