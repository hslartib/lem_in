/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_sdl_loadmap.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/28 21:04:00 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/28 21:04:01 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

SDL_Rect	lem_sdl_getcoord(t_sdl *lm, int i)
{
	SDL_Rect	rect;
	int 		side;
	int 		parts_x;
	int 		parts_y;

	side = (sqrt((lm->w_height * lm->w_width) / lm->info->count_room) + 1) / 5 * 2;
	rect.w = side * lm->w_width / lm->w_height;
	rect.h = side * lm->w_height / lm->w_width;
	if (rect.w > 160 || rect.h > 90)
	{
		rect.w = 160;
		rect.h = 90;
	}
	parts_x = (lm->w_width / rect.w) / 5 * 2 - 2;
	parts_y = (lm->w_height / rect.h) / 5 * 2 - 2;
	rect.x = (i % parts_x + 1) * rect.w * 5 / 2 + rect.w;
	rect.y = (i % parts_y + 1) * rect.h * 5 / 2 + rect.h;
	if (rect.w > 72 || rect.h > 40)
	{
		rect.w = 72;
		rect.h = 40;
	}
	return (rect);
}

void		lem_sdl_loadrooms(t_sdl *lm)
{
	SDL_Rect	rect;
	int 		r;

	r = 0;
	while (lm->info->rooms[r])
	{
		rect = lem_sdl_getcoord(lm, r);
		SDL_SetRenderDrawColor(lm->renderer, lm->c_room.r, lm->c_room.g, lm->c_room.b, lm->c_room.a);
		SDL_RenderFillRect(lm->renderer, &rect);
		r += 1;
	}
}

void		lem_sdl_loadpath(t_sdl *lm)
{
	SDL_Rect	rect;
	SDL_Rect	l_rect;
	int 		r;
	int 		l;

	r = 0;
	while (lm->info->rooms[r])
	{
		rect = lem_sdl_getcoord(lm, r);
		l = 0;
		while (l < lm->info->rooms[r]->links_len)
		{
			l_rect = lem_sdl_getcoord(lm, lm->info->rooms[r]->links[l]);
			SDL_SetRenderDrawColor(lm->renderer, lm->c_path.r, lm->c_path.g, lm->c_path.b, lm->c_path.a);
			SDL_RenderDrawLine(lm->renderer, (rect.x + rect.w / 2), (rect.y + rect.h / 2), (l_rect.x + l_rect.w / 2), (l_rect.y + l_rect.h / 2));
			l += 1;
		}

		r += 1;
	}
}

int 		lem_sdl_loadmap(t_sdl *lm)
{
	lem_sdl_loadpath(lm);
	lem_sdl_loadrooms(lm);
	return (0);
}