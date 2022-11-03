/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem-in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thle <thle@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:07:47 by thule             #+#    #+#             */
/*   Updated: 2022/11/03 22:34:48 by itkimura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

t_bool	init_info(t_info *info)
{
	info->total_ants = 0;
	info->total_rooms = 0;
	info->total_links = 0;
	info->start_room = NULL;
	info->end_room = NULL;
	info->room_head = NULL;
	info->line = NULL;
	info->room_head = NULL;
	info->hash_table = NULL;
	info->link_head = NULL;
	return (TRUE);
}

t_bool	check_digit_and_space(char *line)
{
	int	i;
	int	space;

	i = 1;
	space = 0;
	if (line == NULL || line[0] != ' ')
		return (FALSE);
	while (line[i] != '\0')
	{
		if (line[i] == ' ')
			space++;
		if ((ft_isdigit(line[i]) == 0 && line[i] != ' '
				&& line[i] != '+') || space > 1)
			return (FALSE);
		if (line[i] == ' ' && (ft_isdigit(line[i + 1]) == 0
				|| line[i + 1] == '+'))
			return (FALSE);
		i++;
	}
	if (space == 0)
		return (FALSE);
	return (TRUE);
}

t_bool	check_xy(char *line)
{
	long	x;
	long	y;

	if (check_digit_and_space(line) == FALSE)
		return (FALSE);
	x = ft_atol(line);
	y = ft_atol(ft_strchr(line + 1, ' '));
	if ((x > INT_MAX || x < INT_MIN) || (y > INT_MAX || y < INT_MIN))
		return (FALSE);
	return (TRUE);
}

t_bool	lem_in(void)
{
	t_info	info;

	if (init_info(&info) == FALSE)
		return (error("\nError.\n"), FALSE);
	if (read_line(&info) == FALSE)
	{
		free_rooms(&(info.room_head));
		if (info.hash_table)
			free(info.hash_table);
		return (error("\nError.\n"), FALSE);
	}
	if (connect_rooms(&info) == FALSE)
	{
		free_rooms(&(info.room_head));
		free_links(&(info.link_head));
		if (info.hash_table)
			free(info.hash_table);
		return (error("\nError.\n"), FALSE);
	}
	/*Delete start here*/
	//print_info(&info);
	//print_hash_table(&info);
	solution(&info);
	// print_room(info.room_head);
	/*Delete end here*/
	free(info.hash_table);
	free_rooms(&(info.room_head));
	free_links(&(info.link_head));
	// return (printf("\n%sSuccess.\n%s", GREEN, WHITE), TRUE);
	return (TRUE);
}

int	main(void)
{
	if (lem_in() == FALSE)
		return (1);
	return (0);
}
