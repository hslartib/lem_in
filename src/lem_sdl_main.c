/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_vis_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 15:46:44 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/27 15:46:45 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

/*
 * enclose in cicle
 * animate by group
 */

void 	lem_sdl_addcolour(SDL_Color *color, int r, int g, int b, int a)
{
	if (color->r + r < 50 || color->r + r > 240)
		return ;
	color->r += r;
	color->g += g;
	color->b += b;
	color->a += a;
}

void	lem_sdl_handle_more_events(SDL_Event e, t_sdl *lm)
{
	if (e.key.keysym.sym == SDLK_s)
		lm->soviet = 1;
	if (e.key.keysym.sym == SDLK_g)
		lm->soviet = 0;
	if (e.key.keysym.sym == SDLK_f)
		lm->flow = lm->flow ? 0 : 1;
	if (e.key.keysym.sym == SDLK_m)
		lm->move = 1;
}

void	lem_sdl_handle_events(SDL_Event e, t_sdl *lm)
{
	if (e.type == SDL_QUIT)
		lm->quit = 1;
	else if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
			lm->quit = 1;
		else if (e.key.keysym.sym == SDLK_LEFTBRACKET)
			lem_sdl_addcolour(&lm->c_path, -10, -10, -10, -10);
		else if (e.key.keysym.sym == SDLK_RIGHTBRACKET)
			lem_sdl_addcolour(&lm->c_path, 10, 10, 10, 10);
		else if (e.key.keysym.sym == SDLK_QUOTE)
			lem_sdl_addcolour(&lm->c_room, -10, -10, -10, -10);
		else if (e.key.keysym.sym == SDLK_BACKSLASH)
			lem_sdl_addcolour(&lm->c_room, 10, 10, 10, 10);
		else if (e.key.keysym.sym == SDLK_EQUALS)
			lm->anim.parts += 10;
		else if (e.key.keysym.sym == SDLK_MINUS)
			lm->anim.parts >= 100 ? lm->anim.parts -= 10 : 0;
		else
			lem_sdl_handle_more_events(e, lm);
		if (lm->anim.step >= lm->anim.parts)
			lm->anim.step = lm->anim.parts - 1;
	}
}

void	lem_sdl_control(t_info *info)
{
	t_sdl *lm;

	lem_sdl_init_main(&lm, info);
	while (!lm->quit)
	{
		while (SDL_PollEvent(&lm->event))
			lem_sdl_handle_events(lm->event, lm);
		if (lm->flow || lm->move)
		{
			while (!NULL)
			{
				while (SDL_PollEvent(&lm->event))
					lem_sdl_handle_events(lm->event, lm);
				SDL_SetRenderDrawColor(lm->renderer, 0x00, 0x00, 0x00, 0x00);
				SDL_RenderClear(lm->renderer);
				lem_sdl_loadmap(lm);
				lem_sdl_anim_control(lm);
				lem_sdl_renderttext(lm);
				SDL_RenderPresent(lm->renderer);
				if (!lm->anim.step)
					break ;
			}
			lm->move = 0;
		}
		if (lm->anim.arrived != lm->anim.ant_all)
			lem_sdl_anim_static(lm);
	}
	lem_sdl_close(lm, 0);
}
