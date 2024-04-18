/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:11:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/18 11:20:05 by emimenza         ###   ########.fr       */
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

void draw_line_to_direction(t_game *game, int x, int y, double length, double desv)
{
	int end_x;         // End x-coordinate of the line
	int end_y;         // End y-coordinate of the line
	double steps;      // Number of steps to take along the line
	double dx;         // Change in x-coordinate per step
	double dy;         // Change in y-coordinate per step
	double c_x;        // Current x-coordinate during line traversal
	double c_y;        // Current y-coordinate during line traversal
	double dtw;        // Distance to wall (distance to the first wall encountered)

	dtw = -1;
	end_x = x + (length * cos(game->p->rad + desv));
	end_y = y + (length * sin(game->p->rad + desv));

	if (abs(end_x - x) > abs(end_y - y))
		steps = abs(end_x - x);
	else
		steps = abs(end_y - y);

	dx = (end_x - x) / steps;
	dy = (end_y - y) / steps;
	c_x = x;
	c_y = y;

	int i;
	for (i = 0; i <= steps; i++)
	{
		int map_x = (int)(c_x / ((game->window.size->w / RES )/ game->map.size->w));
		int map_y = (int)(c_y / ((game->window.size->h / RES ) / game->map.size->h));
		if (map_x >= 0 && map_x < game->map.size->w && map_y >= 0 && map_y < game->map.size->h &&
			game->map.grid[map_y][map_x] == '1')
		{
			// Once a wall is found, calculate distance to wall
			dtw = sqrt((c_x - x) * (c_x - x) + (c_y - y) * (c_y - y));
			break;
		}

		my_mlx_pixel_put(game, (int)round(c_x), (int)round(c_y), 0xfa2e0a);
		// Move along the line
		c_x += dx;
		c_y += dy;
	}

	// i = 0;
	// while (i <= dtw)
	// {
	// 	printf("0");
	// 	i +=5;
	// }
	// printf("\n");
}

//Draws the fov fo the player
void	draw_fov(t_game *game, int px_rela, int py_rela, double l)
{
	double start;
	double	end;

	start = ANGLE_S;	//Angle start to the left
	end = ANGLE_E;		//Angle end to the right

	while (start <= end)
	{
		draw_line_to_direction(game, px_rela, py_rela, l, (start * M_PI / 180.0));
		start += ITER; //less number equals to more lines
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

	l = INT32_MAX;
	c_y = 0;
	posx = 0;
	posy = 0;
	px_rela = ((game->p->pos.x * game->window.size->w / RES) / (game->map.size->w));
	py_rela = ((game->p->pos.y * game->window.size->h / RES) / (game->map.size->h));
	y = 0;
	while ( y < (game->window.size->h / RES))
	{
		x = 0;
		while (x < (game->window.size->w / RES))
		{
			if ((((x - px_rela) * (x - px_rela)) + ((y - py_rela) * (y - py_rela))) <= 40)
			{
				//If para printear circulito
				my_mlx_pixel_put(game, x, y, 0xfa2e0a);
			}
			else if ((posx != ((x * game->map.size->w) / (game->window.size->w / RES))) || (c_y != posy))
			{
				//If para printear lineas grid
				my_mlx_pixel_put(game, x, y, 0x000000);
				posx = ((x * game->map.size->w) / (game->window.size->w / RES));
				posy = ((y * game->map.size->h) / (game->window.size->h / RES));
			}
			else
			{
				//Else para printear todo lo demas
				posx = ((x * game->map.size->w) / (game->window.size->w / RES));
				posy = ((y * game->map.size->h) / (game->window.size->h / RES));
				
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
		c_y = ((y * game->map.size->h) / (game->window.size->h / RES));
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
