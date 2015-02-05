#ifndef __EVIEO__ADV_STRING_H__
#define __EVIEO__ADV_STRING_H__


#include "common.h"


typedef struct {
    uint8_t *data;
    size_t len;
} lts_str_t;


#define lts_string(str) {\
    (uint8_t *)str, sizeof(str) - 1,\
}
#define lts_null_string {\
    NULL, 0,\
};
static inline
void lts_str_init(lts_str_t *str, uint8_t *data, size_t len)
{
    str->data = data;
    str->len = len;
}


extern size_t long_width(long x);
extern void lts_str_reverse(lts_str_t *src);
extern size_t lts_str_filter(lts_str_t *src, uint8_t c);
extern int lts_str_compare(lts_str_t const *a, lts_str_t const *b);
extern int lts_str_find(lts_str_t const *text, lts_str_t const *pattern);
extern int lts_l2str(lts_str_t *str, long x);
#endif // __EVIEO__ADV_STRING_H__