# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzenz <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/12 18:25:28 by tzenz             #+#    #+#              #
#    Updated: 2020/03/05 14:11:00 by tzenz            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
PTF_DIR = ./srcs/
PTF_SRC =	ft_printf.c\
			other_function.c\
			parse_format.c\
			parse_specifier.c\
			print_char_str.c\
			print_double.c\
			print_hex_oct.c\
			print_int.c\
			itoa_double.c\
			print_utf.c\
			print_binary.c\
			macro.c\

CFILES = $(patsubst %, $(PTF_DIR)%, $(PTF_SRC))
PTF_OBJ = $(patsubst %.c, %.o, $(PTF_SRC))
OBJ_DIR = ./obj/
OFILES = $(patsubst %, $(OBJ_DIR)%, $(PTF_OBJ))
SRC_INC = -I ./includes/
INC_FT = ./includes/ft_printf.h
FLAGS = -Wall -Wextra -Werror

LFT_DIR = ./srcs/libft/
LFT_INC = -I $(LFT_DIR)includes/
LFT_OBJ = $(patsubst %.c, %.o, $(LFT_DIR)*.c)

LFT_LIBFT = $(LFT_DIR)libft.a

INC_LIB = ./srcs/libft/includes/libft.h

GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

all:$(NAME)

$(NAME): $(OBJ_DIR) $(LFT_OBJ) $(OFILES)
	@echo "printf: $(GREEN)Creating libftprintf...$(RESET)"
	@ar rc $(NAME) $(OFILES)
	@ranlib $(NAME)

$(OBJ_DIR)%.o: $(PTF_DIR)%.c $(INC_FT)
	@gcc $(FLAGS) $(SRC_INC) $(LFT_INC) -c $(CFILES)
	@mv *.o $(OBJ_DIR)

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LFT_DIR)%.o: $(LFT_DIR)%.c $(INC_LIB)
	@echo "printf: $(GREEN)Creating libft...$(RESET)"
	@make -C $(LFT_DIR)
	@cp $(LFT_LIBFT) ./$(NAME)

clean:
	@echo "printf: $(RED)Deleting libft obj...$(RESET)"
	@make clean -C $(LFT_DIR)
	@echo "printf: $(RED)Deleting srcs obj...$(RESET)"
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "printf: $(RED)Deleting libft.a...$(RESET)"
	@make fclean -C srcs/libft
	@echo "printf: $(RED)Deleting libftprintf.a...$(RESET)"
	@rm -f $(NAME)

re: fclean clean all

.PHONY: all clean fclean re
