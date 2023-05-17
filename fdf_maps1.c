/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_maps1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:30:08 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 14:46:57 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_bigger_z(t_var *v)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	v->x_of_bigger_z = 0;
	v->y_of_bigger_z = 0;
	v->bigger_z = v->map[i][j];
	while (i < v->nb_cols && j < v->nb_lines)
	{
		while (j < v->nb_lines)
		{
			if (v->map[i][j] > v->bigger_z)
			{	
				v->bigger_z = v->map[i][j];
				v->x_of_bigger_z = i;
				v->y_of_bigger_z = j;
			}	
			j++;
		}
		j = 0;
		i++;
	}
}

void	fdf_tuils(t_var *v)
{
	double	divider_w;
	double	divider_h;

	fdf_divider_width(v, &divider_w);
	fdf_divider_height(v, &divider_h);
	v->nb_tuils_in_height = divider_h;
	v->nb_tuils_in_width = divider_w;
}

void	fdf_pix_per_side(t_var *v, double space, double nb_tuils)
{
	double	pix;

	pix = space;
	while (pix * nb_tuils > space)
		pix--;
	v->pix_per_side = (int)(pix / 2);
}

void	fdf_how_many_pixels(t_var *v)
{
	double	free_width;
	double	free_height;
	double	buf_w;
	double	buf_h;

	free_width = v->img_size_width - 2 * MARGE;
	free_height = v->img_size_height - 2 * MARGE;
	buf_w = free_width / v->nb_tuils_in_width;
	buf_h = free_height / v->nb_tuils_in_height;
	if (buf_w < buf_h)
		fdf_pix_per_side(v, free_width, v->nb_tuils_in_width);
	else
		fdf_pix_per_side(v, free_height, v->nb_tuils_in_height);
}

int	fdf_map(int ac, char **av, t_var *v)
{	
	v->map = NULL;
	if (!checks(ac, av))
		return (0);
	parsing_map(v, av);
	close (v->fd);
	if (!v->map)
		return (0);
	fdf_suppr_neg(v);
	fdf_bigger_z(v);
	fdf_tuils(v);
	fdf_how_many_pixels(v);
	return (1);
}
