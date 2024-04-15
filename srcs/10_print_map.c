/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:11:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/15 16:38:57 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//Main function which prints the map into the window.
// void	ft_print_map(t_game *game)
// {
// 	int		x;
// 	int		y;
// 	char	**grid;
// 	int		enemy;

// 	enemy = 0;
// 	grid = game->map.grid;
// 	y = 0;
// 	while (grid[y])
// 	{
// 		x = 0;
// 		while (grid[y][x])
// 		{
// 			ft_put_img(game, x, y, enemy);
// 			x++;
// 		}
// 		y++;
// 	}
// }

//This function prints the grid on the console.
void	ft_print_grid(char **grid)
{
	int		x;
	int		y;

	y = 0;
	printf("\n");
	while (grid[y])
	{
		x = 0;
		while(grid[y][x] != '\0')
		{
			if (grid[y][x] == ' ')
				printf("x");
			else
				printf("%c", grid[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}
