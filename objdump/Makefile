# Makefile for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/objdump
#
# Made by jsx
# Login   <jsx@epitech.net>
#
# Started on  Wed Feb 22 10:51:54 2017 jsx
# Last update Wed Feb 22 10:51:54 2017 jsx

NAME    = my_objdump

CC	= gcc

CP	= cp

CFLAGS  = -W -Wall -Werror -Wextra -I./include

SRC 	= 	src/main.c \
		src/objdump_32arch.c \
		src/objdump_64arch.c \
		src/objdump32_utils.c \
		src/objdump64_utils.c \
		src/utils.c \

OBJ	 = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)
	$(CP) $(NAME) ../
	@printf "\033[0;32mmy_objdump compiled successfully !\n\033[0m"

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)
	$(RM) ../$(NAME)
re: fclean all

.PHONY: all clean fclean re
