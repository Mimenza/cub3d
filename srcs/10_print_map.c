/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:11:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/16 17:00:43 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"


void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->window.addrs + (y * game->window.line_len) + (x * (game->window.bpp / 8));
	*(unsigned int *) dst = color;
}

void draw_line_to_direction(t_game *game, int x, int y, double rad, double length, int color)
{
	// Calcula las coordenadas finales de la línea
	int end_x = x + (length * cos(rad));
	int end_y = y + (length * sin(rad));

	// Dibuja la línea desde (x, y) hasta (end_x, end_y)
	while (x != end_x || y != end_y)
	{
		my_mlx_pixel_put(game, x, y, color);
		double dx = end_x - x;
		double dy = end_y - y;
		double norm = sqrt(dx * dx + dy * dy);
		x += (int)(dx / norm);
		y += (int)(dy / norm);
	}
}

//Main function which prints the map into the window.
void	ft_print_map(t_game *game)
{
	int		x;
	int		y;
	char	**grid;
	int		posx;		//saved x position
	int		posy;		//saved y position
	int		px_rela;	//player relative x position
	int		py_rela;	//player relative y position
	int		c_y;		//current y
	double	l;

	l = 40;
	c_y = 0;
	posx = 0;
	posy = 0;
	px_rela = ((game->p->pos.x * game->window.size->w) / (game->map.size->w));
	py_rela = ((game->p->pos.y * game->window.size->h) / (game->map.size->h));
	y = 0;
	while ( y < (game->window.size->h))
	{
		x = 0;
		while (x < (game->window.size->w))
		{
			if ((((x - px_rela) * (x - px_rela)) + ((y - py_rela) * (y - py_rela))) <= 40)
			{
				//If para printear circulito
				my_mlx_pixel_put(game, x, y, 0xfa2e0a);
			}
			else if ((x == (l * cos(game->p->rad) + px_rela)) && (y == (l * sin(game->p->rad) + py_rela)))
			{
				draw_line_to_direction(game, px_rela, py_rela, game->p->rad, l, 0xfa2e0a);
				l--;
			}
			else if ((posx != ((x * game->map.size->w) / (game->window.size->w))) || (c_y != posy))
			{
				//If para printear lineas grid
				my_mlx_pixel_put(game, x, y, 0x000000);
				posx = ((x * game->map.size->w) / (game->window.size->w));
				posy = ((y * game->map.size->h) / (game->window.size->h));
			}
			else
			{
				//Else para printear todo lo demas
				posx = ((x * game->map.size->w) / (game->window.size->w));
				posy = ((y * game->map.size->h) / (game->window.size->h));
				
				if (game->map.grid[posy][posx] == '0')
					my_mlx_pixel_put(game, x, y, 0xFFFFFF);
				else if (game->map.grid[posy][posx] == '1')
					my_mlx_pixel_put(game, x, y, 0x8a8787);
				else if (game->map.grid[posy][posx] == ' ')
					my_mlx_pixel_put(game, x, y, 0x000000);
				else
					my_mlx_pixel_put(game, x, y, 0xFFFFFF);
			}
			x++;
		}
		//Actualizamos que estamos en nueva fila
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
