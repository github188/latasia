#include "file.h"
#include "logger.h"


lts_str_t LTS_LOG_PREFIXES[LTS_LOG_MAX];

lts_logger_t lts_stderr_logger = {
    &lts_stderr_file,
    LTS_LOG_EMERGE,
};
lts_logger_t lts_file_logger = {
    &lts_log_file,
    LTS_LOG_ERROR,
};


ssize_t lts_write_logger_fd(lts_logger_t *log, void const *buf, size_t n)
{
    return lts_file_write(log->file, buf, n, 0);
}


ssize_t lts_write_logger(lts_logger_t *log,
                         int level, char const *fmt, ...)
{
    va_list args;
    int len, total;
    char buf[4096];

    if (level < log->level) {
        return 0;
    }

    total = len = snprintf(
        buf, sizeof(buf), "[%s] ", LTS_LOG_PREFIXES[level].data
    );
    va_start(args, fmt);
    len = vsnprintf(buf + len, sizeof(buf) - len, fmt, args);
    va_end(args);

    if (len > 0) {
        total += len;
        return lts_write_logger_fd(log, buf, total);
    } else {
        return -1;
    }
}

/*
ssize_t lts_write_logger(lts_logger_t *log,
                         int level, char const *fmt, ...)
{
    va_list args;
    char const *p, *last;
    char const *arg;
    lts_str_t const *prefix;
    ssize_t total_size, tmp_size;
    char delimiter = 0x20;

    if (level < log->level) {
        return 0;
    }

    prefix = LTS_LOG_PREFIXES + level;
    (void)lts_write_logger_fd(log, prefix->data, prefix->len);
    (void)lts_write_logger_fd(log, &delimiter, 1);
    va_start(args, fmt);
    total_size = 0;
    p = fmt;
    while (*p) {
        for (last = p; (*last) && ('%' != *last); ++last) {
        }
        tmp_size = lts_write_logger_fd(log, p, last - p);
        if ((0 == *last) ||  (0 == *(last + 1))) {
            break;
        }
        switch (*++last) {
            case 's': {
                arg = va_arg(args, char const *);
                (void)lts_write_logger_fd(log, arg, strlen(arg));
                p = last + 1;
                break;
            }

            case '%': {
                (void)lts_write_logger_fd(log, "%", strlen("%"));
                p = last + 1;
                break;
            }

            case 'd': {
                size_t width;
                lts_str_t str;

                arg = (char const *)va_arg(args, long);
                width = long_width((long)arg);
                lts_str_init(&str, (uint8_t *)alloca(width), width);
                (void)lts_l2str(&str, (long)arg);
                (void)lts_write_logger_fd(log, str.data, str.len);
                p = last + 1;
                break;
            }

            default: {
                p = last;
                break;
            }
        }

        if (-1 == tmp_size) {
            total_size = -1;
            break;
        }

        total_size += tmp_size;
    }
    va_end(args);

    return total_size;
}
*/
