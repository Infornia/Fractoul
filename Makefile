# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mwilk <mwilk@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/09 16:17:56 by mwilk             #+#    #+#              #
#    Updated: 2016/02/09 22:21:20 by mwilk            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = fractol
LIBFT = Libft

CC = gcc
CFLAGS = -Wall -Wextra -Werror

OBJ_PATH = ./obj/
SRC_PATH = ./

OBJ = $(SRC:.c=.o)
SRC = init.c\
	  init_img.c\
	  fractol.c\
	  main.c\
	  hooks.c\
	  hooks_help.c\
	  draw.c\
	  color.c\
	  usage.c\
	  julia.c\
	  tree.c\
	  burn_newton.c\
	  mandelbrot.c\
	  triangle.c\

OBJS = $(addprefix $(OJB_PATH),$(OBJ))
SRCS = $(addprefix $(SRC_PATH),$(SRC))

FDF_H = -I ./

LIB_H = -I Libft/includes/
LIB_L = -LLibft -lft

MLX_H = -I minilibx/
#MLX_H = -I usr/local/lib/
MLX_L = -L minilibx/ -lmlx -framework OpenGl -framework Appkit
#MLX_L = -L /usr/local/lib/ -lmlx -lm -framework OpenGl -framework Appkit


all: makelib normal

makelib:
		git submodule add --force https://github.com/Infornia/Libft.git $(LIBFT)
		git submodule init
		git submodule update
		@make -C Libft

makerelib:
		@make -C libft re

cleanlib:
		@make -C libft clean

fcleanlib:
		@make -C libft fclean

normal: clean $(NAME)

$(NAME):
	@make -C minilibx/ clean
	@make -C minilibx/
	@gcc -g $(CFLAGS) $(LIB_H) $(FDF_H) $(MLX_H) -c $(SRCS) 
	@mkdir $(OBJ_PATH)
	@gcc -o $(NAME) $(OBJ) $(LIB_L) $(MLX_L)
	@mv $(OBJ) $(OBJ_PATH)
	@echo "\033[35m <(O.O<) WOW ! Very Fractol ! Amaze ! (>^o^)> \033[0m"

clean:
	@/bin/rm -rf $(OBJ_PATH)
	@echo "\033[36mT.T Miss you object files T.T \033[0m"

fclean: clean
	@/bin/rm -rf $(NAME) $(LIBFT)
	@/bin/rm -rf .gitmodules
	@echo "\033[36m X.x Bye Bye compiled files >_< \033[0m"

re: fclean all

.PHONY: all normal clean fclean re makelib makerelib cleanlib fcleanlib

