#include "ft_ping.h"

int	send_request(t_ping_ctx *ping_ctx, char *packet) {
    struct sockaddr_in dest_addr;
	memset(&dest_addr, 0, sizeof(dest_addr));
	dest_addr.sin_familly = AF_INET;
	dest_addr.sin_addr.s_addr = ping_ctx->dest_ip;
	
	ssize_t sent_size = sendto(ping_ctx->sockfd, packet, 64, 0, (struct sockaddr *)&dest_addr, sizeof(dest_addr));
	if (sent_size < 0) {
		perror("send failed");
		return (0);
	}
	if (sent_size != 64) {
		fprintf(stderr, "ft_ping: partial packet sent, %zd of 64 bytes sent\n", sent_size)
		return (0);
	}
	return (1);
}

int	receive_icmp_echo_reply(t_ping_ctx *ping_ctx, t_icmphdr *icmphdr, char *recv_buf, char *packet) {
	ssize_t n = recvfrom(ping_ctx->sockfd, recv_buf, RECV_BUF_SIZE, 0, NULL, NULL);
	if (n < 0) {
		perror("recv failed");
		return (0);
	}
	struct iphdr *ip_hdr = (struct iphdr *)recv_buf;
	int ip_hdr_len = ip_hdr->ihl * 4;
	if (n < (ip_hdr_len + (int)sizeof(t_icmphdr)))
		return (0);
	t_icmphdr *reply = (t_icmphdr *)(recv_buf + ip_hdr_len);
	if (reply->type == ECHO_REPLY) {
		if (reply->id != icmphdr->id)
			return (0);
		if (reply->sequence != icmphdr->sequence)
			return (0);
		char *payload = (char *)reply + sizeof(t_icmphdr);
		struct timeval recv_time;
		struct timeval send_time;
		gettimeofday(&recv_time, NULL);
		memcpy(send_time, payload, sizeof(send_time));
		double rtt_min = (recv_time.tv_sec - send_time.tv_sec) * 1000 - (recv_time.tv_usec - send_time.tv_usec) / 1000; 
			
	} else if (reply->type == DESTINATION_UNREACHABLE
				|| reply->type == TIME_EXCEEDED) {
	
	}
}