/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_strt.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hslartib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 12:58:29 by hslartib          #+#    #+#             */
/*   Updated: 2019/08/13 12:58:31 by hslartib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

#include "../libft/libft.h"
#include "math.h"
#include "/Users/dbrady/Library/Frameworks/SDL2.framework/Versions/A/Headers/SDL.h"
#include "/Users/dbrady/Library/Frameworks/SDL2_image.framework/Versions/A/Headers/SDL_image.h"
#include "/Users/dbrady/Library/Frameworks/SDL2_ttf.framework/Versions/A/Headers/SDL_ttf.h"
#include "/Users/dbrady/Library/Frameworks/SDL2_mixer.framework/Versions/A/Headers/SDL_mixer.h"
#include "../Frameworks/SDL2_gfx/SDL2_framerate.h"
#include "../Frameworks/SDL2_gfx/SDL2_gfxPrimitives.h"
#include "../Frameworks/SDL2_gfx/SDL2_imageFilter.h"
#include "../Frameworks/SDL2_gfx/SDL2_rotozoom.h"

# define NUMBER_OF_FRAMES	8
# define F_FRATE			10

# define ABS_MINUS(a, b)	((a >= b) ? (a - b) : (b - a))
# define ABS(x)				((x >= 0) ? x : -x)

enum 				e_errcode
{
	ALLRIGHT,
	ERROR,
	NO_ROOMS,
	NO_ANTS,
	NO_STARTEND,
	MULTIPLE_STARTEND,
	NO_SOLUTION,
	LINK_TO_GHOST,
	NEGATIVE_ANTS,
	MAP_WRONG_ORDER,
	MAP_INVALID_NAME
};


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
	int				count_ants;
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
}					t_info;

typedef struct		s_ant
{
	SDL_Rect		start;
	SDL_Rect		end;
	int 			visible;
	int 			frame;
}					t_ant;

typedef struct 		s_anim
{
	SDL_Texture		*f_arr[NUMBER_OF_FRAMES];
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
	t_anim			anim;
	t_info			*info;
	int 			soviet;
	int 			w_width;
	int 			w_height;
	int 			quit;
	int 			key;

}					t_sdl;

/*
**	visuals related functions
*/
void	lem_sdl_control(t_info *info);
int		lem_sdl_init_main(t_sdl **lm, t_info *info);
int 	lem_sdl_loadmap(t_sdl *lm);
int 	lem_sdl_close(t_sdl *lm, int ret);
void	lem_sdl_addcolour(SDL_Color *c, int r, int g, int b, int a);
void	lem_sdl_anim_control(t_sdl *lm);
void	lem_sdl_setroompos(t_sdl *lm);
int		lem_sdl_init_font(t_sdl *lm);
void	lem_sdl_renderttext(t_sdl *lm);

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

/*
** finish related functions
*/
void				cleanup_info(t_info *info);
int					lem_errmsg(t_info *info, int errcode);


/*
**	algo functions
*/
void				end_vertc(t_info *info, char *str);
void				len_vrtc(t_info *info, int index);
void				path(t_info *info, char *str, int index);
void				workroom(t_info *info);
int					double_all_path(t_room *rooms, char *str);
int			double_end_path(t_room *rooms, char *str);
int			double_vrtc(t_info *info, int index);
int check_end(char *str, int index);
int check_len(t_info *info, int nbr);
int check_link(t_info *info, int index, int m);
void copy_path(t_path *path);
void len_vrtc_den(t_info *info, int index, char *str);
void weight(t_info *info);
void delite(t_info *info, t_path *path);
void clean_del(t_info *info);
int next_number(t_path *path, int index);
int check_denied(t_info *info, int index);
void	double_path(t_path *path, int index, int r);
void copy_prepath(t_path **path, int index);
void free_pathes(t_info *info, t_path **path, int count);


#endif
