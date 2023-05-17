/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 07:38:45 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/19 15:09:23 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_save_updated(char *old)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (old[i] && old[i] != '\n')
		i++;
	if (!old[i])
	{
		free(old);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (len_c(old, '\0') - i + 1));
	if (!new)
		return (NULL);
	i++;
	while (old[i])
		new[j++] = old[i++];
	new[j] = '\0';
	free(old);
	return (new);
}

char	*gnl_create_line(char *saved)
{
	int		i;
	char	*line;

	i = 0;
	if (!saved[i])
		return (NULL);
	line = (char *)malloc(sizeof(char) * len_c(saved, '\0') + 2);
	if (!line)
		return (NULL);
	while (saved[i] && saved[i] != '\n')
	{
		line[i] = saved[i];
		i++;
	}
	if (saved[i])
		line[i] = '\n';
	else
		line[i] = '\0';
	line[i + 1] = '\0';
	return (line);
}

char	*gnl_fill_save(int fd, char *saved, int nb_char)
{
	char	buf[BUFFER_SIZE + 1];

	buf[0] = '\0';
	while (!gnl_strrchr(buf, '\n') && nb_char)
	{
		nb_char = read(fd, buf, BUFFER_SIZE);
		if (nb_char == -1)
		{
			if (saved)
				free(saved);
			return (NULL);
		}
		buf[nb_char] = '\0';
		saved = gnl_strjoin(saved, buf);
		if (!saved)
			return (NULL);
	}
	return (saved);
}

char	*get_next_line(int fd)
{
	int			nb_char;
	char		*line;
	static char	*saved = NULL;

	if (fd < 0)
	{
		if (saved)
		{
			free(saved);
			saved = NULL;
		}
	}
	nb_char = 1;
	line = NULL;
	if (BUFFER_SIZE <= 0 || fd < 0)
		return (NULL);
	saved = gnl_fill_save(fd, saved, nb_char);
	if (!saved)
		return (NULL);
	line = gnl_create_line(saved);
	saved = gnl_save_updated(saved);
	return (line);
}
