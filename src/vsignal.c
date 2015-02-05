#include "latasia.h"
#include "vsignal.h"


static void sig_int_handler(int s);
static void sig_term_handler(int s);
static void sig_chld_handler(int s);
static void sig_pipe_handler(int s);


static lts_signal_t lts_signals[] = {
    {SIGINT, "SIGINT", &sig_int_handler},
    {SIGTERM, "SIGTERM", &sig_term_handler},
    {SIGCHLD, "SIGCHLD", &sig_chld_handler},
    {SIGPIPE, "SIGPIPE", &sig_pipe_handler},
    {0, NULL, NULL},
};


void sig_int_handler(int s)
{
    lts_signals_mask |= LTS_MASK_SIGSTOP;

    return;
}


void sig_term_handler(int s)
{
    lts_signals_mask |= LTS_MASK_SIGSTOP;

    return;
}


void sig_chld_handler(int s)
{
    lts_signals_mask |= LTS_MASK_SIGCHLD;

    return;
}


void sig_pipe_handler(int s)
{
    lts_signals_mask |= LTS_MASK_SIGPIPE;

    return;
}


int lts_init_sigactions(void)
{
    struct sigaction sa;

    sa.sa_flags = 0;
    for (int i = 0; lts_signals[i].signo; ++i) {
        sa.sa_handler = lts_signals[i].handler;
        if (-1 == sigaction(lts_signals[i].signo, &sa, NULL)) {
            return -1;
        }
    }

    return 0;
}