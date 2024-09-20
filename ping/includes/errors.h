#ifndef ERRORS_H
# define ERRORS_H

# define ERROR_TTL_TOO_BIG(ttl)                 fprintf(stderr, "ft_ping: option value too big: %s\n", ttl)
# define ERROR_INVALID_VALUE(value)             fprintf(stderr, "ft_ping: invalid value (`%s' near `%s')\n", value, value)
# define ERROR_OPTION_REQUIRE_ARG(option)       fprintf(stderr, "ping: option '%s' requires an argument\nTry 'ping --help' or 'ping --usage' for more information.\n", option)
# define ERROR_CORE_DUMP                        fprintf(stderr, "Quit (core dumped)\n")
# define ERROR_TIMEOUT_VALUE_TOO_SMALL(value)   fprintf(stderr, "ft_ping: option value too small: %ld\n", value)
# define ERROR_TIMEOUT_VALUE_TOO_BIG(value)     fprintf(stderr, "ft_ping: option value too big: %ld\n", value)
# define ERROR_INVALID_OPTION(opt)              fprintf(stderr, "ft_ping: invalid option -- '%s'\nTry 'ping --help' or 'ping --usage' for more information.\n", opt)
# define ERROR_UNKNOWN_HOST                     fprintf(stderr, "ft_ping : unknown host\n")
# define ERROR_COMPILING_REGEX                  fprintf(stderr, "An error occured compiling regex.\n")
# define ERROR_NEED_TO_BE_ROOT                  fprintf(stderr, "You need to be root\n")
# define ERROR_MISSING_HOST_OPERAND             fprintf(stderr, "ft_ping: missing host operand\nTry 'ping --help' or 'ping --usage' for more information.\n")
# define ERROR_TIMEOUT(dest_ip, seq)            fprintf(stderr, "Timeout from %s: icmp_seq=%d\n", dest_ip, seq)
# define ERROR_INTERVAL_AND_FLOOD_INCOMPATIBLE  fprintf(stderr, "ft_ping: -f and -i incompatible options\n")

#endif