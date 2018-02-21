# Makefile for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/objdump
#
# Made by jsx
# Login   <jsx@epitech.net>
#
# Started on  Wed Feb 22 10:51:54 2017 jsx
# Last update Wed Feb 22 10:51:54 2017 jsx

NAME    = my_nm

CC	= gcc

CP  	= cp

CFLAGS  = -W -Wall -Werror -Wextra -I./include

SRC 	= 	src/main.c \
		src/nm_32arch.c \
		src/nm_64arch.c \
		src/nm32_utils.c \
		src/nm64_utils.c \
		src/nm32_sym.c \
		src/nm64_sym.c \
		src/utils.c \

OBJ	 = 	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	$(CP) $(NAME) ../
	@printf "\033[0;32mmy_nm compiled successfully !\n\033[0m"

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)
re: fclean all

.PHONY: all clean fclean re
