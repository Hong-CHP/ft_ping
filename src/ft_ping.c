#include "ft_ping.h"

int main(int argc, char **argv) {
    if (argc < 2) {
        fprintf(stderr, "ft_ping: usage error: Destination address required\n");
        exit(2);
    }
    t_ping_ctx  *ping_ctx;
    ping_ctx = malloc(sizeof(t_ping_ctx));
    if (!ping_ctx) {
        fprintf(stderr, "malloc failed\n");
        exit(1);
    }
    if (!parse_ping_args(argc - 1, argv + 1, ping_ctx)) {
        free(ping_ctx);
        exit(2);
    }
    free(ping_ctx);
    return 0;
}