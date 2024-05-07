/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:41:11 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/07 12:41:54 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//Calculates the size of the map
void	calculate_size(t_map *map)
{
	int			x;
	int			y;
	char		**grid;

	grid = map->grid;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
			x++;
		y++;
	}
	map->size = malloc(sizeof(t_size));
	map->size->h = y;
	map->size->w = x;
}

// Main function which creates the map struct
t_map	ft_create_map(char *strmap)
{
	t_map	map;

	map.created = 0;
	if (ft_read_file(&map, strmap) == 0)
		return (map);
	calculate_size(&map);
	map.created = 1;

	return (map);
}
