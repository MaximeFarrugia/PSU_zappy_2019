##
## EPITECH PROJECT, 2019
## Makefile
## File description:
## Makefile
##

SERVER_NAME	=	zappy_server

IA_NAME		=	zappy_ai

SERVER_SRC	=	$(shell find server -name "*.c")

IA_CLI		=	$(shell find cli -name "*.c")

IA_SRC	=	ia/ai.c

CFLAGS		=	-g3 -W -Wall -Wextra

LDFLAGS		=	-Iincludes -D_GNU_SOURCE

all: zappy_server zappy_ia clean2

zappy_server: $(SERVER_SRC)
	gcc $(CFLAGS) -o $(SERVER_NAME) $(SERVER_SRC) $(LDFLAGS)

zappy_ia: $(IA_SRC)
	gcc $(CFLAGS) -o $(IA_NAME) $(IA_SRC) $(LDFLAGS)

clean clean1 clean2:
	$(shell find . -name "*.o" -delete)
	$(shell find . -name "*~" -delete)
	$(shell find . -name "#*#" -delete)
	$(shell find . -name "vgcore.*" -delete)

fclean: clean1
	rm -f $(SERVER_NAME)
	rm -f $(IA_NAME)

re: fclean all

.PHONY: all clean1 clean2 fclean re server ia
