NAME	= 	ft_ping

FLAGS	= 	-Wextra -Wall -Werror

SRC		= 	srcs/main.c										\
			srcs/init_and_parse/init_structs.c				\
			srcs/init_and_parse/parse_input_check_conf.c	\
			srcs/init_and_parse/regex_parse_input.c			\
			srcs/init_and_parse/init_sockets.c				\
			srcs/routine/fill_packet.c						\
			srcs/routine/handle_signals.c					\
			srcs/routine/compute_checksum.c					\
			srcs/routine/send_ping.c						\
			srcs/routine/recv_pong.c						\
			srcs/routine/utils.c							\
			srcs/routine/create_thread_if_timeout.c			\
			srcs/print/print_final_stats_and_exit.c			\
			srcs/print/print_and_update_packet_stats.c		\
			srcs/print/print_packet_sent_dump.c				\

OBJ 	=	${SRC:.c=.o}

%.o: %.c
	@echo "\e[38;2;255;222;0mcreating object for:\e[38;2;255;255;255m $< "
	@clang ${FLAGS} -c $< -o ${<:.c=.o}

$(NAME): $(OBJ)
	@clang  ${OBJ} ${FLAGS} -o $(NAME) -lm
	@# sudo setcap cap_net_raw=eip ./ft_ping
	@echo "\e[38;2;31;236;0mcompilation finished\e[38;2;255;255;255m"
 
all :
	@echo "\e[38;2;255;222;0mcompiling $(NAME)"
	${NAME}

clean:
	@echo "\e[38;2;255;129;0m$(NAME) objects removed\e[38;2;255;255;255m"
	@/bin/rm -f ${OBJ}

fclean: clean
	@echo "\e[38;2;255;0;0m$(NAME) binary removed\e[38;2;255;255;255m"
	@/bin/rm -f ${NAME}

re: fclean ${NAME}

.PHONY = all clean fclean re
