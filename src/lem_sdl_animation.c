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

void 	lem_sdl_anim_drawframe(t_sdl *lm, int x, int y, int frame)
{
	SDL_Rect rect;

	rect.w = lm->frame_pos.w;
	rect.h = lm->frame_pos.h;
	rect.x = x;
	rect.y = y;
	SDL_RenderCopy(lm->renderer, lm->anim[frame], NULL, &rect);
}

