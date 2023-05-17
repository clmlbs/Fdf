/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 08:07:23 by cleblais          #+#    #+#             */
/*   Updated: 2022/11/24 16:08:27 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	len_c(char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c)
		i++;
	return (i);
}

size_t	gnl_strlcpy(char *dst, char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dstsize)
		return (len_c(src, '\0'));
	while (src[i] && (i < dstsize - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (len_c(src, '\0'));
}

size_t	gnl_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;

	i = 0;
	if (!dstsize)
		return (len_c(src, '\0'));
	dstlen = len_c(dst, '\0');
	if (dstlen > dstsize)
		return (len_c(src, '\0') + dstsize);
	while (src[i] && (dstlen + i) < dstsize - 1)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen = len_c(src, '\0'));
}

char	*gnl_strrchr(char *s, int c)
{
	int	i;

	i = len_c(s, '\0');
	while (i > 0)
	{
		if (s[i] == c)
			return (&s[i]);
		i--;
	}
	if (s[i] == c)
		return (&s[i]);
	return (NULL);
}

char	*gnl_strjoin(char *s1, char *s2)
{
	char	*saved;
	int		len;

	if (!s1)
	{
		s1 = (char *)malloc(sizeof(char));
		if (!s1)
			return (NULL);
		s1[0] = '\0';
	}
	if (!s1 || !s2)
	{
		free(s1);
		return (NULL);
	}
	len = len_c(s1, '\0') + len_c(s2, '\0') + 1;
	saved = (char *)malloc(sizeof(char) * len);
	if (!saved)
		return (NULL);
	gnl_strlcpy(saved, s1, len_c(s1, '\0') + 1);
	gnl_strlcat(saved, s2, len_c(saved, '\0') + len_c(s2, '\0') + 1);
	free(s1);
	return (saved);
}
