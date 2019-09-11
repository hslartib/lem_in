LM = lem-in

FRAMEDIR = /Users/$(USER)/Library/Frameworks

INC =	-I ./inc -I ./libft -I ./ \
		-I $(FRAMEDIR)/SDL2.framework/Versions/A/Headers \
		-I $(FRAMEDIR)/SDL2_image.framework/Versions/A/Headers \
		-I $(FRAMEDIR)/SDL2_ttf.framework/Versions/A/Headers \
		-I $(FRAMEDIR)/SDL2_mixer.framework/Versions/A/Headers

FRAME =	$(FRAMEDIR)/SDL2.framework $(FRAMEDIR)/SDL2_image.framework \
		$(FRAMEDIR)/SDL2_mixer.framework $(FRAMEDIR)/SDL2_ttf.framework

FLAGS = -Ofast -Wall -Werror -Wextra -c -g

FLAGS2 =	-F ~/Library/Frameworks/ -framework SDL2 -framework SDL2_image \
			-framework SDL2_ttf -framework SDL2_mixer -g


LIB = -L./libft -lft

OBJ = src/build_path.o \
      src/delite.o \
      src/do_count.o \
      src/do_path.o \
      src/double_check.o \
      src/double_path.o \
      src/help_delite_1.o \
      src/help_delite_2.o \
      src/help_do_path.o \
      src/help_double_path.o \
      src/help_len_vrtc_den.o \
      src/help_output.o \
      src/info_init.o \
      src/info_init_misc.o \
      src/info_validation.o \
      src/lem_cleanup.o \
      src/lem_finish.o \
      src/lem_sdl_animation.o \
      src/lem_sdl_close.o \
      src/lem_sdl_init.o \
      src/lem_sdl_loadmap.o \
      src/lem_sdl_main.o \
      src/lem_sdl_text.o \
      src/lem_strt.o \
      src/len_vrtc_and_weight.o \
      src/len_vrtc_den_and_weight_den.o \
      src/output.o \
      src/lem_sdl_loadres.o \
      src/info_init_checkorder.o


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
	rm -rf $(FRAMEDIR)/*
	Make -C libft clean
	rm -f $(OBJ)

fclean: clean
	Make -C libft fclean
	rm -f $(LM)

re: fclean all
