/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:11:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/16 23:36:44 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//Places a pixel
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->window.addrs + (y * game->window.line_len) + (x * (game->window.bpp / 8));
	*(unsigned int *) dst = color;
}

//Drawns a line
// void draw_line_to_direction(t_game *game, int x, int y, double length, double desv)
// {
// 	int		end_x;
// 	int 	end_y;
// 	int		steps;
// 	double	dx;
// 	double	dy;
// 	double	c_x;
// 	double	c_y;
// 	int		i;

// 	i = 0;

// 	// Calcula las coordenadas finales de la línea
// 	end_x = x + (length * cos(game->p->rad + desv));
// 	end_y = y + (length * sin(game->p->rad + desv));

// 	// Dibuja la línea desde (x, y) hasta (end_x, end_y)
// 	if (abs(end_x - x) > abs(end_y - y))
// 		steps = abs(end_x - x);
// 	else
// 		steps = abs(end_y - y);
	
// 	dx = (double)(end_x - x) / steps;
// 	dy = (double)(end_y - y) / steps;
// 	c_x = x;
// 	c_y = y;

// 	while (i <= steps)
// 	{
// 		my_mlx_pixel_put(game, (int)round(c_x), (int)round(c_y), 0xfa2e0a);
// 		c_x += dx;
// 		c_y += dy;
// 		i++;
// 	}
// }

void draw_line_to_direction(t_game *game, int x, int y, double length, double desv)
{
	int		end_x;
	int		end_y;
	int		steps;
	double	dx;
	double	dy;
	double	c_x;
	double	c_y;
	int		i;
	int		map_x;
	int		map_y;

	end_x = x + (length * cos(game->p->rad + desv));
	end_y = y + (length * sin(game->p->rad + desv));
	i = 0;

	if (abs(end_x - x) > abs(end_y - y))
		steps = abs(end_x - x);
	else
		steps = abs(end_y - y);

	dx = (double)(end_x - x) / steps;
	dy = (double)(end_y - y) / steps;
	c_x = x;
	c_y = y;

	while (i <= steps)
	{
		map_x = c_x / (game->window.size->w / game->map.size->w);
		map_y = c_y / (game->window.size->h / game->map.size->h);
		if (map_x >= 0 && map_x < game->map.size->w && map_y >= 0 && map_y < game->map.size->h &&
			game->map.grid[map_y][map_x] == '1')
		{
			// Si choca con una pared, detener el dibujo de la línea
			break;
		}

		my_mlx_pixel_put(game, (int)round(c_x), (int)round(c_y), 0xfa2e0a);
		c_x += dx;
		c_y += dy;
		i++;
	}
}

//Draws the fov fo the player
void	draw_fov(t_game *game, int px_rela, int py_rela, double l)
{
	double start;
	double	end;

	start = -45;
	end = 45;

	while (start <= end)
	{
		draw_line_to_direction(game, px_rela, py_rela, l, -(start * M_PI / 180.0));
		start += 0.1; //less number equals to more lines
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
	double	l;			//len of the line

	l = 10000000;
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
	draw_fov(game, px_rela, py_rela, l);
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
