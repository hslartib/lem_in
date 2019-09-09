/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_sdl_loadres.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 13:04:31 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/09 13:04:32 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

SDL_Texture		*lem_sdl_init_loadt(t_sdl *tmp, char *path)
{
	SDL_Texture *texture;
	SDL_Surface *surface;

	surface = IMG_Load(path);
	if (!surface)
		return (NULL);
	else
	{
		texture = SDL_CreateTextureFromSurface(tmp->renderer, surface);
		if (!texture)
			return (NULL);
		SDL_FreeSurface(surface);
	}
	return (texture);
}

int				lem_sdl_init_loadanimrev(t_sdl *tmp)
{
	int i;

	i = NUMBER_OF_FRAMES;
	if (!(tmp->anim.f_arr[0 + i] = lem_sdl_init_loadt(tmp, "./res/r0.png")))
		return (1);
	if (!(tmp->anim.f_arr[1 + i] = lem_sdl_init_loadt(tmp, "./res/r1.png")))
		return (1);
	if (!(tmp->anim.f_arr[2 + i] = lem_sdl_init_loadt(tmp, "./res/r2.png")))
		return (1);
	if (!(tmp->anim.f_arr[3 + i] = lem_sdl_init_loadt(tmp, "./res/r3.png")))
		return (1);
	if (!(tmp->anim.f_arr[4 + i] = lem_sdl_init_loadt(tmp, "./res/r4.png")))
		return (1);
	if (!(tmp->anim.f_arr[5 + i] = lem_sdl_init_loadt(tmp, "./res/r5.png")))
		return (1);
	if (!(tmp->anim.f_arr[6 + i] = lem_sdl_init_loadt(tmp, "./res/r6.png")))
		return (1);
	if (!(tmp->anim.f_arr[7 + i] = lem_sdl_init_loadt(tmp, "./res/r7.png")))
		return (1);
	if (!(tmp->s_flag = lem_sdl_init_loadt(tmp, "./res/s_flag.png")))
		return (1);
	SDL_SetTextureBlendMode(tmp->s_flag, SDL_BLENDMODE_BLEND);
	SDL_SetTextureAlphaMod(tmp->s_flag, 27);
	return (0);
}

int				lem_sdl_init_loadanim(t_sdl *tmp)
{
	if (!(tmp->anim.f_arr[0] = lem_sdl_init_loadt(tmp, "./res/0.png")))
		return (1);
	if (!(tmp->anim.f_arr[1] = lem_sdl_init_loadt(tmp, "./res/1.png")))
		return (1);
	if (!(tmp->anim.f_arr[2] = lem_sdl_init_loadt(tmp, "./res/2.png")))
		return (1);
	if (!(tmp->anim.f_arr[3] = lem_sdl_init_loadt(tmp, "./res/3.png")))
		return (1);
	if (!(tmp->anim.f_arr[4] = lem_sdl_init_loadt(tmp, "./res/4.png")))
		return (1);
	if (!(tmp->anim.f_arr[5] = lem_sdl_init_loadt(tmp, "./res/5.png")))
		return (1);
	if (!(tmp->anim.f_arr[6] = lem_sdl_init_loadt(tmp, "./res/6.png")))
		return (1);
	if (!(tmp->anim.f_arr[7] = lem_sdl_init_loadt(tmp, "./res/7.png")))
		return (1);
	if (lem_sdl_init_loadanimrev(tmp))
		return (1);
	return (0);
}
