/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:42:48 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/21 10:35:28 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	init_data(int (*flags)[4], t_map *map, char **grid_line, char *path)
{
	(*flags)[TREAD_FLAG] = 10;
	(*flags)[EMPTY_FLAG] = 10;
	(*flags)[G_FLAG] = 1;
	(*flags)[FD_MAP] = open(path, O_RDONLY);
	map->no_texture = NULL;
	map->so_texture = NULL;
	map->we_texture = NULL;
	map->ea_texture = NULL;
	map->c_color = 0;
	map->f_color = 0;
	(*grid_line) = ft_strdup("");
	free(path);
	printf("CHECKING FILE SYNTAX...");
}

int	assign_data_t(char *line, char **ref)
{
	char	*r_line;

	if (*ref != NULL)
		return (0);
	while (*line != ' ' && *line != '\t' && *line != '\0')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	r_line = ft_substr(line, 0, ft_strchr(line, '\n') - line);
	*ref = r_line;
	return (1);
}

int	assign_data_c(char *line, int *ref)
{
	int	r;
	int	g;
	int	b;
	int	control;

	control = true;
	if (*ref != 0)
		return (0);
	while (*line != ' ' && *line != '\t' && *line != '\0')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	r = ft_atol(line, &control);
	g = ft_atol(ft_strchr(line, ',') + 1, &control);
	b = ft_atol(ft_strchr(ft_strchr(line, ',') + 1, ',') + 1, &control);
	if (control == false)
		return (2);
	*ref = (r << 16) | (g << 8) | b;
	return (1);
}

//CHECKS THE PREV LINES
int	check_flags(int *flag, int empty_flag)
{
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
int	is_empty(char *str)
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
