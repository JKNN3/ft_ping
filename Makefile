NAME	= ft_ping

FLAGS	= -Wextra -Wall -Werror -g

SRC		= 	ping/main.c						\
			ping/handle_signals.c			\
			ping/init_and_parse/init_structs.c				\
			ping/init_and_parse/parse_input_check_conf.c		\
			ping/init_and_parse/regex_parse_input.c		\
			ping/fill_packet.c				\
			ping/compute_checksum.c			\
			ping/print_packet_sent_dump.c	\
			ping/socket.c					\
			ping/send_ping.c				\
			ping/recv_pong.c				\
			ping/utils.c					\
			ping/print_final_stats_and_exit.c		\
			ping/print_and_update_packet_stats.c\
			ping/create_thread_if_timeout.c	\

OBJ 	=	${SRC:.c=.o}

%.o: %.c
	clang ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
	clang  ${OBJ} ${FLAGS} -o $(NAME) -lm
	sudo setcap cap_net_raw=eip ./ft_ping

all : ${NAME}

clean:
	/bin/rm -f ${OBJ}

fclean: clean
	/bin/rm -f ${NAME}

re: fclean ${NAME}

.PHONY = all clean fclean re