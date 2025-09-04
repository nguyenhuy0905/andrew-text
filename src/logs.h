#pragma once

#ifdef __cplusplus
extern "C" {
#endif

enum DebugLogType {
    INFO,
    ERROR,
    WARN,
};

#if defined(NDEBUG) && !defined(debug_log)
#define debug_log(type, msg, ...) 0
#else
/**
 * Print stuff when NDEBUG is not defined and return the number of characters
 * printed. Otherwise do nothing and return 0.
 *
 * Also, this should be thread-safe.
 */
int debug_log(enum DebugLogType type, const char *fmt, ...);
#endif

/**
 * \brief This function holds a mutex basically.
 */
[[noreturn]] void thread_safe_exit(int retcode);

#ifdef __cplusplus
}
#endif
