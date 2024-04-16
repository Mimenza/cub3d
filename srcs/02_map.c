/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:41:11 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/16 11:41:33 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

// Function to create and validate the grid
static char	**ft_create_and_validate_grid(char *strmap)
{
	char	**grid;

	if (ft_create_grid(strmap, &grid) == 0)
		return (grid);

	if (ft_map_coll(grid) == 0)
		return (grid);

	if (ft_reachable(grid, strmap) == 0)
		return (grid);

	fill_w_sp(&grid);
	ft_print_grid(grid);
	draw_map(grid);
	return (grid);
}

// Main function which creates the map struct
t_map	ft_create_map(char *strmap)
{
	t_map	map;
	char	**grid;

	grid = ft_create_and_validate_grid(strmap);
	if (grid == NULL)
		return (map);
	return (map);
}