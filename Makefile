NAME	= ft_ping

FLAGS	= -Wextra -Wall -Werror

SRC		= 	ping/main.c					\
			ping/get_conf.c				\
			ping/fill_packet.c			\
			ping/compute_checksum.c		\
			ping/print_packet.c			\
			ping/socket.c				\
			ping/send_ping.c			\
			ping/recv_pong.c			\
			ping/utils.c				\
			ping/print_stats_and_exit.c	\
			ping/handle_signals.c		\
			ping/init_structs.c			\
			ping/get_conf.c				\
			ping/parse_input.c			\

OBJ 	=	${SRC:.c=.o}

%.o: %.c
	clang ${FLAG} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
	clang ${OBJ} -o $(NAME) -lm
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