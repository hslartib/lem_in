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

void		lem_sdl_music(t_sdl *lm)
{
	if (lm->soviet)
		system("afplay ./res/r_alert.mp3 &");
	else
		system("pkill afplay");
}

void		lem_sdl_anim_drawframe(t_sdl *lm, SDL_Rect pos, int frame)
{
	int i;

	i = lm->soviet ? NUMBER_OF_FRAMES : 0;
	SDL_RenderCopy(lm->renderer, lm->anim.f_arr[frame + i], NULL, &pos);
}

SDL_Rect	lem_sdl_anim_getrect(t_sdl *lm, int i)
{
	t_ant		*ant;
	SDL_Rect	ret;
	SDL_Rect	start;
	SDL_Rect	end;

	ant  = &lm->anim.ants[i];
	if (!ant->visible || ant->visible == -1)
	{
		if (ant->visible != -1 && (!lm->anim.step &&
			(i == 0 || (lm->anim.ants[i - 1].path[0] ==
			ant->path[0] && lm->anim.ants[i - 1].step > 0)
			|| (lm->anim.ants[i - 1].path[1] != ant->path[1]))))
			ant->visible = 1;
		else
			return ((SDL_Rect){0, 0, 0, 0});
	}
	if (ant->step == (ant->p_len - 1) && (ant->visible = -1))
		return ((SDL_Rect){0, 0, 0, 0});
	start = lm->info->rooms[ant->path[ant->step]]->pos;
	end = lm->info->rooms[ant->path[ant->step + 1]]->pos;
	ret.w = lm->anim.a_width;
	ret.h = lm->anim.a_height;
	ret.x = (int)((float)start.x + ((float)(end.x - start.x) *
			(float)lm->anim.step / (float)lm->anim.parts)) + ret.w / 2;
	ret.y = (int)((float)start.y + ((float)(end.y - start.y) *
			(float)lm->anim.step / (float)lm->anim.parts)) - ret.h / 2;
	return (ret);
}

void		lem_sdl_anim_control(t_sdl *lm)
{
	int			i;
	int			frame;
	SDL_Rect	pos;

	i = 0;
	while (i < lm->anim.ant_all)
	{
		frame = lm->anim.ants[i].frame;
		pos = lem_sdl_anim_getrect(lm, i);
		if (pos.w)
		{
			lem_sdl_anim_drawframe(lm, pos,
								   lm->anim.ants[i].frame / F_FRATE);
			lm->anim.ants[i].frame = (frame >= NUMBER_OF_FRAMES * F_FRATE - 1)
									 ? 0 : (frame + 1);
			if (lm->anim.step == lm->anim.parts)
				lm->anim.ants[i].step += 1;
		}
		i += 1;
	}
	lm->anim.step = (lm->anim.step == lm->anim.parts) ? 0 : (lm->anim.step + 1);
}

void		lem_sdl_anim_static(t_sdl *lm)
{
	int			i;
	int			frame;
	SDL_Rect	pos;

	i = 0;
	lem_sdl_draw_background(lm);
	while (i < lm->anim.ant_all)
	{
		if (lm->anim.ants[i].step && (lm->anim.ants[i].step < lm->anim.ants[i].p_len - 1))
		{
			frame = lm->anim.ants[i].frame;
			pos = lm->info->rooms[lm->anim.ants[i].path[lm->anim.ants[i].step]]->pos;
			pos.x += lm->anim.a_width / 2;
			pos.y -= lm->anim.a_height / 2;
			pos.w = lm->anim.a_width;
			pos.h = lm->anim.a_height;
			lem_sdl_anim_drawframe(lm, pos,
			   lm->anim.ants[i].frame / F_FRATE);
			lm->anim.ants[i].frame = (frame >= NUMBER_OF_FRAMES * F_FRATE - 1)
				? 0 : (frame + 1);
		}
		i += 1;
	}
	SDL_RenderPresent(lm->renderer);
}
