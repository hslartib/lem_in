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

SDL_Texture *lem_sdl_init_loadt(t_sdl *tmp, char *path)
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

int 	lem_sdl_init_loadanim(t_sdl *tmp)
{
	if (!(tmp->anim[0] = lem_sdl_init_loadt(tmp, "./res/0.png")))
		return (1);
	if (!(tmp->anim[1] = lem_sdl_init_loadt(tmp, "./res/1.png")))
		return (1);
	if (!(tmp->anim[2] = lem_sdl_init_loadt(tmp, "./res/2.png")))
		return (1);
	if (!(tmp->anim[3] = lem_sdl_init_loadt(tmp, "./res/3.png")))
		return (1);
	if (!(tmp->anim[4] = lem_sdl_init_loadt(tmp, "./res/4.png")))
		return (1);
	if (!(tmp->anim[5] = lem_sdl_init_loadt(tmp, "./res/5.png")))
		return (1);
	if (!(tmp->anim[6] = lem_sdl_init_loadt(tmp, "./res/6.png")))
		return (1);
	if (!(tmp->anim[7] = lem_sdl_init_loadt(tmp, "./res/7.png")))
		return (1);
	return (0);
}

int 	lem_sdl_init_setrender(t_sdl *tmp)
{
	int 	f_img;

	SDL_GetWindowSize(tmp->window, &tmp->w_width, &tmp->w_height);
	tmp->w_rect.x = 0;
	tmp->w_rect.y = 0;
	tmp->w_rect.w = tmp->w_width;
	tmp->w_rect.h = tmp->w_height;
	if (!(tmp->renderer = SDL_CreateRenderer(tmp->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)))
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

int		lem_sdl_init_main(t_sdl **lm, t_info *info)
{
	t_sdl	*tmp;

	tmp = (t_sdl *)malloc(sizeof(t_sdl));
	tmp->f_pos = (SDL_Rect *)malloc(sizeof(SDL_Rect) * (*lm)->info->count_ants);
	ft_bzero(tmp, sizeof(t_sdl));
	ft_bzero(tmp->f_pos, sizeof(sizeof(SDL_Rect) * (*lm)->info->count_ants));
	lem_sdl_addcolour(&tmp->c_room, 100, 100, 100, 100);
	lem_sdl_addcolour(&tmp->c_path, 100, 100, 100, 100);
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (lem_sdl_close(tmp, 1));
	else
	{
		if (!(tmp->window = SDL_CreateWindow("Run, ants, run!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, tmp->w_width, tmp->w_height, SDL_WINDOW_FULLSCREEN_DESKTOP)))
			return(lem_sdl_close(tmp, 2));
		else
			if (lem_sdl_init_setrender(tmp))
				return (3);
	}
	SDL_SetRenderDrawBlendMode(tmp->renderer, SDL_BLENDMODE_ADD);
	tmp->info = info;
	*lm = tmp;
	return (0);
}