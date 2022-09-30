/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/09/30 14:53:00 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem-in.h"

/* thu */
t_room	*new_room(int type, int x, int y, char *room_name)
{
	t_room *new;

	new = (t_room *)malloc(sizeof(t_room));
	if (new)
		return ();
	new->x = x;
	new->y = y;
	new->type = type;
	return (new);
}

/* number_of_ants > 0 */
e_bool	is_positive(int nb)
{
	if (nb < 0)
		return FALSE;
	return TRUE;
}

int	type_of_line(char *str)
{
	if (!ft_strcmp(str, "##srart"))
		return (START);
	else if (!ft_strcmp(str, "##end"))
		return (END);
	else if (str[0] == '#' && str[1] != '#')
		return (COMMENT);
	else if (str[0] == '#')
		return (COMMAND);
	return (ROOM);
}

char	*room_name(str *line)
{
	int	len;
	char *room_name;

	len = 0;
	while(line[len] != ' ')
		len++;
	room_name = ft_strsub(line, 0, len); //check strsub
	if (!room_name) //malloc fail
		exit(0);
	return (room_name);
}

/* thu */
void	free_room(t_room *head)
{
	
}

/* thu */
void	create_room(t_room **prev, char *line, int type)
{
	t_room	*tmp;
	int		len;

	*tmp = new_room(type, 0, 0, room_name(line));
	len = ft_strlen(tmp->room_name);
	line += len;

	if (*prev == NULL)
		*prev = tmp;
	else
	{
		*prev->next = tmp;
		*prev = tmp;
	}
}

/* gnl + validation */
void	read_line(t_room *room)
{
	int	*line;
	int	gnl;
	int	type;
	int	next;

	gnl = 1;
	while (gnl)
	{
		gnl = get_next_line(0, &line);
		if (gnl == -1)
			exit(0); //if gnl fail
		type = type_of_line(line);
		if (type == START || type == END)
			next = type;
		if (type == ROOM && (next == START || next == END))
		{
			create_room(line, next);
			next = ROOM;
		}
		else if (type == ROOM)
			create_room(line, type);
		free(line);
	}
}