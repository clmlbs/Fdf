/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_maps3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 13:12:05 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 14:47:41 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**give_y_str(t_var *v, char **line)
{
	int		len;
	char	**y;

	*line = get_next_line(v->fd);
	if (!(*line))
		return (NULL);
	len = ft_strlen(*line);
	if ((*line)[len - 2] == ' ' && (*line)[len - 1] == '\n')
		(*line)[len - 2] = '\0';
	y = ft_split(*line, ' ');
	if (!y)
		return (NULL);
	else
	{
		return (y);
	}
}

int	give_nb_col(t_var *v, char **av, char **line)
{
	char	**y;

	v->fd = open(av[1], O_RDONLY);
	y = give_y_str(v, line);
	if (!y)
		return (0);
	v->nb_cols = 0;
	while (y[v->nb_cols])
		v->nb_cols++;
	ft_free_strs(y);
	return (1);
}

int	give_nb_lines(t_var *v, char **line)
{
	char	*buf;

	v->nb_lines = 1;
	while (*line)
	{
		free(*line);
		buf = get_next_line(v->fd);
		if (!buf)
			return (1);
		*line = ft_strdup(buf);
		free(buf);
		v->nb_lines++;
	}
	return (1);
}

int	create_empty_map(t_var *v)
{
	int	i;

	i = 0;
	v->map = (int **)malloc(sizeof(int *) * v->nb_cols);
	if (!(v->map))
		return (0);
	while (i < v->nb_cols)
	{
		v->map[i] = (int *)malloc(sizeof(int) * v->nb_lines);
		if (!(v->map[i]))
		{
			while (i - 1 >= 0)
			{
				free(v->map[i - 1]);
				i--;
			}
			free(v->map);
			return (0);
		}
		i++;
	}
	return (1);
}

void	fdf_fill_map(t_var *v, char **av, char **line)
{
	char	**y;
	int		i;
	int		j;

	i = 0;
	j = 0;
	*line = NULL;
	close(v->fd);
	v->fd = open(av[1], O_RDONLY);
	while (j < v->nb_lines)
	{
		y = give_y_str(v, line);
		if (*line)
			free(*line);
		if (!y)
			return ;
		while (i < v->nb_cols)
		{
			v->map[i][j] = ft_atoi(y[i]);
			i++;
		}
		ft_free_strs(y);
		i = 0;
		j++;
	}
}
