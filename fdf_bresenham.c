/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bresenham.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:55:24 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 14:41:59 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	fdf_bre_x(t_line point, t_bre *b, t_infos *img)
{
	fdf_pixel_color(img, b->x, b->y, b->color);
	while (b->x < b->xn)
	{
		(b->x)++;
		if (b->pk < 0)
			b->pk = b->pk + 2 * b->delta_y;
		else
		{
			if (point.y0 < point.yn)
				(b->y)++;
			else
				(b->y)--;
			b->pk = b->pk + 2 * b->delta_y - 2 * b->delta_x;
		}
		fdf_pixel_color(img, b->x, b->y, b->color);
	}
}

void	fdf_bre_y(t_line point, t_bre *b, t_infos *img)
{
	fdf_pixel_color(img, b->x, b->y, b->color);
	while (b->y < b->yn)
	{
		(b->y)++;
		if (b->pk < 0)
			b->pk = b->pk + 2 * b->delta_x;
		else
		{
			if (point.y0 > point.yn)
				(b->x)--;
			else
				(b->x)++;
			b->pk = b->pk + 2 * b->delta_x - 2 * b->delta_y;
		}
		fdf_pixel_color(img, b->x, b->y, b->color);
	}
}

void	fdf_bre_determine_points(t_line *point, t_bre *b)
{
	if ((point->x0 <= point->xn && b->delta_x > b->delta_y)
		|| (point->y0 <= point->yn && b->delta_x <= b->delta_y))
	{
		b->x = point->x0;
		b->y = point->y0;
	}
	if ((point->x0 > point->xn && b->delta_x > b->delta_y)
		|| (point->y0 > point->yn && b->delta_x <= b->delta_y))
	{
		b->x = point->xn;
		b->y = point->yn;
	}
	if (b->delta_x > b->delta_y && point->x0 > point->xn)
		b->xn = point->x0;
	if (b->delta_x > b->delta_y && point->x0 <= point->xn)
		b->xn = point->xn;
	if (b->delta_x <= b->delta_y && point->y0 > point->yn)
		b->yn = point->y0;
	if (b->delta_x <= b->delta_y && point->y0 <= point->yn)
		b->yn = point->yn;
}

void	fdf_bresenham(t_line point, t_infos *img, int color)
{
	t_bre	b;

	b.color = color;
	b.delta_x = abs(point.xn - point.x0);
	b.delta_y = abs(point.yn - point.y0);
	if (b.delta_x > b.delta_y)
	{
		b.pk = 2 * b.delta_y - b.delta_x;
		fdf_bre_determine_points(&point, &b);
		fdf_bre_x(point, &b, img);
	}
	else
	{
		b.pk = 2 * b.delta_x - b.delta_y;
		fdf_bre_determine_points(&point, &b);
		fdf_bre_y(point, &b, img);
	}
}
