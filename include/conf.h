/**
 * latasia
 * Copyright (c) 2015 e7 <jackzxty@126.com>
 * */


#ifndef __LATASIA__CONF_H__
#define __LATASIA__CONF_H__


#include "adv_string.h"
#include "mem_pool.h"
#include "file.h"


#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

// configuration {{
#define MAX_CONF_SIZE           65535
#define ENABLE_IPV6             FALSE
#define MODULE_POOL_SIZE        (1024 * 1024)
#define CONN_POOL_SIZE          (1024 * 8)
#define CONN_BUFFER_SIZE        (1024 * 4)
#define MAX_CONNECTIONS         1024
// }} configuration


typedef struct lts_conf_s lts_conf_t;
typedef struct lts_conf_asyn_s lts_conf_asyn_t;


struct lts_conf_s {
    int daemon; // 守护进程
    lts_str_t port; // 监听端口
    int workers; // 工作进程数
    int max_connections; // 单进程最大连接数
    int keepalive; // 连接超时时间
    lts_str_t pid_file; // pid文件
    lts_str_t log_file; // 日志
    lts_str_t app_mod_conf; // 应用模块配置文件
};
struct lts_conf_asyn_s {
    lts_str_t host;
    uintptr_t port;
};


typedef struct {
    lts_str_t name;
    void (*match_handler)(void *conf,
                          lts_str_t *key,
                          lts_str_t *value,
                          lts_pool_t *pool);
} lts_conf_item_t;


extern lts_conf_t lts_main_conf;

extern int load_conf_file(lts_file_t *file, uint8_t **addr, off_t *sz);
extern int parse_conf(void *conf, uint8_t *addr, off_t sz, lts_pool_t *pool);
extern void close_conf_file(lts_file_t *file, uint8_t *addr, off_t sz);
#ifdef __cplusplus
}
#endif // __cplusplus
#endif // __LATASIA__CONF_H__
