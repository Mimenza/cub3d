/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:31:06 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/05 21:31:03 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

char	*parse_textures(char *line)
{
	while (*line != ' ' && *line != '\t' && *line != '\0')
		line++;

	while (*line == ' ' || *line == '\t')
		line++;
	return (line);
}

int		parse_colors(char *line)
{
	char *parsed_line;
	int	r;
	int	g;
	int	b;

	parsed_line = parse_textures(line);
	r = atoi(parsed_line);
	g = atoi(parsed_line + 4);
	b = atoi(parsed_line + 8);

	//printf("%i %i %i\n", r, g, b);	
	//printf("%i \n", (r << 16) | (g << 8) | b);
	//printf("#%06X \n", (r << 16) | (g << 8) | b);
	return((r << 16) | (g << 8) | b);
}



//CHECKS THE LINES
int	check_flags(int *flag, int empty_flag)
{
	//error si empezamos nuevo grupo (flag == 1) y la anterio linea no esta vacia (empty_flag != 0)
	//error si no empezamos nuevo grupo (flag == 0) y la anterior linea esta vacia (empty_flag == 1)
	if ((empty_flag == 0 && *flag == 1) || (empty_flag == 1 && *flag == 0))
	{
		if (*flag == 1)
			*flag = 0;
		return (0);
	}
	if (*flag == 1)
		*flag = 0;
	
	return (1);
}

//CHECKS IF THE LINE IS EMPTY
int is_empty(char *str)
{
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
		{
			return (0);
		}
		str++;
	}
	return (1);
}

//0 ERROR 1 GRID 2 TEXTURE 3 COLOR
int	treat_data(t_map *map, char *line, int empty_flag, int *c_flag, int *g_flag, int *t_flag)
{
	int	error_flag;
	int	data_type;
	int	color_flag;

	data_type = 0; //default
	error_flag = 0;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (map->no_texture || check_flags(t_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 2;
		map->no_texture = parse_textures(line);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (map->so_texture || check_flags(t_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 2;
		map->so_texture = parse_textures(line);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (map->we_texture || check_flags(t_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 2;
		map->we_texture = parse_textures(line);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (map->ea_texture || check_flags(t_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 2;
		map->ea_texture = parse_textures(line);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (map->f_color || check_flags(c_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 3;
		map->f_color = parse_colors(line);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (map->c_color || check_flags(c_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 3;
		map->c_color = parse_colors(line);
	}
	
	if (error_flag == 1)
		return ((void)printf("Error in the map syntax, line-->%s\n", line), 0);//ERROR

	if (data_type == 2)
		return (2); // TEXTURE

	if (data_type == 3)
		return (3); //COLOR
	
	if (check_flags(g_flag, empty_flag) == 0 || *c_flag == 1 || *t_flag == 1)
		return ((void)printf("Error in the map syntax, line-->%s\n", line), 0);//ERROR

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
	int		c_flag; 	//color flag;
	int		g_flag;		//grid flag;
	int		t_flag;		//texture flag;
	char	**grid;
	int		tread_flag;

	tread_flag = 10;	//init in random nbr
	empty_flag = 10;	//init in random nbr
	c_flag = 1;
	g_flag = 1;
	t_flag = 1;

	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->c_color = 0;
	map->f_color = 0;

	grid_line = ft_strdup("");
	path = ft_strjoin("./maps/", strmap);
	fdmap = open(path, O_RDONLY);
	free(path);
	if (fdmap == -1)
		return (1);
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
				tread_flag = treat_data(map, line, empty_flag, &c_flag, &g_flag, &t_flag);
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
	grid = ft_split(grid_line, '\n');
	map->grid = grid;
	if (ft_map_coll(grid) == 0)
		return (0);
	if (ft_reachable(grid, strmap) == 0)
		return (0);
	fill_w_sp(&grid);

	printf("NO %s\n", map->no_texture);
	printf("SO %s\n", map->so_texture);
	printf("WE %s\n", map->we_texture);
	printf("EA %s\n", map->ea_texture);
	return (1);
}
