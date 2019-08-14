LM = lem_in

INC = -I ./inc -I ./libft

FLAGS = -Wall -Werror -Wextra -c -g

LIB = -L./ps_lib -lps -L./ps_lib/libft -lftprintf

OBJ = src/lem_strt.o src/info_init.o

all: $(LM)

$(LM): $(OBJ)
	Make -C libft
	gcc $(OBJ) $(OBJPS) $(INC) $(LIB) -o $(PS)

$(OBJ): %.o: %.c
	gcc $(FLAGS) $(INC) $< -o $@

clean:
	Make -C libft clean
	rm -f $(OBJ)

fclean: clean
	Make -C libft fclean
	rm -f $(LM)

re: fclean all