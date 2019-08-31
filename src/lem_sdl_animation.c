/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_sdl_animation.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 14:12:49 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/30 14:12:50 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

//async animation

void		lem_sdl_anim_drawframe(t_sdl *lm, SDL_Rect pos, int frame)
{

	SDL_RenderCopy(lm->renderer, lm->anim.f_arr[frame], NULL, &pos);
}

SDL_Rect	lem_sdl_anim_getrect(SDL_Rect start, SDL_Rect end, int parts, int step)
{
	SDL_Rect	pos;
	float		x;
	float		y;

	pos.w = start.w;
	pos.h = start.h;
	if (!step)
		return (start);
	x = (float)start.x + ((float)ABS_MINUS(end.x, start.x) / (float)parts * (float)step);
	y = (float)start.y + ((float)ABS_MINUS(end.y, start.y) / (float)parts * (float)step);
	pos.x = (int)x;
	pos.y = (int)y;
//	printf("x: %f | y: %f |sx: %d | sy: %d | ex: %d | ey: %d | px: %d| py: %d | parts: %d | step: %d\n", x, y, start.x, start.y, end.x, end.y, pos.x, pos.y, parts, step);
	return (pos);
}

void		lem_sdl_anim_control(t_sdl *lm)
{
	int			i;
	int 		frame;
	SDL_Rect	pos;

	i = 0;
	while (i < lm->anim.ant_all)
	{
		frame = lm->anim.ants[i].frame;
		pos = lem_sdl_anim_getrect(lm->anim.ants[i].start,
				lm->anim.ants[i].end, lm->anim.parts, lm->anim.step);
		lem_sdl_anim_drawframe(lm, pos,
				lm->anim.ants[i].frame / F_FRATE);
		lm->anim.ants[i].frame = (frame >= NUMBER_OF_FRAMES * F_FRATE - 1)
				? 0 : (frame + 1);
		i += 1;
	}
	lm->anim.step = (lm->anim.step == lm->anim.parts) ? 0 : (lm->anim.step + 1);
}