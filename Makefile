# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzenz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/12 18:25:28 by tzenz             #+#    #+#              #
#    Updated: 2020/01/30 13:23:39 by tzenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#printf
NAME = libftprintf.a
PTF_DIR = ./srcs/ft_printf/
PTF_SRC =	ft_printf.c\
			other_function.c\
			parse_format.c\
			parse_specifier.c\
			print_char_str.c\
			print_double.c\
			print_hex_oct.c\
			print_int.c\
			print_percent.c\
			print_signed_int2.c\
			print_utf.c\

CFILES = $(patsubst %, $(PTF_DIR)%, $(PTF_SRC))
PTF_OBJ = $(patsubst %.c, %.o, $(PTF_SRC))
OBJ_DIR = ./obj/
DIR = ./obj
OFILES = $(addprefix $(OBJ_DIR), $(PTF_OBJ))
SRC_INC = -I ./include
FLAGS = -Wall -Wextra -Werror

#libft
LFT_DIR = ./srcs/libft/
LFT_INC = -I $(LFT_DIR)include/
LFT_OBJ = $(patsubst %.c, %.o, $(LFT_DIR)*.c)
LFT_LIBFT = -I $(LFT_DIR)libft.a

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all:$(NAME)

$(NAME): $(LFT_OBJ) $(PTF_OBJ) $(OBJ_DIR)
	@echo "printf: $(GREEN)Creating libftprintf...$(RESET)"
	@mv *.o $(OBJ_DIR)
	@ar rc $(NAME) $(OFILES) $(LFT_OBJ)
	@ranlib $(NAME)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LFT_DIR)%.o: $(LFT_DIR)%.c
	@echo "printf: $(GREEN)Creating libft...$(RESET)"
	@make -C $(LFT_DIR)

$(PTF_OBJ): $(CFILES)
	@gcc -c $(SRC_INC) $(LFT_INC) $(CFILES) $(LFT_LIBFT)

clean:
	@echo "printf: $(RED)Deleting libft obj...$(RESET)"
	@make clean -C $(LFT_DIR)
	@echo "printf: $(RED)Deleting srcs obj...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -f *.o

fclean: clean
	@echo "printf: $(RED)Deleting libft.a...$(RESET)"
	@make fclean -C srcs/libft
	@echo "printf: $(RED)Deleting libftprintf...$(RESET)"
	@rm -f $(NAME)

re: fclean clean all

.PHONY: all clean fclean re
