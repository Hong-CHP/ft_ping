#include "ft_ping.h"

t_ping_ctx	*g_ctx = NULL;

int	init_socket(t_ping_ctx *ping_ctx) {
	int sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (sockfd < 0) {
		if (errno == EACCES) {
			fprintf(stderr, "ft_ping: Permission to create socket of type and/or protocol is denied.\n");
		} else {
			perror("ft_ping: socket failed.\n");
		}
		return (0);
	}
	ping_ctx->sockfd = sockfd;
	return (1);
}

int	init_ttl(t_ping_ctx *ping_ctx) {
	int ttl_val = ping_ctx->ttl;
	if (setsockopt(ping_ctx->sockfd, IPPROTO_IP, IP_TTL, &ttl_val, sizeof(ttl_val)) < 0) {
		perror("ft_ping: setsockopt IP_TTL\n");
		return (0);
	}
	return (1);
}

void	sigint_handler(int sig) {
	(void)sig;
	// print_statistics(g_ctx);
	printf("print statistics\n");
	close(g_ctx->sockfd);
	free(g_ctx->target_hostname);
	free(g_ctx);
	exit(0);
}

int	init_signal(t_ping_ctx *ping_ctx) {
	g_ctx = ping_ctx;
	signal(SIGINT, sigint_handler);
}