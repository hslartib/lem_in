LM = lem_in

INC = -I ./inc -I ./libft -I ./

FLAGS = -Wall -Werror -Wextra -c -g

LIB = -L./libft -lft

OBJ = src/lem_strt.o src/info_init.o src/info_init_misc.o src/lem_cleanup.o

all: $(LM)

$(LM): $(OBJ)
	Make -C libft
	gcc $(OBJ) $(OBJPS) $(INC) $(LIB) -o $(LM)

$(OBJ): %.o: %.c
	gcc $(FLAGS) $(INC) $< -o $@

clean:
	Make -C libft clean
	rm -f $(OBJ)

fclean: clean
	Make -C libft fclean
	rm -f $(LM)

re: fclean all