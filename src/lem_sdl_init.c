/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_sdl_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:54:01 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/27 15:54:02 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

SDL_Texture		*lem_sdl_init_loadt(t_sdl *tmp, char *path)
{
	SDL_Texture *texture;
	SDL_Surface *surface;

	surface = IMG_Load(path);
	if (!surface)
		return (NULL);
	else
	{
		texture = SDL_CreateTextureFromSurface(tmp->renderer, surface);
		if (!texture)
			return (NULL);
		SDL_FreeSurface(surface);
	}
	return (texture);
}

int				lem_sdl_init_loadanim(t_sdl *tmp)
{
	if (!(tmp->anim.f_arr[0] = lem_sdl_init_loadt(tmp, "./res/0.png")))
		return (1);
	if (!(tmp->anim.f_arr[1] = lem_sdl_init_loadt(tmp, "./res/1.png")))
		return (1);
	if (!(tmp->anim.f_arr[2] = lem_sdl_init_loadt(tmp, "./res/2.png")))
		return (1);
	if (!(tmp->anim.f_arr[3] = lem_sdl_init_loadt(tmp, "./res/3.png")))
		return (1);
	if (!(tmp->anim.f_arr[4] = lem_sdl_init_loadt(tmp, "./res/4.png")))
		return (1);
	if (!(tmp->anim.f_arr[5] = lem_sdl_init_loadt(tmp, "./res/5.png")))
		return (1);
	if (!(tmp->anim.f_arr[6] = lem_sdl_init_loadt(tmp, "./res/6.png")))
		return (1);
	if (!(tmp->anim.f_arr[7] = lem_sdl_init_loadt(tmp, "./res/7.png")))
		return (1);
	return (0);
}

int 			lem_sdl_init_anim_ants(t_anim *anim, t_path *path)
{
	int			r;
	int 		a;

	r = 0;
	a = 0;
	while (r < path->count_root)
	{
		while (path->count_ant[r] > 0)
		{
			anim->ants[a].path = path->root[r];
			anim->ants[a].p_len = path->len_root[r];
			anim->ants[a].step = 0;
			anim->ants[a].visible = 0;
			anim->ants[a].frame = rand() % (NUMBER_OF_FRAMES * F_FRATE);
			path->count_ant[r] -= 1;
			a += 1;
		}
		r += 1;
	}
	return (0);
}

int				lem_sdl_init_anim(t_sdl *tmp)
{
	tmp->anim.a_width = (sqrt((tmp->w_height * tmp->w_width)
			/ tmp->info->count_room) + 1) / 2 * 78 / 90;
	tmp->anim.a_height = (sqrt((tmp->w_height * tmp->w_width)
			/ tmp->info->count_room) + 1) / 2 * 90 / 78;
	tmp->anim.a_width > 90 ? (tmp->anim.a_width = 90) : 0;
	tmp->anim.a_height > 78 ? (tmp->anim.a_height = 78) : 0;
	tmp->anim.parts = 100;
	tmp->anim.step = 0;
	tmp->anim.ant_all = tmp->info->count_ants;
	tmp->anim.waiting = tmp->anim.ant_all;
	tmp->anim.ants = (t_ant *)malloc(sizeof(t_ant) * tmp->anim.ant_all);
	lem_sdl_init_anim_ants(&tmp->anim, tmp->info->sdl_path);
	return (0);
}

int				lem_sdl_init_setrender(t_sdl *tmp)
{
	int		f_img;

	SDL_GetWindowSize(tmp->window, &tmp->w_width, &tmp->w_height);
	tmp->w_rect.x = 0;
	tmp->w_rect.y = 0;
	tmp->w_rect.w = tmp->w_width;
	tmp->w_rect.h = tmp->w_height;
	if (!(tmp->renderer = SDL_CreateRenderer(
tmp->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
		return (lem_sdl_close(tmp, 3));
	else
	{
		f_img = IMG_INIT_PNG;
		if (!(IMG_Init(f_img) & f_img))
			return (lem_sdl_close(tmp, 4));
		else if (lem_sdl_init_loadanim(tmp))
			return (lem_sdl_close(tmp, 5));
	}
	return (0);
}

int				lem_sdl_init_main(t_sdl **lm, t_info *info)
{
	t_sdl	*tmp;

	tmp = (t_sdl *)malloc(sizeof(t_sdl));
	ft_bzero(tmp, sizeof(t_sdl));
	tmp->c_room = (SDL_Color){100, 100, 100, 100};
	tmp->c_path = tmp->c_room;
	tmp->info = info;
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (lem_sdl_close(tmp, 1));
	else
	{
		if (!(tmp->window = SDL_CreateWindow(
				"Run, ants, run!", SDL_WINDOWPOS_UNDEFINED,
				SDL_WINDOWPOS_UNDEFINED, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP)))
			return (lem_sdl_close(tmp, 2));
		else if (lem_sdl_init_setrender(tmp))
			return (3);
	}
	lem_sdl_init_anim(tmp);
	SDL_SetRenderDrawBlendMode(tmp->renderer, SDL_BLENDMODE_ADD);
	lem_sdl_init_font(tmp);
	lem_sdl_setroompos(tmp);
	*lm = tmp;
	return (0);
}
