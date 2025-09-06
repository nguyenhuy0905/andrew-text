#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum DebugLogType {
    INFO,
    ERROR,
    WARN,
};

/**
 * This should be thread-safe.
 */
int debug_log(enum DebugLogType type, const char *fmt, ...);

/**
 * \brief This function holds a mutex basically.
 */
[[noreturn]] void thread_safe_exit(int retcode);

#ifdef __cplusplus
}
#endif
