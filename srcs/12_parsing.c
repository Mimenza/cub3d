/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   12_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 12:31:06 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/05 20:25:35 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	check_flags(int *flag, int empty_flag)
{
	//error si empezamos nuevo grupo (flag == 1) y la anterio linea no esta vacia (empty_flag != 0)
	//error si no empezamos nuevo grupo (flag == 0) y la anterior linea esta vacia (empty_flag == 1)
	if ((empty_flag == 0 && *flag == 1) || (empty_flag == 1 && *flag == 0))
	{
		if (*flag == 1)
			*flag = 0;
		return (0); //si la anterior linea es NO es espacio y hemos empezado nuevo grupo
	}
	
	if (*flag == 1)
		*flag = 0;
	
	return (1);
}

int is_empty(char *str)
{
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
		{
			return 0; // No solo contiene espacios, tabulaciones o saltos de línea
		}
		str++;
	}
	return 1; // Contiene solo espacios, tabulaciones o saltos de línea
}
//0 ERROR 1 GRID 2 TEXTURE 3 COLOR
int	treat_data(t_map *map, char *line, int empty_flag, int *c_flag, int *g_flag, int *t_flag)
{
	int	error_flag;
	int	data_type;
	int	color_flag;

	data_type = 0; //default
	error_flag = 0;

	// printf(" treating the line: %s prev line empty?: %i\n c_f: %i\n t _f: %i\n", line, empty_flag, *c_flag, *t_flag);
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (map->no_texture || check_flags(t_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 2;
		map->no_texture = line;
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (map->so_texture || check_flags(t_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 2;
		map->so_texture = line;
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (map->we_texture || check_flags(t_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 2;
		map->we_texture = line;
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (map->ea_texture || check_flags(t_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 2;
		map->ea_texture = line;
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (map->f_color || check_flags(c_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 3;
		map->f_color = atoi(line);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (map->c_color || check_flags(c_flag, empty_flag) == 0)
			error_flag = 1;
		data_type = 3;
		map->c_color = atoi(line);
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

	tread_flag = 10;
	empty_flag = 10;
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
			{
				empty_flag = 1;
			}
			else
			{
				tmp = ft_strdup(grid_line);
				free(grid_line);
				tread_flag = treat_data(map, line, empty_flag, &c_flag, &g_flag, &t_flag);
				if (tread_flag == 0)
					break;
				else if ( tread_flag == 1)
				{
					// lo queremos para el grid
					grid_line = ft_strjoin(tmp, line);
				}
				else
				{
					//no lo queremos para el grid
					grid_line = ft_strdup(tmp);
				}
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
}