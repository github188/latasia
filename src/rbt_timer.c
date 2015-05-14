/**
 * latasia
 * Copyright (c) 2015 e7 <jackzxty@126.com>
 * */


#include <sys/time.h>

#include "rbt_timer.h"


static lts_socket_t *__lts_timer_heap_search(lts_rb_root_t *root,
                                             lts_socket_t *sock,
                                             int link)
{
    lts_socket_t *s;
    lts_rb_node_t *parent, **iter;

    parent = NULL;
    iter = &root->rb_node;
    while (*iter) {
        parent = *iter;
        s = rb_entry(parent, lts_socket_t, rbnode);

        if (sock->timeout < s->timeout) {
            iter = &(parent->rb_left);
        } else if (sock->timeout > s->timeout) {
            iter = &(parent->rb_right);
        } else {
            return s;
        }
    }

    if (link) {
        rb_link_node(&sock->rbnode, parent, iter);
        rb_insert_color(&sock->rbnode, root);
    }

    return sock;
}

int lts_timer_heap_add(lts_rb_root_t *root, lts_socket_t *s)
{
    if (s != __lts_timer_heap_search(root, s, TRUE)) {
        return -1;
    }

    return 0;
}

void lts_timer_heap_del(lts_rb_root_t *root, lts_socket_t *s)
{
    if (! RB_EMPTY_NODE(&s->rbnode)) {
        if (rb_parent(&s->rbnode) == root->rb_node) {
            RB_CLEAR_NODE(&s->rbnode);
            root->rb_node = NULL;
        } else {
            rb_erase(&s->rbnode, root);
        }
    }

    return;
}

lts_socket_t *lts_timer_heap_min(lts_rb_root_t *root)
{
#if 1

    lts_rb_node_t *p = rb_first(root);

    if (NULL == p) {
        return NULL;
    }

    return rb_entry(p, lts_socket_t, rbnode);

#else

    lts_socket_t *s;
    lts_rb_node_t *p;

    s = NULL;
    p = root->rb_node;
    while (p) {
        if (NULL == p->rb_left) {
            rb_erase(p, root);
            s = rb_entry(p, lts_socket_t, rbnode);
            break;
        }
        p = p->rb_left;
    }

    return s;

#endif
}

void lts_update_time(void)
{
    lts_timeval_t current;

    (void)gettimeofday(&current, NULL);
    lts_current_time = current.tv_sec * 10 + current.tv_usec / 1000 / 100;

    return;
}


int64_t lts_current_time; // 当前时间
lts_rb_root_t lts_timer_heap; // 时间堆
