/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 15:34:11 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 14:42:18 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_determine_color(t_var *v, int z0, int zn, t_line point)
{
	if (z0 == 0 && zn == 0)
		fdf_bresenham(point, &v->img, WHITE);
	else if (z0 < zn || z0 > zn)
		fdf_bresenham(point, &v->img, D_GREEN);
	else
	{
		if (z0 > v->bigger_z / 2)
			fdf_bresenham(point, &v->img, PINK);
		else
			fdf_bresenham(point, &v->img, FUSHIA);
	}
}

void	draw_to_right(t_var *v, t_fdf_lst *pointed)
{
	t_fdf_lst	*other;
	t_line		point;

	other = pointed->next;
	point.x0 = pointed->x;
	point.y0 = pointed->y;
	point.xn = other->x;
	point.yn = other->y;
	fdf_determine_color(v, pointed->z, other->z, point);
}

void	draw_to_up(t_var *v, t_fdf_lst *pointed)
{
	t_fdf_lst	*other;
	t_line		point;

	other = fdf_which_link(v->lst, pointed->x_in_tab, (pointed->y_in_tab) - 1);
	if (!other)
		return ;
	point.x0 = pointed->x;
	point.y0 = pointed->y;
	point.xn = other->x;
	point.yn = other->y;
	fdf_determine_color(v, pointed->z, other->z, point);
}

void	fdf_draw_list(t_var *v)
{
	t_fdf_lst	*pointed;

	pointed = v->lst;
	while (pointed != NULL)
	{
		if (pointed->y_in_tab == 0 && pointed->x_in_tab != v->nb_cols - 1)
			draw_to_right(v, pointed);
		else if (pointed->y_in_tab != 0 && pointed->x_in_tab == v->nb_cols - 1)
			draw_to_up(v, pointed);
		else if (pointed->y_in_tab != 0 && pointed->x_in_tab != v->nb_cols - 1)
		{
			draw_to_up(v, pointed);
			draw_to_right(v, pointed);
		}
		pointed = pointed->next;
	}
}
