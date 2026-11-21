#include "ft_ping.h"
#include <ctype.h>

int contain_space_char(char *str) {
	while (*str) {
		if (isspace(*str))
			return 1;
		str++;
	}
	return 0;
}

char	get_option(char *option, t_ping_ctx *ping_ctx) {
		if (!option[1]) {
			ping_ctx->opt = INVALID;
			fprintf(stderr, "ft_ping: unknown host\n");
			return '\0';
		}
		if (option[1] == '?') {
			// print_usage();
			printf("print usage\n");
			ping_ctx->opt = HELP;
			return '?';
		} else if (option[1] == 'v') {
			ping_ctx->opt = VERBOSE;
			int i = 2;
			while (option[i]) {			
				if (option[i] == '?') {
					// print_usage();
					printf("print usage\n");
					ping_ctx->opt = HELP;
					return '?';
				} else if (option[i] != 'v') {
					ping_ctx->opt = INVALID;
					fprintf(stderr, "ft_ping: invalid option --'%c'\n", option[i]);
					fprintf(stderr, "Try 'ping --help' or 'ping --usage' for more information.\n");
					return option[i];
				}
				i++;
			}
			return 'v';
		} else {
			ping_ctx->opt = INVALID;
			fprintf(stderr, "ft_ping: invalid option --'%c'\n", option[i]);
			fprintf(stderr, "Try 'ping --help' or 'ping --usage' for more information.\n");
			return option[i];
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

	ping_ctx->opt = NO_OPT;
	while (*tmp) {
		if (!*tmp || *tmp == '\0') {
			fprintf(stderr, "ft_ping: unknown host\n");
			return(0);
		}
		if ((*tmp)[0] == '-') {
			char c = get_option(*tmp, ping_ctx);
			if (argc == 1 && c == 'v' && ping_ctx->opt == VERBOSE) {
				fprintf(stderr, "ft_ping: missing host operand\n");
				fprintf(stderr, "Try 'ping --help' or 'ping --usage' for more information.\n");
 				return (127);
			}
			if (ping_ctx->opt == INVALID)
				return (64);
			if (ping_ctx->opt == '?')
				return (0);
		} else {
			if (contain_space_char(*tmp)) {
				fprintf(stderr, "ft_ping: unknown host\n");
				return(0);	
			}
			get_hostname(*tmp, ping_ctx);
			printf("dest IP: %d", ping_ctx->dest_ip);
			if (ping_ctx->opt == HELP)
				return (0);
		}
		tmp++;
	}
	tmp = NULL;
	return (1);
}