/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:11:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/05 12:40:45 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//Places a pixel
void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;
	if ((x < 0 || x > game->window.size->w) || (y < 0 || y > game->window.size->h))
		return;
	dst = game->window.addrs + (y * game->window.line_len) + (x * (game->window.bpp / 8));
	*(unsigned int *) dst = color;
}

double	cal_distance(t_player *player, double c_x, double c_y, double x, double y)
{
	double a;
	double b;
	double distance;

	if (player->rad != 0)
	{
		a = (tan(player->rad + (M_PI / 2)));
		b = (y - (x * a));
	}
	else
		return (fabs(x - c_x));
	distance = fabs((-(a * c_x) + c_y - b) / sqrt((a * a) + (1)));
	return (distance);
}

// void draw_v_line(t_game *game, double desv, double size, int c_i, int color)
// {
// 	int column_w;
// 	int column_h;
// 	int y;
// 	int wall_h;

// 	wall_h = size;
// 	column_w = 1;
// 	column_h = game->window.size->h;

// 	// Calcula el inicio y el final de la pared en la columna
// 	int draw_start = (column_h - wall_h) / 2;
// 	int draw_end = draw_start + wall_h;

// 	// Desplaza la posición horizontalmente para la columna actual
// 	int start_x = c_i * column_w;
// 	int x = start_x;
// 	while (x < start_x + column_w)
// 	{
// 		y = 0;
// 		while (y < column_h)
// 		{
// 			if (y < game->window.size->h / 2)
// 				my_mlx_pixel_put(game, x, y, 0x8d9ed6); // Color superior
// 			else if (y > game->window.size->h / 2)
// 				my_mlx_pixel_put(game, x, y, 0x96867a); // Color inferior

// 			if ( y > draw_start && y < draw_end)
// 				my_mlx_pixel_put(game, x, y, color); // Color de la pared
// 			y++;
// 		}
// 		x++;
// 	}
// }

void draw_v_line(t_game *game, double desv, double size, int c_i, int *texture, double column)
{
	int column_w;
	int column_h;
	int y;
	int wall_h;
	int textel_x;
	int textel_y;

	wall_h = size;
	column_w = 1;
	column_h = game->window.size->h;
	textel_x = round(column * 64);
	// Calcula el inicio y el final de la pared en la columna
	int draw_start = (column_h - wall_h) / 2;
	int draw_end = draw_start + wall_h;

	// Desplaza la posición horizontalmente para la columna actual
	int start_x = c_i * column_w;
	int x = start_x;
	int height = abs(draw_start - draw_end);
	int color = 0;
	while (x < start_x + column_w)
	{
		y = 0;
		while (y < column_h)
		{
			if (y < game->window.size->h / 2)
				my_mlx_pixel_put(game, x, y, 0x8d9ed6); // Color superior
			else if (y > game->window.size->h / 2)
				my_mlx_pixel_put(game, x, y, 0x96867a); // Color inferior

			if ( y > draw_start && y < draw_end)
			{
				textel_y = round((y - draw_start) * 64 / height);
				color = (int) texture[(textel_y * 64) + textel_x];
				my_mlx_pixel_put(game, x, y, color); // Color de la pared
			}
			y++;
		}
		x++;
	}
}

void draw_line(t_game *game, int x0, int y0, int x1, int y1, int color)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		my_mlx_pixel_put(game, x0, y0, color);

		if (x0 == x1 && y0 == y1)
			break;

		int e2 = 2 * err;

		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}

		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

//Returns whether the wall is h, v or a corner
int check_point_in_grid(t_game *game, int x, int y, int grid_size)
{
	// Calcula las coordenadas del cuadrado actual
	int square_x = x / grid_size;
	int square_y = y / grid_size;

	// Verifica si el punto está en una línea horizontal o vertical
	if (x % grid_size == 0 && y % grid_size == 0)
		return (1);
	else if (x % grid_size == 0)
		return (2);
	else if (y % grid_size == 0)
		return (3);
	return (0);
}

void draw_line_to_direction(t_game *game, int x, int y, double length, double desv, int c_i)
{
	int grid_size = game->window.size->w / game->map.size->w; // Tamaño de la cuadrícula

	double end_x = x; // Coordenada x actual/final inicializada con la posición inicial
	double end_y = y; // Coordenada y actual/final inicializada con la posición inicial

	int steps = 0;
	int inter = 0; //interseccion, nos dice si es una pared H V o Esquina //3 H //2 V //1 ESQ

	double grid_x; //posicion en el grid en la que estamos evaluando
	double grid_y;	//posicion en el grid en la que estamos evaluando

	double old_x; //variable para guardarme la ultima vez que un punto ha cruzado una linea
	double old_y; //variable para guardarme la ultima vez que un punto ha cruzado una linea

	double realx;
	double realy;

	double dtw = 0;

	int	dir = 0;
	while (steps < length)
	{
		end_x += cos(game->p->rad + desv);
		end_y += sin(game->p->rad + desv);
		if (steps == 0)
		{
			//inicializamos la ultima vez que hemos cruzado como la primera
			old_x = end_x;
			old_y = end_y;
		}
		steps++;
		inter = check_point_in_grid(game, end_x, end_y, grid_size); //3 H //2 V
		if (inter != 0)
		{
			double distance = sqrt(pow(end_x - old_x, 2) + pow(end_y - old_y, 2)); //varibale de tolerancia por si cortamos la linea 2 veces muy cerca

			//LO QUE TENIAS
			grid_x = (int)(end_x / grid_size);
			grid_y = (int)(end_y / grid_size);

			//VERTICALMENTE
			if (inter ==3)
			{
				if (y > (int)end_y)
				{
					// printf("y arriba\n");
					dir = 1;
					grid_y -= 1;
				}
				else if (y < (int)end_y && inter == 3)
				{
					// printf("y abajo\n");
					dir = 2;
					grid_y += 0.9;
				}
			}

			//HORIZONTALMENTE
			if (inter == 2)
			{
				if (x < (int)end_x)
				{
					// printf("x derecha\n");
					dir = 3;
					grid_x += 0.9;
				}
				else if (x > (int)end_x)
				{
					// printf("x izquierda\n");
					dir = 4;
					grid_x -= 1;
				}
			}
			
			//DIAGONALMENTE //AQUI NO SE MUY BIEN QUE HACER
			if (inter == 1)
			{
				if (x < (int)end_x)
				{
					// printf("x derecha\n");
					grid_x += 0.9;
				}
				else if (x > (int)end_x)
				{
					// printf("x izquierda\n");
					grid_x -= 1;
				}

				if (y > (int)end_y)
				{
					// printf("y arriba\n");
					grid_y -= 1;
				}
				else if (y < (int)end_y && inter == 3)
				{
					// printf("y abajo\n");
					grid_y += 0.9;
				}
			}
			if (game->map.grid[(int)grid_y][(int)grid_x] == '1' || game->map.grid[(int)grid_y][(int)grid_x] == ' ')
			{
				// printf("el rayo ha chocado en las coordenadas x: %f e y:%f\nlas coordenadas del jugador son x", grid_x, grid_y);
				dtw = 50000 / cal_distance(game->p, end_x, end_y, x, y);
				realx = end_x * game->map.size->w / game->window.size->w;
				realy = end_y * game->map.size->h / game->window.size->h;
				// int i = ft_strlen(game->window.imgs[4]->addrs);
				int i = 0;
				int j = 0;
				int color = 0;
				// while(j < 64)
				// {
				// 	i = 0;
				// 	while(i < 64)
				// 	{
				// 		// printf("llegamos a entrar aqui\n")
				// 		// if (((j - 450) * (j - 450)) + ((i - 800) * (i - 800)) <= 40000)
				// 		// {
				// 		// c = (int)game->window.imgs[8]->addrs[color];
				// 		my_mlx_pixel_put(game, i, j, (int)game->window.imgs[8]->addrs[color]);
				// 		color++;
				// 		// }
				// 		i++;
				// 	}
				// 	j++;
				// }
				// while(game->window.imgs[0]->addrs[i] != '\0')
				// {
				// 	printf("%d\n", (int )game->window.imgs[0]->addrs[i]);
				// 	i++;
				// }
				// printf("la colision se da en el punto x: %f e y: %f\ninter es %d\n", realx - (int)realx, realy - (int)realy, inter);
				break;
			}
			old_x = end_x;
			old_y = end_y;
		}
	}
	// Dibuja la línea en el minimapa
	if (inter == 1)
	{
		//No dibujamos las diagonales
		//draw_line(game, x, y, (int)end_x, (int)end_y, 0xeb4034);
		draw_v_line(game, desv, dtw, c_i, game->window.imgs[8]->addrs, realy - (int)realy); //3d
	}
	else if (inter == 2)
	{
		//draw_line(game, x, y, (int)end_x, (int)end_y, 0x2a5cb8);
		if (dir == 3)
			draw_v_line(game, desv, dtw, c_i, game->window.imgs[0]->addrs, realy - (int)realy); //3d verde
		else
			draw_v_line(game, desv, dtw, c_i, game->window.imgs[1]->addrs, realy - (int)realy); //3d naranja
	}
	else if (inter == 3)
	{
		//draw_line(game, x, y, (int)end_x, (int)end_y, 0xcc12a7);
		if (dir == 1)
			draw_v_line(game, desv, dtw, c_i, game->window.imgs[2]->addrs, realx - (int)realx); //3d azul
		else
			draw_v_line(game, desv, dtw, c_i, game->window.imgs[4]->addrs, realx - (int)realx); //3d moradito
	}
}

// void draw_line_to_direction(t_game *game, int x, int y, double length, double desv, int c_i)
// {
// 	int grid_size = game->window.size->w / game->map.size->w; // Tamaño de la cuadrícula

// 	double end_x = x; // Coordenada x actual/final inicializada con la posición inicial
// 	double end_y = y; // Coordenada y actual/final inicializada con la posición inicial

// 	int steps = 0;
// 	int inter = 0; //interseccion, nos dice si es una pared H V o Esquina //3 H //2 V //1 ESQ

// 	double grid_x; //posicion en el grid en la que estamos evaluando
// 	double grid_y;	//posicion en el grid en la que estamos evaluando

// 	double old_x; //variable para guardarme la ultima vez que un punto ha cruzado una linea
// 	double old_y; //variable para guardarme la ultima vez que un punto ha cruzado una linea

// 	double dtw = 0;

// 	int	dir = 0;
// 	while (steps < length)
// 	{
// 		end_x += cos(game->p->rad + desv);
// 		end_y += sin(game->p->rad + desv);
// 		if (steps == 0)
// 		{
// 			//inicializamos la ultima vez que hemos cruzado como la primera
// 			old_x = end_x;
// 			old_y = end_y;
// 		}
// 		steps++;
// 		inter = check_point_in_grid(game, end_x, end_y, grid_size); //3 H //2 V
// 		if (inter != 0)
// 		{
// 			double distance = sqrt(pow(end_x - old_x, 2) + pow(end_y - old_y, 2)); //varibale de tolerancia por si cortamos la linea 2 veces muy cerca

// 			//LO QUE TENIAS
// 			grid_x = (int)(end_x / grid_size);
// 			grid_y = (int)(end_y / grid_size);

// 			//VERTICALMENTE
// 			if (inter ==3)
// 			{
// 				if (y > (int)end_y)
// 				{
// 					// printf("y arriba\n");
// 					dir = 1;
// 					grid_y -= 1;
// 				}
// 				else if (y < (int)end_y && inter == 3)
// 				{
// 					// printf("y abajo\n");
// 					dir = 2;
// 					grid_y += 0.9;
// 				}
// 			}

// 			//HORIZONTALMENTE
// 			if (inter == 2)
// 			{
// 				if (x < (int)end_x)
// 				{
// 					// printf("x derecha\n");
// 					dir = 3;
// 					grid_x += 0.9;
// 				}
// 				else if (x > (int)end_x)
// 				{
// 					// printf("x izquierda\n");
// 					dir = 4;
// 					grid_x -= 1;
// 				}
// 			}
			
// 			//DIAGONALMENTE //AQUI NO SE MUY BIEN QUE HACER
// 			if (inter == 1)
// 			{
// 				if (x < (int)end_x)
// 				{
// 					// printf("x derecha\n");
// 					grid_x += 0.9;
// 				}
// 				else if (x > (int)end_x)
// 				{
// 					// printf("x izquierda\n");
// 					grid_x -= 1;
// 				}

// 				if (y > (int)end_y)
// 				{
// 					// printf("y arriba\n");
// 					grid_y -= 1;
// 				}
// 				else if (y < (int)end_y && inter == 3)
// 				{
// 					// printf("y abajo\n");
// 					grid_y += 0.9;
// 				}
// 			}
// 			if (game->map.grid[(int)grid_y][(int)grid_x] == '1' || game->map.grid[(int)grid_y][(int)grid_x] == ' ')
// 			{
// 				// printf("el rayo ha chocado en las coordenadas x: %f e y:%f\nlas coordenadas del jugador son x", grid_x, grid_y);
// 				dtw = 50000 / cal_distance(game->p, end_x, end_y, x, y);
// 				double realx = end_x * game->map.size->w / game->window.size->w;
// 				double realy = end_y * game->map.size->h / game->window.size->h;
// 				// int i = ft_strlen(game->window.imgs[4]->addrs);
// 				int i = 0;
// 				int j = 0;
// 				int color = 0;
// 				// while(j < 64)
// 				// {
// 				// 	i = 0;
// 				// 	while(i < 64)
// 				// 	{
// 				// 		// printf("llegamos a entrar aqui\n")
// 				// 		// if (((j - 450) * (j - 450)) + ((i - 800) * (i - 800)) <= 40000)
// 				// 		// {
// 				// 		// c = (int)game->window.imgs[8]->addrs[color];
// 				// 		my_mlx_pixel_put(game, i, j, (int)game->window.imgs[8]->addrs[color]);
// 				// 		color++;
// 				// 		// }
// 				// 		i++;
// 				// 	}
// 				// 	j++;
// 				// }
// 				// while(game->window.imgs[0]->addrs[i] != '\0')
// 				// {
// 				// 	printf("%d\n", (int )game->window.imgs[0]->addrs[i]);
// 				// 	i++;
// 				// }
// 				printf("la colision se da en el punto x: %f e y: %f\ninter es %d\n", realx - (int)realx, realy - (int)realy, inter);
// 				break;
// 			}
// 			old_x = end_x;
// 			old_y = end_y;
// 		}
// 	}
// 	// Dibuja la línea en el minimapa
// 	if (inter == 1)
// 	{
// 		//No dibujamos las diagonales
// 		//draw_line(game, x, y, (int)end_x, (int)end_y, 0xeb4034);
// 		draw_v_line(game, desv, dtw, c_i, 0xeb4034); //3d
// 	}
// 	else if (inter == 2)
// 	{
// 		//draw_line(game, x, y, (int)end_x, (int)end_y, 0x2a5cb8);
// 		if (dir == 3)
// 			draw_v_line(game, desv, dtw, c_i, 0x5ab802); //3d verde
// 		else
// 			draw_v_line(game, desv, dtw, c_i, 0xf77102); //3d naranja
// 	}
// 	else if (inter == 3)
// 	{
// 		//draw_line(game, x, y, (int)end_x, (int)end_y, 0xcc12a7);
// 		if (dir == 1)
// 			draw_v_line(game, desv, dtw, c_i, 0x0e8ae3); //3d azul
// 		else
// 			draw_v_line(game, desv, dtw, c_i, 0xa30ee3); //3d moradito
// 	}
// }


//Draws the fov fo the player
void	draw_fov(t_game *game, double px_rela, double py_rela)
{
	double	start;
	double	end;
	int		i;
	double	l;			//len of the line

	//l = INT32_MAX;
	l = 1000000000;
	i = 0;
	start = ANGLE_S;	//Angle start to the left
	end = ANGLE_E;		//Angle end to the right
	
	double num_lines = game->window.size->w / ITER / 10; // un poco meme esta division
	double angle_increment = (end - start) / num_lines; // Calcula el incremento del ángulo
	// draw_line_to_direction(game, px_rela, py_rela, l, (0 * M_PI / 180.0), i);
	// start = 0;
	while (start <= end)
	{
		draw_line_to_direction(game, px_rela, py_rela, l, (start * M_PI / 180.0), i);
		start += angle_increment; //less number equals to more lines
		//start += 1;
		i++;
	}
}

void ft_print_minimap(t_game *game, int px_rela, int py_rela, int posx, int posy)
{
	int y;
	int x;
	int c_y; //current y
	int res = RES; // Obtener el valor de la macro RES
	int	pxps = game->window.size->w / game->map.size->w;
	t_position p_pos = game->p->pos; //(contiene un x y un y);

	c_y = 0;
	y = 0;
	while (y < (pxps * 7) / res)
	{
		x = 0;
		while (x < (pxps * 7) / res)
		{
				int offset_x = x - ((pxps * 7) / res) / 2; // Calculamos el offset en x respecto al centro
				int offset_y = y - ((pxps * 7) / res) / 2; // Calculamos el offset en y respecto al centro
				posx = p_pos.x + offset_x;
				posy = p_pos.y + offset_y;

			if (((offset_x * offset_x) + (offset_y * offset_y)) <= 2)
			{
				// Si la posición está dentro del círculo, pintar el circulito
				my_mlx_pixel_put(game, x, y, 0xfa2e0a);
			}
			else
			{
				// Si la posición está fuera del círculo, pintar el contenido del mapa completo
				if (posx >= 0 && posx < game->map.size->w && posy >= 0 && posy < game->map.size->h)
				{
					if (game->map.grid[posy][posx] == '0')
					{
						my_mlx_pixel_put(game, x, y, 0xFFFFFF);
					}
					else if (game->map.grid[posy][posx] == '1')
					{
						my_mlx_pixel_put(game, x, y, 0x8a8787);
					}
					else
					{
						// Si no hay nada, pintar como transparent
						//my_mlx_pixel_put(game, x, y, 0x000000);
					}
				}
				else
				{
					// Si la posición está fuera de los límites del mapa, pintar como transparente
					//my_mlx_pixel_put(game, x, y, 0x000000);
				}
			}
			x++;
		}
		// Actualizamos que estamos en una nueva fila
		c_y = ((y * game->map.size->h) / (game->window.size->h / res));
		y++;
	}
}

// Main function which prints the map into the window.
void	ft_print_map(t_game *game)
{
	int		posx;		//saved x position
	int		posy;		//saved y position
	int		px_rela1;	//player relative x position
	int		py_rela1;	//player relative y position
	int		px_rela2;	//player relative x position
	int		py_rela2;	//player relative y position

	posx = 0;
	posy = 0;
	px_rela1 = ((game->p->pos.x * game->window.size->w / RES_3D) / game->map.size->w);
	py_rela1 = ((game->p->pos.y * game->window.size->h / RES_3D) / game->map.size->h);
	px_rela2 = ((game->p->pos.x * game->window.size->w / RES) / game->map.size->w);
	py_rela2 = ((game->p->pos.y * game->window.size->h / RES) / game->map.size->h);

	//ft_print_grid(game->map.grid);
	draw_fov(game, px_rela1, py_rela1);
	ft_print_minimap(game, px_rela2, py_rela2, posx, posy);
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