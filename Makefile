#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/10/02 17:07:41 by vvysotsk          #+#    #+#              #
#    Updated: 2018/10/02 17:07:42 by vvysotsk         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

.PHONY : all clean fclean clean re

NAME = libftprintf.a

CFLAGS += -Wall -Wextra -Werror
CFLAGS += -I includes/

FILES =	ft_printf.c bonus.c float.c form_out.c handler.c help_handler.c \
		num.c num_help.c parser.c str.c uni.c wstr.c

LIBFILES =	ft_strlen.c ft_strdup.c	ft_strndup.c ft_strnew.c ft_strchr.c ft_memalloc.c \
			ft_memcpy.c ft_recalloc.c ft_strcpy.c ft_uimaxtoa_base.c ft_memset.c ft_imaxtoa.c \
			ft_strcmp.c ft_memmove.c ft_save_to_str.c ft_find_char.c ft_strncpy.c ft_strnstr.c \
			ft_bzero.c ft_isalpha.c ft_isdigit.c

PRINTFSRCS	= $(addprefix src/, $(FILES))
LIBSRCS	= $(addprefix libft/, $(LIBFILES))

OBJ = $(PRINTFSRCS:.c=.o)
LIBOBJ = $(LIBSRCS:.c=.o)

all: $(NAME)

$(OBJ): %.o: %.c
	@gcc -c $(CFLAGS) $< -o $@

$(LIBOBJ): %.o: %.c
	@gcc -c $(CFLAGS) $< -o $@

$(NAME): $(LIBOBJ) $(OBJ)
	@ar rcs $(NAME) $(OBJ) $(LIBOBJ)
	@echo "\033[32mCreated libftprintf library\033[0m"

clean:
	@rm -rf $(OBJ) $(LIBOBJ)
	@echo "\033[32mRemoved Object Files\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[32mRemoved Object files and library\033[0m"

re: fclean all
