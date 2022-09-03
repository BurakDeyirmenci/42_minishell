# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rdeyirme <rdeyirme@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/01 10:51:34 by rdeyirme          #+#    #+#              #
#    Updated: 2022/09/01 10:51:34 by rdeyirme         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors

BLACK			=	"\033[0;30m"
RED				=	"\033[0;31m"
GREEN			=	"\033[0;32m"
YELLOW			=	"\033[0;33m"
CYAN			=	"\033[0;35m"
BLUE			=	"\033[0;36m"
WHITE			=	"\033[0;37m"
END				=	"\033[0;0m"

# Files
NAME	=	minishell
SRCS	=	main.c command.c exec.c exec2.c exec3.c env.c utils.c env_utils.c builtin_funcs.c builtin_funcs_2.c handle_quote.c handle_pipe.c
OBJS	=	$(SRCS:.c=.o)
CFLAGS	=	-Wall -Wextra -Werror -I./lib/readline/include
LDFLAGS	= 	-L./lib/readline/lib -lreadline
LIBFT	=	libft/libft.a
LIB		= 	lib/.minishell

all: $(NAME)

$(NAME): $(LIB) $(LIBFT) $(OBJS)  
	@echo $(YELLOW) "Building... $(NAME)" $(END)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME) $(LIBFT)
	@echo $(GREEN) "$(NAME) created successfully!\n" $(END)

$(LIBFT):
	@echo $(YELLOW) "Compiling..." Libft $(END)
	@make -C libft

$(LIB):
	@make -C ./lib

clean:
	@echo $(YELLOW) "Removing object files...$(NAME)" $(END)
	@make -C libft fclean
	@rm -rf $(NAME)
	@echo $(RED) "All files deleted successfully!\n" $(END)

fclean: clean
	@make -C lib fclean
	@make -C libft fclean
	@rm -rf $(NAME) $(OBJS)

re: fclean all

norm :
	@make norm -C libft
	@norminette $(SRCS)

.PHONY: all, clean, fclean, re
