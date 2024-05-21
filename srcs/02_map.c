/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 11:41:11 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/21 09:22:54 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//This function creates a double ptr.
char	**ft_create_doubleptr(char **grid)
{
	char	**ptr;
	int		size;

	size = 0;
	while (grid[size])
		size++;
	ptr = (char **)malloc((size + 1) * sizeof(char *));
	if (ptr == NULL)
		return (ptr);
	return (ptr);
}

//This function copies a double ptr.
void	ft_copy_doubleptr(char **grid, char **p_grid)
{
	int	i;
	int	size;

	size = 0;
	while (grid[size])
		size++;
	i = 0;
	while (i <= (size - 1))
	{
		p_grid[i] = ft_strdup(grid[i]);
		i++;
	}
	p_grid[i] = NULL;
}

//Calculates the size of the map
static void	calculate_size(t_map *map)
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
