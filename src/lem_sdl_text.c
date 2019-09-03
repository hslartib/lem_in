/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_sdl_text.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbrady <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 14:15:28 by dbrady            #+#    #+#             */
/*   Updated: 2019/09/03 14:15:30 by dbrady           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_strt.h"

SDL_Texture	*lem_sdl_init_loadft(t_sdl *lm, char *text, SDL_Color color)
{
	SDL_Surface *surface;
	SDL_Texture *texture;


	surface = TTF_RenderText_Blended(lm->font, text, color);
	if (!surface)
		return (NULL);
	else
	{
		texture = SDL_CreateTextureFromSurface(lm->renderer, surface);
		if (!texture)
			return (NULL);
		SDL_FreeSurface(surface);
	}
	return (texture);
}

int		lem_sdl_init_font(t_sdl *lm)
{
	if (TTF_Init())
		return (1);
	if (!(lm->font = TTF_OpenFont("./res/Amatic-Bold.ttf", 42)))
		return (2);
	if (!(lm->text[0] = lem_sdl_init_loadft(lm, "waiting", (SDL_Color){1, 255, 255, 255})))
		return (3);
	if (!(lm->text[1] = lem_sdl_init_loadft(lm, "arrived", (SDL_Color){1, 255, 255, 255})))
		return (3);
	if (!(lm->text[2] = lem_sdl_init_loadft(lm, "waiting", (SDL_Color){255, 1, 1, 255})))
		return (3);
	if (!(lm->text[3] = lem_sdl_init_loadft(lm, "arrived", (SDL_Color){255, 1, 1, 255})))
		return (3);
	return (0);
}

void	lem_sdl_renderttext(t_sdl *lm)
{
	int i;
	int w;
	int h;

	i = !lm->soviet ? 0 : 2;
	i = 2;
	SDL_QueryTexture(lm->text[0 + i], NULL, NULL, &w, &h);
	SDL_RenderCopy(lm->renderer, lm->text[0 + i], NULL, &(SDL_Rect){21, 21, w, h});
	SDL_QueryTexture(lm->text[1 + i], NULL, NULL, &w, &h);
	SDL_RenderCopy(lm->renderer, lm->text[1 + i], NULL, &(SDL_Rect){lm->w_width - w - 21, 21, w, h});
}