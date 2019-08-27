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

int 		lem_sdl_init_loadmap(t_sdl *lm)
{
	SDL_Rect	rect;
	int 		r;

	r = 0;
	rect.w = sqrt((lm->w_height * lm->w_width) / lm->info->count_room) / 5 * 2;
	if (rect.w > 72)
		rect.w = 72;
	rect.h = rect.w;
	SDL_SetRenderDrawColor(lm->renderer, 0x00, 0xFF, 0x00, 0xFF);
	while (lm->info->rooms[r])
	{
		rect.x = r % (lm->w_height / (rect.w * 2) - 2) * rect.w + rect.w;
		rect.y = r % (lm->w_width / (rect.w * 2) - 2) * rect.w + rect.w;
		SDL_RenderFillRect(lm->renderer, &rect);
		r += 1;
	}
	return (0);
}

SDL_Texture *lem_sdl_init_loadt(t_sdl *lm, char *path)
{
	SDL_Texture *texture;
	SDL_Surface *surface;

	surface = IMG_Load(path);
	if (!surface)
		return (NULL);
	else
	{
		texture = SDL_CreateTextureFromSurface(lm->renderer, surface);
		if (!texture)
			return (NULL);
		SDL_FreeSurface(surface);
	}
	return (texture);
}

int		lem_sdl_init_main(t_sdl **lm, t_info *info)
{
	t_sdl	*tmp;
	int 	f_img;

	tmp = (t_sdl *)malloc(sizeof(t_sdl));
	ft_bzero(tmp, sizeof(t_sdl));
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		return (lem_sdl_close(tmp, 1));
	else
	{
		if (!(tmp->window = SDL_CreateWindow("Run, ants, run!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, tmp->w_width, tmp->w_height, SDL_WINDOW_FULLSCREEN_DESKTOP)))
			return(lem_sdl_close(tmp, 2));
		else
		{
			SDL_GetWindowSize(tmp->window, &tmp->w_width, &tmp->w_height);
			tmp->w_rect.x = 0;
			tmp->w_rect.y = 0;
			tmp->w_rect.w = tmp->w_width;
			tmp->w_rect.h = tmp->w_height;
			if (!(tmp->renderer = SDL_CreateRenderer(tmp->window, -1, SDL_RENDERER_ACCELERATED)))
				return (lem_sdl_close(tmp, 3));
			else
			{
				f_img = IMG_INIT_PNG;
				if (!(IMG_Init(f_img) & f_img))
					return (lem_sdl_close(tmp, 4));
				else if (!(tmp->ant = lem_sdl_init_loadt(tmp, "./res/antonio.png")))
					return (lem_sdl_close(tmp, 5));
			}
		}
	}
	tmp->info = info;
	*lm = tmp;
	return (0);
}