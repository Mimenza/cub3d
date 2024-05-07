/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:31:06 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/07 13:43:10 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int assign_data_t(char *line, char **ref, char *(*parse_function)(char *))
{
	if (*ref != NULL)
		return (0); // Error: La referencia ya está asignada
	*ref = parse_function(line);
	return (1); // Datos asignados correctamente
}

int assign_data_c(char *line, int *ref, int (*parse_function)(char *))
{
	if (* ref != 0)
		return (0); // Error: La referencia ya está asignada
	* ref = parse_function(line);
	return (1); // Datos asignados correctamente
}

//2 non grid but saved, 0 error, 1 grid
int	treat_data(t_map *map, char *line, int empty_flag, int *g_flag)
{
	int	flag;

	flag = 10; //default
	if (ft_strncmp(line, "NO ", 3) == 0)
		flag = assign_data_t(line, &(map->no_texture), &parse_textures);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		flag = assign_data_t(line, &(map->so_texture), &parse_textures);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		flag = assign_data_t(line, &(map->we_texture), &parse_textures);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		flag = assign_data_t(line, &(map->ea_texture), &parse_textures);
	else if (ft_strncmp(line, "F ", 2) == 0)
		flag = assign_data_c(line, &(map->f_color), &parse_colors);
	else if (ft_strncmp(line, "C ", 2) == 0)
		flag = assign_data_c(line, &(map->c_color), &parse_colors);
	if (flag == 1)
		return (2);
	if (flag == 0)
		return (ft_print_error(5),0);
	if (check_flags(g_flag, empty_flag) == 0 || map->c_color == 0 || \
	map->f_color == 0 || map->ea_texture == NULL || \
	map->no_texture == NULL || map->so_texture == NULL || \
	map->we_texture == NULL)
		return ((void)printf("\033[1;31m [KO] \033\n"), 0); //ERROR IN THE GRID
	return (1); //GRID
}

int ft_read_file(t_map *map, char *strmap)
{
	char	*path;
	int		fdmap;
	char	*line;
	char	*tmp;
	char	*grid_line;
	int		empty_flag; // line is empty
	int		g_flag;		//grid flag;
	char	**grid;
	int		tread_flag;

	tread_flag = 10;	//init in random nbr
	empty_flag = 10;	//init in random nbr
	g_flag = 1;
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->c_color = 0;
	map->f_color = 0;
	
	printf("CHECKING FILE SYNTAX...");
	grid_line = ft_strdup("");
	path = ft_strjoin("./maps/", strmap);
	fdmap = open(path, O_RDONLY);
	free(path);
	if (fdmap == -1)
		return (ft_print_error(2), 1);
	while (1)
	{
		line = get_next_line(fdmap);
		if (line != NULL)
		{
			if (is_empty(line) == 1)
				empty_flag = 1;
			else
			{
				tmp = ft_strdup(grid_line);
				free(grid_line);
				tread_flag = treat_data(map, line, empty_flag, &g_flag);
				if (tread_flag == 0)
					break;
				else if ( tread_flag == 1)
					grid_line = ft_strjoin(tmp, line);// lo queremos para el grid
				else
					grid_line = ft_strdup(tmp); //no lo queremos para el grid
				free(line);
				free(tmp);
				empty_flag = 0;
			}
		}
		else
			break;
	}
	close(fdmap);

	if (tread_flag == 0)
		return(0);
	if (!map->c_color || !map->f_color || !map->ea_texture || !map->no_texture || !map->so_texture || !map->we_texture)
		return(ft_print_error(4), 0);
	
	ft_print_ok();
	grid = ft_split(grid_line, '\n');
	if (grid == NULL)
		return (ft_print_error(3), 0);

	map->grid = grid;
	if (ft_map_coll(grid) == 0)
		return (0);

	if (ft_reachable(grid, strmap) == 0)
		return (ft_print_error(6) ,0);

	fill_w_sp(&grid);
	
	return (1);
}
