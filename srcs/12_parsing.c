/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:31:06 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/06 18:59:28 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

char	*parse_textures(char *line)
{
	char * r_line;
	
	while (*line != ' ' && *line != '\t' && *line != '\0')
		line++;

	while (*line == ' ' || *line == '\t')
		line++;

	r_line = ft_substr(line, 0, ft_strchr(line, '\n') - line);//REMOVES THE LAST JUMP LINE
	//free(line);
	return (r_line);
}

int		parse_colors(char *line)
{
	int	r;
	int	g;
	int	b;

	while (*line != ' ' && *line != '\t' && *line != '\0')
		line++;

	while (*line == ' ' || *line == '\t')
		line++;
			
	r = atoi(line);
	g = atoi(ft_strchr(line, ',') + 1); //Ref to the first ,
	b = atoi(ft_strchr(ft_strchr(line, ',') + 1, ',') + 1); // Ref to the second ,
	
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
int	treat_data(t_map *map, char *line, int empty_flag, int *g_flag)
{
	int	error_flag;
	int	flag;

	flag = 0;
	error_flag = 0;

	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (map->no_texture)
			error_flag = 1;
		map->no_texture = parse_textures(line);
		flag = 1;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (map->so_texture)
			error_flag = 1;
		map->so_texture = parse_textures(line);
		flag = 1;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (map->we_texture)
			error_flag = 1;
		map->we_texture = parse_textures(line);
		flag = 1;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (map->ea_texture)
			error_flag = 1;
		map->ea_texture = parse_textures(line);
		flag = 1;
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (map->f_color)
			error_flag = 1;
		map->f_color = parse_colors(line);
		flag = 1;
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (map->c_color)
			error_flag = 1;
		map->c_color = parse_colors(line);
		flag = 1;
	}

	if (flag == 1)
		return (2);
		
	if (error_flag == 1 || check_flags(g_flag, empty_flag) == 0 || map->c_color == 0 || map->f_color == 0 || map->ea_texture == NULL || map->no_texture == NULL || map->so_texture == NULL || map->we_texture == NULL)
		return ((void)printf("\033[1;31m [KO] \033[0m\nline-->%s\n", line), 0); //ERROR


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
