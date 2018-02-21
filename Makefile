# Makefile for PSU_2016_nmobjdump in /home/jsx/Epitech/tek2/PSU/nm_objdump/PSU_2016_nmobjdump/objdump
#
# Made by jsx
# Login   <jsx@epitech.net>
#
# Started on  Wed Feb 22 10:51:54 2017 jsx
# Last update Wed Feb 22 10:51:54 2017 jsx

$@

RULES = objdump nm

all: $(RULES)

$(RULES):
	make -C $@

re clean fclean all:
	make -C objdump $@
	make -C nm $@

.PHONY: $(RULES)
