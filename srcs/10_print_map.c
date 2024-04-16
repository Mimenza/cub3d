/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:11:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/16 13:15:13 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->window.addrs + (y * game->window.line_len) + (x * (game->window.bpp / 8));
	*(unsigned int *) dst = color;
}

//Main function which prints the map into the window.
void	ft_print_map(t_game *game)
{
	int		x;
	int		y;
	char	**grid;
	int		posx;
	int		posy;
	int		c_y;

	c_y = 0;
	posx = 0;
	posy = 0;
	// grid = game->map.grid;
	y = 0;
	while ( y < (game->window.size->h))
	{
		x = 0;
		while (x < (game->window.size->w))
		{
			//printf("x: %i y: %i\n", x, y);
			if ((posx != ((x * game->map.size->w) / (game->window.size->w))) || (c_y != posy))
			{
				my_mlx_pixel_put(game, x, y, 0x000000);
				posx = ((x * game->map.size->w) / (game->window.size->w));
				posy = ((y * game->map.size->h) / (game->window.size->h));
			}
			else
			{
				posx = ((x * game->map.size->w) / (game->window.size->w));
				posy = ((y * game->map.size->h) / (game->window.size->h));
				if (game->map.grid[posy][posx] == '0')
					my_mlx_pixel_put(game, x, y, 0xFFFFFF);
				else if (game->map.grid[posy][posx] == '1')
					my_mlx_pixel_put(game, x, y, 0x8a8787);
				else if (game->map.grid[posy][posx] == ' ')
					my_mlx_pixel_put(game, x, y, 0x000000);
				else
					my_mlx_pixel_put(game, x, y, 0xe32424);
			}
			x++;
		}
		c_y = ((y * game->map.size->h) / (game->window.size->h));
		y++;
	}
	mlx_put_image_to_window(game->window.mlx, game->window.win, game->window.img, 0, 0);
}

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
