#include "logs.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

static pthread_mutex_t print_mtx = PTHREAD_MUTEX_INITIALIZER;
int debug_log(enum DebugLogType type, const char *fmt, ...) {
    va_list va;
    // this *might* be due to C23.
    va_start(va, fmt);
    pthread_mutex_lock(&print_mtx);
    switch (type) {
    case INFO:
        printf("\033[34;1m[INFO]\033[0m: ");
        break;
    case ERROR:
        printf("\033[31;1m[ERROR]\033[0m: ");
        break;
    case WARN:
        printf("\033[93;1m[WARN]\033[0m: ");
        break;
    }
    auto ret = vprintf(fmt, va);
    pthread_mutex_unlock(&print_mtx);
    return ret;
}
