#include "ft_ping.h"

void    ping_loop(t_ping_ctx *ping_ctx) {
    while (1) {
        printf("111\n");
        sleep(1);
    }
}

int main(int argc, char **argv) {
    if (argc < 2) {
		fprintf(stderr, "ft_ping: missing host operand\n");
		fprintf(stderr, "Try 'ping --help' or 'ping --usage' for more information.\n");
        return(127);
    }
    t_ping_ctx  *ping_ctx;
    ping_ctx = malloc(sizeof(t_ping_ctx));
    if (!ping_ctx) {
        fprintf(stderr, "malloc failed\n");
        return(1);
    }
    memset(ping_ctx, 0, sizeof(t_ping_ctx));
    ping_ctx->ttl = 64;
    if (!parse_ping_args(argc - 1, argv + 1, ping_ctx)) {
        free(ping_ctx);
        exit(2);
    }
    if (!init_socket(ping_ctx)) {
        free(ping_ctx);
        exit(1);
    }
    init_signal(ping_ctx);
    ping_loop(ping_ctx);
    free(ping_ctx);
    return 0;
}