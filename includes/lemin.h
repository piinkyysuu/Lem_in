/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thule <thule@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 18:06:12 by thule             #+#    #+#             */
/*   Updated: 2022/11/01 11:52:31 by thule            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define FD 0
# include "libft.h"
# include "get_next_line.h"
/* remove later */
# include <stdio.h>

# define NORMAL "\x1B[0m"
# define BOLD "\033[1m"
# define RED "\x1B[31m"
# define GREEN "\x1B[32m"
# define YELLOW "\x1B[33m"
# define BLUE "\x1B[34m"
# define MAGENTA "\x1B[35m"
# define GREY "\x1B[38;5;238m"
# define PINK "\x1B[38;5;212m"
# define CYAN "\x1B[36m"
# define WHITE "\x1B[37m"

# define RATIO 1
# define PATH_BUFF_SIZE 100

# define NORMAL_WEIGHT 2
# define INVERSE 0
# define USED_INVERSE -5
# define SKIP -10

typedef enum e_bool
{
	FALSE,
	TRUE,
}	t_bool;

enum
{
	COMMENT,
	ROOM,
	START,
	END,
	COMMAND,
	LINK,
	EMPTY,
};

typedef enum e_direction
{
	OUT,
	IN,
}			t_direction;

/* room */
typedef struct s_room
{
	char			*room_name;
	int				index;
	t_bool			splitted;
	int				level;
	int				total_links;
	int				malloc_link;
	struct s_link	**link;
	struct s_room	*hash_table_next;
	struct s_room	*list_next;
}					t_room;

typedef struct s_que
{
	t_room			*room;
	int				direction;
	int				weight;
	struct s_que	*next;
}					t_que;

typedef struct s_path {
	t_room			**path;
	int				len;
	struct s_path	*next;
}	t_path;

/* link-room structure */
/*
 * one_two -> the weight from room 1 to room 2
 * two_one -> the weight from room 2 to room 1
 */
typedef struct s_link
{
	t_room			*room1;
	t_room			*room2;
	int				one_two;
	int				two_one;
	struct s_link	*next;
}					t_link;

typedef struct	s_path_link
{
	t_link	*link;
	int		start;
	struct s_path_link	*next;
}				t_path_link;

typedef struct	s_path_set
{
	t_path_link *head;
	// t_path_link *tail;
	int			len;
	int			level;
}				t_path_set;

typedef struct	s_flow {
	t_link	**link;
	int		number_of_flow;
}				t_flow;



/* adjacency matrix */
typedef struct s_info
{
	int		total_ants;
	int		total_rooms;
	int		total_links;
	t_room	*start_room;
	t_room	*end_room;
	char	*line;
	t_room	*room_head;
	t_room	**hash_table;
	t_link	*link_head;
}			t_info;

typedef struct s_table
{
	t_bool		visited[2];
	t_room		*prev[2]; //OUT:0      IN:1
	int			distance[2];
}	t_table;

/* bfs */
typedef struct s_bfs
{
	t_que		*head;
	t_que		*tail;
	// t_visited	*visited_test;
	t_table		*table;
	
	// t_bool	*visited;
	// t_room	**prev;
	// int		*distance;
}	t_bfs;

/* bfs.c */
t_bool			solution(t_info *info);


/**/
/* lem-in.c */
t_bool			init_info(t_info *info);
t_bool			check_digit_and_space(char *line);
t_bool			check_xy(char *line);
t_bool			lem_in(void);

/* hash_table.c */
unsigned int	hash(char *str, int size);
t_bool			create_hash_table(t_info *info);
t_room			*hash_table_lookup(t_room **hash_table, char *str, int size);
t_bool			hash_table_appending(t_info *info, t_room *list);
t_bool			init_hash_table(t_info *info);

/* utils.c */
void			error(char *error);
void			free_rooms(t_room **head);
void			free_links(t_link **link);

/* print.c */
void			print_hash_table(t_info *info);
void			print_single_room(t_room *room);
void			print_room(t_room *room);
void			print_info(t_info *info);
void			print_links(t_info *info);
void			print_single_link(t_link *link);
void			print_paths(t_path	*path);
void			print_single_path(t_path *path);

/* validation/read_line.c */
int				type_of_line(char *str);
t_bool			get_ants(t_info *info, int type, int *stage);
t_bool			path_to_each_stage(t_info *info, int type, int *stage);
t_bool			read_line(t_info *info);

/* validation/create_room.c */
t_bool			create_new_room(t_room **room, t_info *info);
char			*get_room_name(char *line);
t_bool			get_rooms(t_info *info, int type);

/* validation/create_link.c */
t_bool			get_room_in_link(t_link *new, t_room **hash_table,
					char *line, int size);
t_bool			create_new_link(t_info *info);
t_bool			get_links(t_info *info);

/* validation/onnect_rooms.c */
void			create_link_array(t_info *info);
t_bool			connect_rooms(t_info *info);

#endif
