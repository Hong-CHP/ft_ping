#include "ft_ping.h"

void	build_icmp_echo_request(t_ping_ctx *ping_ctxm, char packet[64], int seq) {
	t_icmphdr	*icmphdr;
	icmphdr = (t_icmphdr*)packet;
	icmphdr->type = ECHO_REQUEST;
	icmphdr->code = 0;
	icmphdr->id = getpid() & 0xFFFF;
	icmphdr->sequence = seq;
	
	payload = packet + sizeof(t_icmphdr);
	
	struct timeval now;
	gettimeofday(&now, NULL);
	memcpy(payload, &now, sizeof(now));

	int remain = 64 - sizeof(t_icmphdr) - sizeof(payload);
	for (int i = 0; i < remain; i++) {
		payload[sizeof(now) + i] = i;
	}

	checksum(packet, 64);
}