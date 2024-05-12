/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:31:06 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/12 18:41:48 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//2 non grid but saved, 0 error, 1 grid
int	treat_data(t_map *map, char *line, int empty_flag, int *g_flag)
{
	int	flag;

	flag = 10;
	if (ft_strncmp(line, "NO ", 3) == 0)
		flag = assign_data_t(line, &(map->no_texture));
	else if (ft_strncmp(line, "SO ", 3) == 0)
		flag = assign_data_t(line, &(map->so_texture));
	else if (ft_strncmp(line, "WE ", 3) == 0)
		flag = assign_data_t(line, &(map->we_texture));
	else if (ft_strncmp(line, "EA ", 3) == 0)
		flag = assign_data_t(line, &(map->ea_texture));
	else if (ft_strncmp(line, "F ", 2) == 0)
		flag = assign_data_c(line, &(map->f_color));
	else if (ft_strncmp(line, "C ", 2) == 0)
		flag = assign_data_c(line, &(map->c_color));
	if (flag == 1)
		return (2);
	if (flag == 0)
		return (ft_print_error(5), 0);
	if (check_flags(g_flag, empty_flag) == 0 || map->c_color == 0 || \
	map->f_color == 0 || map->ea_texture == NULL || \
	map->no_texture == NULL || map->so_texture == NULL || \
	map->we_texture == NULL)
		return ((void)printf("\033[1;31m [KO] \033\n"), 0);
	return (1);
}

int	ft_read_each_line(int (*flags)[4], t_map *map, char **grid_line)
{
	char	*line;
	char	*tmp;

	while (1)
	{
		line = get_next_line((*flags)[FD_MAP]);
		if (line != NULL)
		{
			if (is_empty(line) == 1)
				(*flags)[EMPTY_FLAG] = 1;
			else
			{
				tmp = ft_strdup(*grid_line);
				free(*grid_line);
				(*flags)[TREAD_FLAG] = treat_data(map, line, (*flags)[EMPTY_FLAG], &(*flags)[G_FLAG]);
				if ((*flags)[TREAD_FLAG] == 0)
					return (free(tmp), free(line), 0);
				else if ((*flags)[TREAD_FLAG] == 1)
					*grid_line = ft_strjoin(tmp, line);
				else
					*grid_line = ft_strdup(tmp);
				free(tmp);
				(*flags)[EMPTY_FLAG] = 0;
			}
			free(line);
		}
		else
			break ;
	}
	close((*flags)[FD_MAP]);
	return (1);
}

int	ft_read_file(t_map *map, char *strmap)
{
	char	*grid_line;
	int		flags[4];

	init_data(&flags, map, &grid_line, ft_strjoin("./maps/", strmap));
	if (flags[FD_MAP] == -1)
		return (ft_print_error(2), 0);
	ft_read_each_line(&flags, map, &grid_line);
	if (flags[TREAD_FLAG] == 0)
		return (0);
	if (!map->c_color || !map->f_color || !map->ea_texture || \
	!map->no_texture || !map->so_texture || !map->we_texture)
		return (ft_print_error(4), 0);
	ft_print_ok();
	map->grid = ft_split(grid_line, '\n');
	free(grid_line);
	if (map->grid == NULL)
		return (ft_print_error(3), 0);
	if (ft_check_p(map->grid) == 0)
		return (0);
	if (ft_reachable(map->grid) == 0)
		return (ft_print_error(6), 0);
	fill_w_sp(&map->grid);
	return (1);
}
