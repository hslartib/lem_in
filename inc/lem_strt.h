/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_strt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:58:29 by hslartib          #+#    #+#             */
/*   Updated: 2019/09/11 17:47:24 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include <limits.h>
#include "../libft/libft.h"
#include <math.h>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_mixer.h"
#include "../Frameworks/SDL2.framework/Versions/A/Headers/SDL.h"
#include "../Frameworks/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"
#include "../Frameworks/SDL2_mixer.framework/Versions/A/Headers/SDL_mixer.h"
#include "../Frameworks/SDL2_image.framework/Versions/A/Headers/SDL_image.h"

# define NUMBER_OF_FRAMES	8
# define F_FRATE			10

# define ABS_MINUS(a, b)	((a >= b) ? (a - b) : (b - a))
# define ABS(x)				((x >= 0) ? x : -x)

enum 				e_errcode
{
	ALLRIGHT,
	ERROR,
	NO_ROOMS,
	WRONG_ANTS,
	NO_STARTEND,
	MULTIPLE_STARTEND,
	NO_SOLUTION,
	LINK_TO_GHOST,
	MAP_WRONG_ORDER,
	ROOM_INVALID_NAME,
	START_IS_END,
	NO_LINKS,
	EMPTY,
	DUP_ROOMS
};

typedef struct		s_valid
{
	int 			ant;
	int				room;
	int				link;
	int 			runner;
	int				start;
	int				end;
}					t_valid;

typedef struct		s_pos
{
	int pos1[2];
	int pos2[2];
}					t_pos;

typedef struct	s_opredel
{
	int			i;
	int			k;
	int			last;
	int			end;
	int			z;
}				t_opredel;

typedef struct		s_path
{
	int				**root;
	int 			*len_root;
	int 			*count_ant;
	int				count_root;
	int 			itog;
	int             check;
	int             score;

}					t_path;

typedef struct		s_room
{
	char			*name;
	int             index;
	int 			rebuild;
	int				*links;
	int 			coord_x;
	int 			coord_y;
	int				links_len;
	int 			true_index;
	char			*all_path;
	SDL_Rect		pos;
}					t_room;

typedef struct		s_info
{
	int				visual;
	long int		count_ants;
	int				start;
	int				end;
	t_room			**rooms;
	int				count_room;
	int				*len_path;
	t_room			**time;
	int				count_time;
	char 			*path;
	t_path			*marshroot;
	int 			count_string;
	t_room			**dop_rooms;
	int 			cou_d;
	int 			*denied_link_start;
	int				count_den_link;
	char			**input;
	int 			silent;
	t_path			*sdl_path;
}					t_info;

typedef struct		s_ant
{
	int 			*path;
	int 			step;
	int 			p_len;
	int 			visible;
	int 			frame;
}					t_ant;

typedef struct 		s_anim
{
	SDL_Texture		*f_arr[NUMBER_OF_FRAMES * 2];
	t_ant			*ants;
	int 			a_width;
	int 			a_height;
	int 			parts;
	int 			step;
	int 			ant_all;
	int 			waiting;
	int 			arrived;
}					t_anim;

typedef	struct 		s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Rect		w_rect;
	SDL_Event		event;
	SDL_Color		c_path;
	SDL_Color		c_room;
	TTF_Font		*font;
	SDL_Texture		*text[4];
	SDL_Texture		*s_flag;
	t_anim			anim;
	t_info			*info;
	int 			flow;
	int 			move;
	int 			soviet;
	int 			w_width;
	int 			w_height;
	int 			quit;
	int 			key;

}					t_sdl;

/*
**	visuals related functions
*/
void				lem_sdl_text_countants(t_sdl *lm);
void			 	lem_sdl_anim_static(t_sdl *lm);
void				lem_sdl_control(t_info *info);
int					lem_sdl_init_main(t_sdl **lm, t_info *info);
int 				lem_sdl_close(t_sdl *lm, int ret);
void				lem_sdl_addcolour(SDL_Color *colour, SDL_Color c, int sign);
void				lem_sdl_anim_control(t_sdl *lm);
void				lem_sdl_setroompos(t_sdl *lm);
int					lem_sdl_init_font(t_sdl *lm);
void				lem_sdl_renderttext(t_sdl *lm);
void				lem_sdl_draw_background(t_sdl *lm);
int					lem_sdl_init_loadanim(t_sdl *tmp);
void				lem_sdl_loadpath(t_sdl *lm);
void				lem_sdl_loadrooms(t_sdl *lm);
void				lem_sdl_music(t_sdl *lm);
void				lem_sdl_anims_wrap(t_sdl *lm);

/*
** info_init related functions
*/
int					info_init(t_info *info);
int					rooms_find_name(t_room **rooms, char *name);
int					next_value(t_info *info, char **text, int i);
int					init_rooms(t_info *info, char **text);
int					info_valid(t_info *info);
int					info_checkorder(t_info *info);
char				**read_split();
int					check_print(char *line);
int					check_number(char *line);

/*
** finish related functions
*/
void				cleanup_info(t_info *info);
int					lem_errmsg(t_info *info, int errcode);


/*
**	algo functions
*/
int					help_build(t_path *path, t_info *info, char **mas);
void				build_path_den(char *str, t_path *path, t_info *info);
void				rebuild_path(t_path **path, int index);
void				build_path(t_info *info, t_path *path, int index, int lamp);
void				vrtc_den_1(t_info *info, int index, char *str, int k);
void				vrtc_den_2(t_info *info, int index, char *str, int k);
void				vrtc_den_3(t_info *info, int index, char *str, int k);
void				vrtc_den_4(t_info *info, int index, char *str, int k);
char				*obsilut_str(char *str, int index);
char				*help_str_vrtc(char *str, int index, t_info *info);
void				len_vrtc_den(t_info *info, int index, char *str);
void				weight_den(t_info *info);
int					find_max(t_path *path);
int					find_len(t_path *path, t_info *info, int max);
int					find_mod(t_path *path, t_info *info, int max, int len);
void				bit(t_path *path, int mod);
void				do_count(t_info *info, t_path *path);
void				init_path0(t_path **path);
void				init_path0_continue(t_info *info, t_path **path);
void				vibor_krotchaishego(t_info *info, t_path *path);
void				init_path_i(t_path **path, int i);
int					do_path_part_1(t_info *info, t_path **path);
void				do_path_part_2(t_info *info, t_path **path, int i);
void				do_path_part_3(t_info *info, t_path **path, int i);
void				free_path0(t_path **path, t_info *info);
int					do_path(t_info *info);
void				len_vrtc(t_info *info, int nbr);
void				weight(t_info *info);
int					opredel_end(t_path *path, int *puti, int *z, int k);
void				vivod(t_path *path, int *puti, int *komnat, int i);
void				null_n(int *i1, int *i2, int *i3, int *i4);
void				opredel_path(t_info *info, t_path *path, int *puti, int *komnat);
void				finish_algo(t_info *info, t_path *path, int *puti, int *komnat);
void				output(t_info *info, t_path *path);
int					check_end_start_link(t_info *info);
void				output_start_end(t_info *info);

void				umenshaem_do_path1(t_info *info, t_path ***path, int *rex, int *i);
void				umenshaem_do_path2(int *rex, int *i);

void				copy_first(int *src, int *dep, int count);
void				copy_last(int *src, int *dep, int last_s, int last_d);
void				do_pos(t_path *path, int index, int r, t_pos *pos);
void				init_pos(t_pos *pos);
void				double_path_do_prt1(t_path *path, int index, int *mas1);
void				double_path_do1(t_path *path, int index, int r, t_pos *pos);
void				double_path(t_path *path, int index, int r);
int					check_len(t_info *info, int nbr);
void				copy_prepath(t_path **path, int index);
void				perdoz(t_info *info, int src, int out, int in);
void				perdoz_2(t_info *info, int src, int out, int in);
int					check_start_time(int dep, t_path *path);
void				room_in_time_copy(t_room *room, t_info *info, int index);
void				fill_rest(t_info *info);
void				init_time(t_info *info, t_path *path);
void				init_v(t_info *info, int v, int kl);
void				init_start(t_info *info, t_path *path);
int					delite_prt1(t_info *info, t_path *path, int coo, int v);
void				delite(t_info *info, t_path *path);
void				clean_del(t_info *info);
void				free_pathes(t_info *info, t_path **path, int count);


#endif
