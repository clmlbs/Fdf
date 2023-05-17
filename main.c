/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:45:37 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 16:22:10 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	fdf_list(t_var *v)
{
	if (!fdf_create_list(v))
		return (0);
	fdf_determine_00(v);
	fdf_modify_coor_in_isometric(v);
	fdf_add_z(v);
	fdf_verify_y(v);
	return (1);
}

int	main(int ac, char **av)
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_var	v;

	v.img_size_width = 1700;
	v.img_size_height = 900;
	if (!fdf_map(ac, av, &v))
		return (0);
	if (!fdf_list(&v))
		return (0);
	mlx_ptr = mlx_init();
	win_ptr = mlx_new_window(mlx_ptr, 1700, 900, "Fdf");
	v.img.ptr = mlx_new_image(mlx_ptr, v.img_size_width, v.img_size_height);
	v.img.str = mlx_get_data_addr(v.img.ptr, &v.img.bpp, &v.img.line_length, \
	&v.img.endian);
	fdf_draw_list(&v);
	mlx_put_image_to_window(mlx_ptr, win_ptr, v.img.ptr, 0, 0);
	fdf_lst_free(&(v.lst));
	mlx_key_hook(win_ptr, deal_key, (void *)0);
	mlx_hook(win_ptr, 17, 0, fdf_close_window, (void *)0);
	mlx_loop(mlx_ptr);
	return (0);
}
