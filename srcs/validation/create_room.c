/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:01:48 by thle              #+#    #+#             */
/*   Updated: 2022/11/10 17:43:03 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	init_room(t_room *room, char *room_name)
{
	room->room_name = room_name;
	room->is_occupied = FALSE;
	room->index = 0;
	room->total_links = 0;
	room->malloc_link = 0;
	room->path_nb = 0;
	room->link = NULL;
	room->hash_table_next = NULL;
	room->list_next = NULL;
}

t_bool	create_new_room(t_room **room, t_info *info)
{
	t_room	*new;
	char	*room_name;

	room_name = get_room_name(info->line);
	if (room_name == NULL)
		return (FALSE);
	if ((room_name && room_name[0] == 'L')
		|| check_xy(info->line + ft_strlen(room_name)) == FALSE)
		return (free(room_name), FALSE);
	new = (t_room *)malloc(sizeof(t_room));
	if (new == NULL)
		return (FALSE);
	init_room(new, room_name);
	if (*room == NULL)
		info->room_head = new;
	else
		(*room)->list_next = new;
	*room = new;
	(*room)->index = (info->total_rooms)++;
	return (TRUE);
}

char	*get_room_name(char *line)
{
	char	*room_name;
	int		len;

	len = 0;
	while (line[len] != ' ')
		len++;
	room_name = ft_strsub(line, 0, len);
	if (room_name == NULL)
		return (NULL);
	return (room_name);
}

t_bool	get_rooms(t_info *info, int type)
{
	static t_room	*room;
	static int		command;

	if (type == ROOM && (create_new_room(&room, info) == FALSE))
		return (FALSE);
	if ((command == START || command == END) && type != ROOM)
		return (FALSE);
	if (command == START)
		info->start_room = room;
	if (command == END)
		info->end_room = room;
	command = type;
	return (TRUE);
}
