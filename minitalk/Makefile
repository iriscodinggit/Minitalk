# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mlanca-c <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/06/28 10:50:29 by mlanca-c          #+#    #+#              #
#    Updated: 2024/01/21 19:25:39 by irlozano         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

	# Library Name #
NAME	=   minitalk
CLIENT	=	client
SERVER	=	server
CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

	# libft Variables #
LIBFT		=	./libft/libft.a
LIBFT_DIR	=	./libft


	# Mandatory Variables #
SRC_C	=	client.c
SRC_S	=	server.c
INC		=	-I. -I$(LIBFT_DIR)

	# Bonus Variables #
SRC_C_BONUS = client_bonus.c
SRC_S_BONUS = server_bonus.c

	# Compiling Variables #
CC			=	gcc
CFLAG		=	-Wall -Wextra -Werror
RM			=	rm -f

all: $(SERVER) $(CLIENT)

$(NAME): all

$(SERVER): $(LIBFT)
	@ $(CC) $(CFLAG) $(SRC_S) $(LIBFT) $(INC) -o $(SERVER)

$(CLIENT): $(LIBFT)
	@ $(CC) $(CFLAG) $(SRC_C) $(LIBFT) $(INC) -o $(CLIENT)

bonus: $(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER_BONUS): $(LIBFT)
	@ $(CC) $(CFLAG) $(SRC_S_BONUS) $(LIBFT) $(INC) -o $(SERVER_BONUS)

$(CLIENT_BONUS): $(LIBFT)
	@ $(CC) $(CFLAG) $(SRC_C_BONUS) $(LIBFT) $(INC) -o $(CLIENT_BONUS)

$(LIBFT):
	@ $(MAKE) -C ./libft

clean:
	@ $(RM) $(CLIENT) $(SERVER)
	@ $(RM) $(CLIENT_BONUS) $(SERVER_BONUS)
	@ $(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	@ $(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
