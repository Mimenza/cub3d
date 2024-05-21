/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   04_map_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 15:32:43 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/14 11:19:28 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//Check the map player
int	ft_check_p(char **grid)
{
	int		x;
	int		y;
	int		player;

	printf("CHECKING ONLY 1 PLAYER...");
	y = 0;
	player = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (0 == ft_count_item(grid[y][x], &player))
				return (0);
			x++;
		}
		y++;
	}
	if (ft_check_item(&player) == 0)
		return (0);
	printf("\033[0;32m [OK] \033[0m\n\n");
	return (1);
}

//Replace the horientation with P
void	ft_replace_p(char ***p_grid)
{
	int			x;
	int			y;
	char		**grid;

	grid = (*p_grid);
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (grid[y][x] == 'N' || grid[y][x] == 'S' || \
			grid[y][x] == 'E' || grid[y][x] == 'W')
				grid[y][x] = 'P';
			x++;
		}
		y++;
	}
}

//Returns the size of the longest line
static size_t	max_line(char **grid)
{
	size_t	max;
	int		i;

	i = 0;
	max = 0;
	while (grid[i])
	{
		if (max < ft_strlen(grid[i]))
			max = ft_strlen(grid[i]);
		i++;
	}
	return (max);
}

//Fills the blank spaces till is rectangular
void	fill_w_sp(char	***grid)
{
	size_t	len;
	size_t	max;
	int		x;
	size_t	y;
	char	*tmp;

	max = max_line(*grid) - 1;
	x = -1;
	while ((*grid)[++x])
	{
		y = -1;
		tmp = (*grid)[x];
		len = ft_strlen((*grid)[x]);
		(*grid)[x] = (char *)malloc(sizeof(char *) * (max + 1));
		(*grid)[x][max + 1] = '\0';
		while (++y <= max)
		{
			if (y < len)
				(*grid)[x][y] = tmp[y];
			else
				(*grid)[x][y] = ' ';
		}
		free(tmp);
	}
}
