LM = lem_in

FRAMEDIR = /Users/dbrady/Library/Frameworks

INC =	-I ./inc -I ./libft -I ./ \
		-I $(FRAMEDIR)/SDL2.framework/Versions/A/Headers \
		-I $(FRAMEDIR)/SDL2_image.framework/Versions/A/Headers \
		-I $(FRAMEDIR)/SDL2_ttf.framework/Versions/A/Headers \
		-I $(FRAMEDIR)/SDL2_mixer.framework/Versions/A/Headers

FRAME =	$(FRAMEDIR)/SDL2.framework $(FRAMEDIR)/SDL2_image.framework \
		$(FRAMEDIR)/SDL2_mixer.framework $(FRAMEDIR)/SDL2_ttf.framework

FLAGS = -Ofast -Wall -Werror -Wextra -c

FLAGS2 =	-F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
			-framework SDL2_ttf -framework SDL2_mixer


LIB = -L./libft -lft

OBJ = src/lem_strt.o src/info_init.o src/info_init_misc.o src/lem_cleanup.o src/lem_finish.o src/info_validation.o \
src/lem_sdl_main.o src/lem_sdl_close.o src/lem_sdl_init.o

all: $(FRAMEDIR) $(FRAME) $(LM)

$(LM): $(OBJ)
	Make -C libft
	gcc $(OBJ) $(OBJPS) $(INC) $(LIB) $(FLAGS2) -o $(LM)

$(OBJ): %.o: %.c
	gcc $(FLAGS) $(INC) $< -o $@

$(FRAMEDIR):
		mkdir -p $(FRAMEDIR)
		rm -rf $(FRAMEDIR)/*

$(FRAME): $(FRAMEDIR)/%: Frameworks/%
		cp -R $< $(FRAMEDIR)

clean:
	Make -C libft clean
	rm -f $(OBJ)

fclean: clean
	Make -C libft fclean
	rm -f $(LM)

re: fclean all