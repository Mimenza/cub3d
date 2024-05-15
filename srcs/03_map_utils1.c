/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_map_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:33:02 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/14 11:42:04 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//Checks if the above position is expandable, and expand to it.
static int	ft_check_position(int x, int y, char **grid, int *w_flag)
{
	if (!grid[y][x] || grid[y][x] == ' ')
		*w_flag = 1;
	if (grid[y][x] && (grid[y][x] == '0'))
	{
		grid[y][x] = 'P';
		return (1);
	}
	return (0);
}

//Aux function which checks if the map is doable
static int	ft_expandable(char **grid, int *w_flag)
{
	int			x;
	int			y;
	t_coords	coords;

	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'P')
			{
				coords.a = ft_check_position(x - 1, y, grid, w_flag);
				coords.b = ft_check_position(x + 1, y, grid, w_flag);
				coords.r = ft_check_position(x, y - 1, grid, w_flag);
				coords.l = ft_check_position(x, y + 1, grid, w_flag);
				if (coords.a == 1 || coords.b == 1 \
				|| coords.r == 1 || coords.l == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}

//Main function which checks if the map is doable
int	ft_reachable(char **grid)
{
	int			expandable;
	char		**p_grid;
	int			w_flag;

	expandable = 1;
	w_flag = 0;
	printf("CHECKING IF THE MAP IS DO-ABLE...");
	p_grid = ft_create_doubleptr(grid);
	ft_copy_doubleptr(grid, p_grid);
	ft_replace_p(&p_grid);
	while (expandable == 1 && w_flag == 0)
		expandable = ft_expandable(p_grid, &w_flag);
	if (w_flag == 0)
	{
		ft_free_doubleptr(p_grid);
		printf("\033[0;32m [OK] \033[0m\n\n");
		return (1);
	}
	ft_free_doubleptr(p_grid);
	return (0);
}

//Counts the entity number
int	ft_count_item(char c, int *player)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W' && \
	c != '0' && c != '1' && c != ' ' && c != '	')
	{
		ft_print_error(7);
		return (0);
	}
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		*player += 1;
	return (1);
}

//Check the  entity number
int	ft_check_item(int *player)
{
	if (*player != 1)
		ft_print_error(8);
	if (*player == 1)
		return (1);
	return (0);
}
