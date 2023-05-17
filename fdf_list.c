/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:31:14 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 14:45:15 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_create_list(t_var *v)
{
	int			i;
	int			j;
	t_fdf_lst	*buf;

	v->lst = fdf_lstnew(0, 0);
	i = 1;
	j = 0;
	while (i < v->nb_cols && j < v->nb_lines)
	{
		while (i < v->nb_cols)
		{
			if (!v->lst)
				return (0);
			buf = fdf_lstnew(i, j);
			fdf_lstadd_back(&(v->lst), buf);
			i++;
		}
		i = 0;
		j++;
	}
	return (1);
}

void	fdf_modify_coor_in_isometric(t_var *v)
{
	t_fdf_lst	*buf;

	buf = v->lst;
	while (buf != NULL)
	{
		buf->x = ((buf->x_in_tab - buf->y_in_tab) * v->pix_per_side * 2) \
			+ v->x_of_00;
		buf->y = ((buf->x_in_tab + buf->y_in_tab) * v->pix_per_side) \
			+ v->y_of_00;
		buf = buf->next;
	}
}

void	fdf_add_z(t_var *v)
{
	int			i;
	int			j;
	t_fdf_lst	*buf;

	i = 0;
	j = 0;
	buf = v->lst;
	while (j < v->nb_lines)
	{
		while (i < v->nb_cols)
		{
			buf->y = buf->y - v->map[i][j] * v->pix_per_side;
			buf->z = v->map[i][j];
			i++;
			buf = buf->next;
		}
		i = 0;
		j++;
	}
}

void	fdf_verify_y(t_var *v)
{
	t_fdf_lst	*buf;
	int			y_min;
	int			dif;

	dif = 0;
	buf = v->lst;
	y_min = buf->y;
	while (buf != NULL)
	{
		if (buf->y < y_min)
			y_min = buf->y;
		buf = buf->next;
	}
	if (y_min < MARGE)
	{	
		dif = MARGE - y_min;
		buf = v->lst;
		while (buf != NULL)
		{
			buf->y += dif;
			buf = buf->next;
		}
	}
}

void	fdf_determine_00(t_var *v)
{
	int	marge_y;
	int	marge_x;

	marge_x = (v->img_size_width - (2 * MARGE) - \
		(v->nb_tuils_in_width * v->pix_per_side * 2)) / 2;
	marge_y = ((v->img_size_height) - (2 * MARGE) - (v->nb_tuils_in_height \
		* v->pix_per_side * 2)) / 2;
	v->x_of_00 = (v->nb_lines - 1) * v->pix_per_side * 2 + MARGE + marge_x;
	v->y_of_00 = (int)((MARGE + marge_y + (double) \
		((double)v->nb_tuils_in_height * (double)v->pix_per_side * 2)) \
		- (((double)(v->nb_lines - 1 + v->nb_cols - 1) * \
		(double)v->pix_per_side)));
	if (v->y_of_00 < MARGE)
		v->y_of_00 = MARGE;
}
