#include "ft_ping.h"
#include <ctype.h>

int not_empty(char *str) {
	if (!str)
		return 0;
	while (*str) {
		if (isspace(*str))
			return 0;
		str++;
	}
	return 1;
}

char	get_option(char *option, t_ping_ctx *ping_ctx) {
		if (!option[1]) {
			ping_ctx->opt = INVALID;
			fprintf(stderr, "ft_ping: -: Temporary failure in name resolution\n");
			return '\0';
		}
		if (option[1] == '?') {
			// print_usage();
			printf("print usage\n");
			ping_ctx->opt = HELP;
			return '?';
		} else if (option[1] == 'v') {
			int i = 2;
			while (option[i]) {
				if (option[i] == 'v')
					ping_ctx->opt = VERBOSE;
				else if (option[i] == '?') {
					// print_usage();
					printf("print usage\n");
					ping_ctx->opt = HELP;
					return '?';
				} else {
					ping_ctx->opt = INVALID;
					fprintf(stderr, "ft_ping: invalid option --'%c'\n", option[i]);
					// print_usage();
					printf("print usage\n");
					return '\0';
				}
				i++;
			}
			ping_ctx->opt = VERBOSE;
			return 'v';
		} else {
			ping_ctx->opt = INVALID;
			fprintf(stderr, "ft_ping: invalid option --'%c'\n", option[i]);
			// print_usage();
			printf("print usage\n");
			return '\0';
		}
}

int	get_hostname(char *arg, t_ping_ctx *ping_ctx) {
	struct addrinfo hints;
	struct addrinfo *res;
	int	s;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_RAW;

	s = getaddrinfo(arg, NULL, &hints, &res);
	if (s != 0) {
		fprintf(stderr, "ft_ping: getaddrinfo: %s", gai_strerror(s));
		return (0);
	}
	struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
	ping_ctx->dest_ip = addr->sin_addr.s_addr;
	ping_ctx->target_hostname = strdup(arg);
	freeaddrinfo(res);
	return (1);
}   

int	parse_ping_args(int argc, char **argv, t_ping_ctx *ping_ctx) {
	char **tmp = argv;
	while (not_empty(*tmp)) {
		tmp++;
	}
	if (!*tmp) {
		fprintf(stderr, "ft_ping: : No address associated with hostname\n");
		return (0);
	}
	ping_ctx->opt = NO_OPT;
	tmp = argv;
	while (*tmp) {
		if (not_empty(*tmp))
			continue;
		if ((*tmp)[0] == '-') {
			char c = get_option(*tmp, ping_ctx);
			if (ping_ctx->opt == INVALID)
				return (0);
			if (ping_ctx->opt == '?')
				return (1);
			if (argc == 1 && c == 'v' && ping_ctx->opt == VERBOSE) {
			    fprintf(stderr, "ft_ping: usage error: Destination address required\n");
				return (0);
			}
		}
		else {
			get_hostname(*tmp, ping_ctx);
			printf("dest IP: %d", ping_ctx->dest_ip);
			if (ping_ctx->opt == HELP)
				return (1);
		}
		tmp++;
	}
	tmp = NULL;
	return (1);
}