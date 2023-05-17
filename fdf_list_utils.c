/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cleblais <cleblais@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/12 12:07:00 by cleblais          #+#    #+#             */
/*   Updated: 2023/01/20 14:46:14 by cleblais         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf_lst	*fdf_lstnew(int x, int y)
{
	t_fdf_lst	*new_link;

	new_link = (t_fdf_lst *)malloc(sizeof(t_fdf_lst));
	if (!new_link)
		return (NULL);
	new_link->x = x;
	new_link->y = y;
	new_link->x_in_tab = x;
	new_link->y_in_tab = y;
	new_link->next = NULL;
	return (new_link);
}

void	fdf_lstadd_back(t_fdf_lst **lst, t_fdf_lst *new)
{
	t_fdf_lst	*ptr;

	if (!new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	ptr = fdf_lstlast(*lst);
	ptr->next = new;
}

t_fdf_lst	*fdf_lstlast(t_fdf_lst *lst)
{
	t_fdf_lst	*ptr;

	if (!lst)
		return (NULL);
	ptr = lst;
	while (ptr->next != NULL)
		ptr = ptr->next;
	return (ptr);
}

void	fdf_lst_free(t_fdf_lst **lst)
{
	t_fdf_lst	*buf;

	if (lst)
	{
		while (*lst)
		{
			buf = (*lst)->next;
			free(*lst);
			*lst = buf;
		}
	}
}

t_fdf_lst	*fdf_which_link(t_fdf_lst *lst, int x, int y)
{
	t_fdf_lst	*buf;

	buf = lst;
	while (buf != NULL)
	{
		if (buf->x_in_tab == x && buf->y_in_tab == y)
			return (buf);
		buf = buf->next;
	}
	return (NULL);
}
