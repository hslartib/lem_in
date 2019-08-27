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

void	lem_sdl_control(t_info *info)
{
	t_sdl *lm;

	lem_sdl_init_main(&lm, info);
	while (!lm->quit)
	{
		while (SDL_PollEvent(&lm->event))
		{
			if(lm->event.type == SDL_QUIT || (lm->event.type == SDL_KEYDOWN && lm->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
				lm->quit = 1;
		}
		SDL_SetRenderDrawColor(lm->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(lm->renderer);
		lem_sdl_init_loadmap(lm);
		SDL_RenderPresent(lm->renderer);
	}

	lem_sdl_close(lm, 0);
}