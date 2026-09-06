#include "ft_ping.h"

void    ping_loop(t_ping_ctx *ping_ctx) {
    int seq = 1;
    char packet[64];
    char    recv_buf[RECV_BUF_SIZE];
    t_icmphdr	*icmphdr;

    while (1) {
        build_icmp_echo_request(ping_ctx, icmphdr, packet, seq);
        if (send_request(ping_ctx, packet)) {
            seq++;
            sleep(1);
            continue;
        }
        ping_ctx->sent_count++;
        if (receive_icmp_echo_reply(ping_ctx, icmphdr, recv_buf, packet)) {
        //     print_reply();
            ping_ctx->recv_count++;

        }
        printf("seq = %d\n", seq);
        seq++;
        sleep(1);
    }
}

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