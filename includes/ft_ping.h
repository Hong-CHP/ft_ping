#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <unistd.h>
# include <stdint.h>
# include <stdlib.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h> 
# include <netdb.h>
# include <string.h>
# include <signal.h>
# include <sys/time.h>

typedef enum e_icmp_proto_type
{
	ECHO_REPLY = 0,
	DESTINATION_UNREACHABLE = 3,
	REDIRECT_MESSAGE = 5,
	ECHO_REQUEST = 8,
	ROUTER_ADVERTISEMENT = 9,
	ROUTER_SOLICITATION = 10,
	TIME_EXCEEDED = 11,
	PARAMETER_PROBLEM = 12,
	TIMESTAMP = 13,
	TIMESTAMP_REPLY = 14,
}			t_icmp_proto_type;

typedef struct s_icmphdr
{
	uint8_t type;
	uint8_t code;
	uint16_t checksum;
	uint16_t id;
	uint16_t sequence;
}				t_icmphdr;

typedef enum s_opt_type {
	NO_OPT,
	VERBOSE,
	HELP,
	INVALID,
}				t_opt_type;

typedef struct s_ping_ctx
{
	t_opt_type	opt;
	char	*target_hostname;
	uint32_t source_ip;
	uint32_t dest_ip;
	uint8_t ttl;
	int		verbose;
	int		sockfd;
	int		sent_count;
	int		recv_count;
	double	rtt_min;
	double	rtt_max;
	double	rtt_sum;
	double	rtt_sum_sq;
}				t_ping_ctx;

extern 	t_ping_ctx	*g_ctx;

int		parse_ping_args(int argc, char **argv, t_ping_ctx *ping_ctx);
int		init_socket(t_ping_ctx *ping_ctx);
int		init_ttl(t_ping_ctx *ping_ctx);
int		init_signal(t_ping_ctx *ping_ctx);
void	build_icmp_echo_request(t_ping_ctx *ping_ctxm, char packet[64], int seq);

#endif
