/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_events.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 12:01:52 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 16:22:56 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	deal_key(int key, void *param)
{
	(void)param;
	if (key == KEY_ESC)
		exit (0);
	return (0);
}

int	fdf_close_window(void *param)
{
	(void)param;
	exit(0);
	return (0);
}

void	fdf_pixel_color(t_infos *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->str + (y * img->line_length + x * (img->bpp / sizeof(char *)));
	*(unsigned int *)pixel = color;
}
