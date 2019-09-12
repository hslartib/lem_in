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

int		lem_sdl_close(t_sdl *lm, int ret)
{
	int i;

	i = -1;
	if (!lm)
		return (ret);
	while (++i < NUMBER_OF_FRAMES * 2)
	{
		if (lm->anim.f_arr[i])
			SDL_DestroyTexture(lm->anim.f_arr[i]);
		if (i < 4)
			SDL_DestroyTexture(lm->text[i]);
	}
	TTF_CloseFont(lm->font);
	SDL_DestroyRenderer(lm->renderer);
	SDL_DestroyWindow(lm->window);
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
	if (lm)
		free(lm);
	system("pkill afplay");
	return (ret);
}

void	lem_sdl_anims_wrap(t_sdl *lm)
{
	lem_sdl_anim_static(lm);
	SDL_RenderPresent(lm->renderer);
}
