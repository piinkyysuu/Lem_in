/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_link.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:17:18 by thle              #+#    #+#             */
/*   Updated: 2022/10/06 16:49:37 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool get_room_in_link(t_link *new, t_room **hash_table, char *line, int size)
{
	char *tmp;
	char *room1;
	char *room2;
	int len;

	tmp = ft_strchr(line, '-');
	while (tmp)
	{
		len = tmp - line;
		room1 = ft_strsub(line, 0, len);
		room2 = line + len + 1;
		if (room1 == NULL)
			return (error("Malloc fails.\n"), FALSE);
		new->room1 = hash_table_lookup(hash_table, room1, size);
		new->room2 = hash_table_lookup(hash_table, room2, size);
		ft_strdel(&room1);
		if (new->room1 &&new->room2)
		{
			new->room1->quantity_of_links++;
			new->room2->quantity_of_links++;
			return (TRUE);
		}
		tmp = ft_strchr(tmp + 1, '-');
	}
	return (error("No room found.\n"), FALSE);
}

t_bool create_new_link(t_link **link, t_info *info)
{
	t_link *new;
	static t_link *tmp;
	int len;

	len = 0;
	new = (t_link *)malloc(sizeof(t_link));
	link = NULL;
	if (new == NULL)
		return (error("Malloc fails.\n"), FALSE);
	new->room1 = NULL;
	new->room2 = NULL;
	if (get_room_in_link(new, info->hash_table, info->line,
						 (int)(info->quantity_of_rooms * RATIO)) == FALSE)
		return (FALSE);
	if (info->link_head == NULL)
	{
		info->link_head = new;
		tmp = new;
	}
	else
	{
		tmp->next = new;
		tmp = new;
	}
	return (TRUE);
}

t_bool get_links(t_info *info)
{
	static t_link *link;

	if (create_new_link(&link, info) == FALSE)
		return (FALSE);
	return (TRUE);
}

