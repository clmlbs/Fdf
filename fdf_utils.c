/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:59:53 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 14:47:59 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	ft_free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs[i]);
	free(strs);
}

void	ft_free_ints(int **ints, int x)
{
	int	i;

	i = 0;
	while (i < x)
	{
		free(ints[i]);
		i++;
	}
	free(ints);
}

int	checks(int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		ft_printf("error: bad number of arguments\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}
	close(fd);
	return (1);
}
