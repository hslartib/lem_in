/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_sdl_close.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/27 16:19:08 by dbrady            #+#    #+#             */
/*   Updated: 2019/08/27 16:19:09 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

int 	lem_sdl_close(t_sdl *lm, int ret)
{
	int i;

	i = -1;
	while (++i < NUMBER_OF_FRAMES)
		if (lm->anim.f_arr[i])
			SDL_DestroyTexture(lm->anim.f_arr[i]);
	SDL_DestroyRenderer(lm->renderer);
	SDL_DestroyWindow(lm->window);
	SDL_Quit();
	if (lm)
		free(lm);
	return (ret);
}