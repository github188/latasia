#ifndef __EVIEO__CONF_H__
#define __EVIEO__CONF_H__


#include "adv_string.h"
#include "mem_pool.h"


typedef struct lts_conf_s lts_conf_t;


struct lts_conf_s {
    int workers; // 工作进程数
    lts_str_t port; // 监听端口
    lts_str_t log_file; // 日志
    lts_str_t backends; // 后台服务器
    int keepalive; // 连接超时时间
};


extern lts_conf_t lts_conf;
extern int lts_load_config(lts_conf_t *conf, lts_pool_t *pool);
#endif // __EVIEO__CONF_H__