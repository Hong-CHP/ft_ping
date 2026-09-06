#include "ft_ping.h"

void	send_request(t_ping_ctx *ping_ctx, char *packet) {
	struct sockaddr *dest_addr;
	
	sendto(ping_ctx->sockfd, packet, 64, flags, )
}