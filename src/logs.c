#include "logs.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

static mtx_t print_mtx;
static void print_mtx_init(void) {
    mtx_init(&print_mtx, mtx_plain | mtx_recursive);
}
int debug_log(enum DebugLogType type, const char *fmt, ...) {
    static once_flag init_flag = ONCE_FLAG_INIT;
    call_once(&init_flag, print_mtx_init);
    va_list va;
    // this *might* be due to C23.
    va_start(va, fmt);
    mtx_lock(&print_mtx);
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
    mtx_unlock(&print_mtx);
    return ret;
}
