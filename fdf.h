/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:42:14 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 16:22:46 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "get_next_line/get_next_line.h"
# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include <math.h>

# define MARGE 150
# define KEY_ESC 53

# define WHITE 0x00FFFFFF
# define RED 0x00FF0000
# define L_GREEN 0x0090EE90
# define D_GREEN 0x00006400
# define PINK 0x00F9429E
# define FUSHIA 0x00D473D4
# define CYAN 0x0000FFFF

typedef struct s_bre
{
	int	delta_x;
	int	delta_y;
	int	pk;
	int	x;
	int	y;
	int	xn;
	int	yn;
	int	color;
}	t_bre;

typedef struct s_fdf_lst
{
	int					x;
	int					y;
	int					z;
	int					x_in_tab;
	int					y_in_tab;
	struct s_fdf_lst	*next;
}	t_fdf_lst;

typedef struct s_infos
{
	void	*ptr;
	char	*str;
	int		bpp;
	int		line_length;
	int		endian;
}	t_infos;

typedef struct s_var
{
	int			img_size_width;
	int			img_size_height;
	double		nb_tuils_in_height;
	double		nb_tuils_in_width;
	int			nb_cols;
	int			nb_lines;
	int			fd;
	int			**map;
	int			pix_per_side;
	int			x_of_00;
	int			y_of_00;
	int			bigger_z;
	int			x_of_bigger_z;
	int			y_of_bigger_z;
	t_fdf_lst	*lst;
	t_infos		img;
}	t_var;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	xn;
	int	yn;
}	t_line;

int			main(int ac, char **av);
void		fdf_add_z(t_var *v);
void		fdf_bresenham(t_line point, t_infos *img, int color);
void		fdf_bre_x(t_line point, t_bre *b, t_infos *img);
void		fdf_bre_y(t_line point, t_bre *b, t_infos *img);
void		fdf_bre_determine_points(t_line *point, t_bre *b);
int			checks(int ac, char **av);
int			create_empty_map(t_var *v);
int			deal_key(int key, void *param);
void		fdf_determine_color(t_var *v, int z0, int zn, t_line point);
void		fdf_draw_list(t_var *v);
void		draw_to_right(t_var *v, t_fdf_lst *pointed);
void		draw_to_up(t_var *v, t_fdf_lst *pointed);
void		fdf_bigger_z(t_var *v);
int			fdf_close_window(void *param);
void		fdf_divider_width(t_var *v, double *divider);
void		fdf_divider_height(t_var *v, double *divider);
void		fdf_determine_00(t_var *v);
void		fdf_fill_map(t_var *v, char **av, char **line);
void		fdf_how_many_pixels(t_var *v);
int			fdf_map(int ac, char **av, t_var *va_list);
void		fdf_modify_with_max_neg(t_var *v, int max_neg);
void		fdf_pixel_color(t_infos *img, int x, int y, int color);
void		fdf_pix_per_side(t_var *v, double space, double nb_tuils);
void		fdf_suppr_neg(t_var *v);
void		fdf_tuils(t_var *v);
void		fdf_verify_y(t_var *v);
void		ft_free_strs(char **strs);
void		ft_free_ints(int **ints, int x);
int			give_nb_col(t_var *v, char **av, char **line);
int			give_nb_lines(t_var *v, char **line);
char		**give_y_str(t_var *v, char **line);
void		parsing_map(t_var *v, char **av);
t_fdf_lst	*fdf_lstnew(int x, int y);
void		fdf_lstadd_back(t_fdf_lst **lst, t_fdf_lst *new);
t_fdf_lst	*fdf_lstlast(t_fdf_lst *lst);
void		fdf_lst_free(t_fdf_lst **lst);
t_fdf_lst	*fdf_which_link(t_fdf_lst *lst, int x, int y);
int			fdf_list(t_var *v);
int			fdf_create_list(t_var *v);
void		fdf_modify_coor_in_isometric(t_var *v);

#endif