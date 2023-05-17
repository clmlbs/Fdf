/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 08:49:23 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/19 15:06:54 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

size_t	len_c(char *s, char c);
size_t	gnl_strlcpy(char *dst, char *src, size_t dstsize);
size_t	gnl_strlcat(char *dst, char *src, size_t dstsize);
char	*gnl_strrchr(char *s, int c);
char	*gnl_strjoin(char *s1, char *s2);
char	*gnl_save_updated(char *old);
char	*gnl_create_line(char *saved);
char	*gnl_fill_save(int fd, char *saved, int nb_char);
char	*get_next_line(int fd);

#endif
