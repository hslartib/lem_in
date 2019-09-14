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
	SDL_Rect	r;
	double		side;
	int			parts_y;

	side = (sqrt(((lm->w_height - 320) * (lm->w_width - 180))
			/ lm->info->count_room) + 1) / 2;
	r.w = side * lm->w_width / lm->w_height;
	r.h = side * lm->w_height / lm->w_width;
	if ((r.w > 160 || r.h > 90) && (r.w = 160))
		r.h = 90;
	parts_y = ((lm->w_height - 320) / r.h) / 2 - 2;
	r.x = (i / parts_y) * r.w * 32 / 19 - r.w / 2 +
	(lm->w_width - (lm->info->count_room * r.w / parts_y * 32 / 19)) / 2;
	r.y = (i % parts_y) * r.h * 2 +
			(lm->w_height - (r.h * parts_y * 2)) / 2;
	!((i / parts_y) % 2) ? r.y += r.h * 2 : 0;
	!(i % 2) ? r.x += r.w / 2 : 0;
	if ((r.w > 72 || r.h > 40) && (r.w = 72))
		r.h = 40;
	if (i == lm->info->start || i == lm->info->end)
	{
		r.x = (lm->w_width / 2) - (r.w / 2);
		r.y = (i == lm->info->start) ? (r.w) : (lm->w_height - r.w * 3 / 2);
	}
	return (r);
}

void		lem_sdl_setroompos(t_sdl *lm)
{
	int r;

	r = 0;
	while (lm->info->rooms[r])
	{
		lm->info->rooms[r]->pos = lem_sdl_getcoord(lm, r);
		r += 1;
	}
}

void		lem_sdl_loadrooms(t_sdl *lm)
{
	SDL_Rect	rect;
	int			r;

	r = 0;
	while (lm->info->rooms[r])
	{
		rect = lm->info->rooms[r]->pos;
		SDL_SetRenderDrawColor(lm->renderer, lm->c_room.r,
				lm->c_room.g, lm->c_room.b, lm->c_room.a);
		SDL_RenderFillRect(lm->renderer, &rect);
		r += 1;
	}
}

void		lem_sdl_loadpath(t_sdl *lm)
{
	SDL_Rect	rect;
	SDL_Rect	l_rect;
	int			r;
	int			l;

	r = 0;
	while (lm->info->rooms[r])
	{
		rect = lm->info->rooms[r]->pos;
		l = 0;
		while (l < lm->info->rooms[r]->links_len)
		{
			l_rect = lm->info->rooms[lm->info->rooms[r]->links[l]]->pos;
			SDL_SetRenderDrawColor(lm->renderer,
					lm->c_path.r, lm->c_path.g, lm->c_path.b, lm->c_path.a);
			SDL_RenderDrawLine(lm->renderer,
					(rect.x + rect.w / 2), (rect.y + rect.h / 2),
					(l_rect.x + l_rect.w / 2), (l_rect.y + l_rect.h / 2));
			l += 1;
		}
		r += 1;
	}
}
