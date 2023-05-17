/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_maps2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:27:00 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 14:47:31 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_modify_with_max_neg(t_var *v, int max_neg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < v->nb_cols && j < v->nb_lines)
	{
		while (j < v->nb_lines)
		{
			v->map[i][j] -= max_neg;
			j++;
		}
		j = 0;
		i++;
	}
}

void	fdf_suppr_neg(t_var *v)
{
	int	max_neg;
	int	i;
	int	j;

	i = 0;
	j = 0;
	max_neg = 0;
	while (i < v->nb_cols && j < v->nb_lines)
	{
		while (j < v->nb_lines)
		{
			if (v->map[i][j] < max_neg)
				max_neg = v->map[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	if (max_neg < 0)
		fdf_modify_with_max_neg(v, max_neg);
}

void	parsing_map(t_var *v, char **av)
{
	char	*line;

	line = NULL;
	if (give_nb_col(v, av, &line))
	{
		if (give_nb_lines(v, &line))
		{
			if (create_empty_map(v))
			{
				fdf_fill_map(v, av, &line);
			}
		}
	}
}

void	fdf_divider_width(t_var *v, double *divider)
{
	*divider = (double)(double)v->nb_cols + (double)v->nb_lines;
	if (*divider == 2)
		*divider = 1;
	if (*divider == 3)
		*divider = 1.5;
	else
		*divider = *divider - 2;
}

void	fdf_divider_height(t_var *v, double *divider)
{
	*divider = (double)(((double)v->bigger_z + ((double)v->nb_cols \
		- (double)v->x_of_bigger_z) + ((double)v->nb_lines - \
		(double)v->y_of_bigger_z) - 2) / 2);
	if (*divider == 0)
		*divider = 1;
	if (*divider == 1)
		*divider = 1.5;
}
