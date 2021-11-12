	# Library Name #
NAME	=
CLIENT	=	client
SERVER	=	server

	# libft Variables #
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft

	# Mandatory Variables #
SRC_C	=	client.c
SRC_S	=	server.c
INC		=	-I. -I$(LIBFT_DIR) -I$(LIBFT_DIR)/get_next_line

	# Compiling Variables #
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

	# Colors #
GREEN		=	\e[38;5;118m
YELLOW		=	\e[38;5;226m
RESET		=	\e[0m
_SUCCESS	=	[$(GREEN)SUCCESS$(RESET)]
_INFO		=	[$(YELLOW)INFO$(RESET)]

all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER): $(LIBFT) $(SRC_S)
	@ $(CC) $(CFLAG) $(SRC_S) $(LIBFT) $(INC) -o $(SERVER)
	@printf "$(_SUCCESS) server ready.\n"

$(CLIENT): $(LIBFT) $(SRC_C)
	@ $(CC) $(CFLAG) $(SRC_C) $(LIBFT) $(INC) -o $(CLIENT)
	@printf "$(_SUCCESS) client ready.\n"


$(LIBFT):
	@ $(MAKE) -C ./libft

clean:
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"

fclean:
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ $(RM) $(CLIENT) $(SERVER)
	@printf "$(_INFO) client removed.\n"
	@printf "$(_INFO) server removed.\n"

re: fclean all

mandatory:	$(CLIENT) $(SERVER)
bonus:		mandatory

m : mandatory
b : bonus

.PHONY: all clean fclean re mandatory m bonus b
