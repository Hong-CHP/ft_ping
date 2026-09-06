#include "ft_ping.h"

uint16_t checksum(void *packet, int len) {
	uint16_t *ptr = packet;
	uint32_t sum = 0;

	for (; len > 1; len -= 2) {
		sum += *ptr++;
	}
	if (len == 1)
		sum += *(uint8_t*)ptr;
	while (sum >> 16)
		sum = (sum >> 16) + (sum & 0xFFFF);
	return (~sum);
}

void	build_icmp_echo_request(t_ping_ctx *ping_ctxm, char packet[64], int seq) {
	t_icmphdr	*icmphdr;
	icmphdr = (t_icmphdr*)packet;
	icmphdr->type = ECHO_REQUEST;
	icmphdr->code = 0;
	icmphdr->checksum = 0;
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

	icmphdr->checksum = checksum(packet, 64);
}