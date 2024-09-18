NAME	= ft_ping

FLAGS	= -Wextra -Wall -Werror -g

SRC		= 	ping/main.c						\
			ping/handle_signals.c			\
			ping/init_structs.c				\
			ping/parse_input_get_conf.c		\
			ping/regex_parse_input.c		\
			ping/fill_packet.c				\
			ping/compute_checksum.c			\
			ping/print_packet.c				\
			ping/socket.c					\
			ping/send_ping.c				\
			ping/recv_pong.c				\
			ping/utils.c					\
			ping/print_final_stats_and_exit.c		\
			ping/print_and_update_packet_stats.c\
			ping/fork_if_timeout_option.c	\

OBJ 	=	${SRC:.c=.o}

%.o: %.c
	clang ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
	clang  ${OBJ} ${FLAGS} -o $(NAME) -lm
	sudo setcap cap_net_raw=eip ./ft_ping
	${MAKE}	clean
	# clear

all : ${NAME}

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f ${NAME}

re: fclean ${NAME}

.PHONY = all clean fclean re