/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:41:11 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/05 18:47:01 by emimenza         ###   ########.fr       */
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

// Function to create and validate the grid
// static char	**ft_create_and_validate_grid(t_map *map, char *strmap)
// {
// 	char	**grid;

// 	if (ft_create_grid(map, strmap, &grid) == 0)
// 	{
// 		grid = NULL;
// 		return (grid);
// 	}
// 	if (ft_map_coll(grid) == 0)
// 	{
// 		grid = NULL;
// 		return (grid);
// 	}
// 	if (ft_reachable(grid, strmap) == 0)
// 	{
// 		grid = NULL;
// 		return (grid);
// 	}
// 	fill_w_sp(&grid);
// 	return (grid);
// }

// Main function which creates the map struct
t_map	ft_create_map(char *strmap)
{
	t_map	map;
	char	**grid;

	map.created = 0;
	// grid = ft_create_and_validate_grid(&map, strmap);
	ft_read_file(&map, strmap);
	if (grid == NULL)
		return (map);
	map.grid = grid;
	calculate_size(&map);
	map.created = 1;
	return (map);
}
