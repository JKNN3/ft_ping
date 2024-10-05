NAME		= 	ft_ping

SRC_DIR		=	srcs
OBJ_DIR		=	obj
FLAGS		=	-Wextra -Wall -Werror
INCLUDE_DIR 	=	 -I includes
OBJ 		=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

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


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@clang $(FLAGS) $(INCLUDE_DIR) -c $< -o $@
	@echo "$(YELLOW)creating object for:$(NC) $(notdir $<)"

$(NAME): $(OBJ)
	@clang  $(OBJ) $(INCLUDE_DIR) $(FLAGS) -o $(NAME) -lm
	@echo "$(BLUE)compilation finished$(NC)"
 
all:
	$(NAME)

setcap: $(NAME)
	@sudo setcap cap_net_raw=eip ./ft_ping
	@echo "$(PURPLE)$(NAME) FT_PING IS CAPABLE OF ANYTHING NOW !! $(NC)"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(PINK)$(NAME) objects removed$(NC)"

fclean: clean
	@rm -f $(NAME)
	@echo "$(PINK)$(NAME) binary removed$(NC)"

re: fclean $(NAME)

.PHONY = all setcap clean fclean re

#########  COLORS  ##########

BLUE = \e[38;2;102;178;255m
PURPLE = \e[38;2;153;153;255m
PINK = \e[38;2;255;153;204m
YELLOW = \e[38;2;255;205;0m
NC = \033[0;37m


ifeq ($(VERBOSE), true)
	FLAGS += -D VERBOSE
endif
