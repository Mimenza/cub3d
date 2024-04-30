/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:11:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/30 09:57:02 by anurtiag         ###   ########.fr       */
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

void draw_v_line(t_game *game, double desv, int size, int c_i, int color)
{
	int column_w;
	int column_h;
	int y;
	int wall_h;

	wall_h = size;
	column_w = 1;
	column_h = game->window.size->h;

	// Calcula el inicio y el final de la pared en la columna
	int draw_start = (column_h - wall_h) / 2;
	int draw_end = draw_start + wall_h;

	// Desplaza la posición horizontalmente para la columna actual
	int start_x = c_i * column_w;
	int x = start_x;
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
				my_mlx_pixel_put(game, x, y, color); // Color de la pared
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

//OLD VERSION OF DRAW LINE TO DIRECTION

// void draw_line_to_direction(t_game *game, int x, int y, double length, double desv, int c_i)
// {
// 	int			end_x;      // End x-coordinate of the line
// 	int			end_y;      // End y-coordinate of the line
// 	double		steps;   // Number of steps to take along the line
// 	double		dx;      // Change in x-coordinate per step
// 	double		dy;      // Change in y-coordinate per step
// 	double		c_x;     // Current x-coordinate during line traversal
// 	double		c_y;     // Current y-coordinate during line traversal
// 	int			dtw;     // Distance to wall (distance to the first wall encountered)
// 	int			color;
// 	double		map_y;
// 	double		map_x;
// 	int			i;

// 	i = 0;
// 	map_x = 0;
// 	map_y = 0;
// 	color = 0xfa2e0a;
// 	dtw = -1;
// 	end_x = x + (length * cos(game->p->rad + desv));
// 	end_y = y + (length * sin(game->p->rad + desv));
// 	if (abs(end_x - x) > abs(end_y - y))
// 		steps = abs(end_x - x);
// 	else
// 		steps = abs(end_y - y);

// 	dx = (end_x - x) / steps;
// 	dy = (end_y - y) / steps;
// 	c_x = x;
// 	c_y = y;

// 	while (i <= steps)
// 	{
// 		map_x = (c_x / ((game->window.size->w / RES) / game->map.size->w));
// 		map_y = (c_y / ((game->window.size->h / RES) / game->map.size->h));

// 		if ((int)map_x >= 0 && (int)map_x < game->map.size->w && (int)map_y >= 0 && (int)map_y < game->map.size->h &&
// 			game->map.grid[(int)map_y][(int)map_x] == '1')
// 		{
// 			dtw = 11000 / cal_distance(game->p, c_x, c_y, x, y);
// 			break;
// 		}

// 		c_x += dx;
// 		c_y += dy;
// 		i++;
// 	}
// 	if (fmod(map_y, 1) > 0.96 || fmod(map_y, 1) < 0.040)
// 	{
// 		draw_line(game, x, y, (int)c_x, (int)c_y, 0x8a1a96); //minimapa
// 		//draw_v_line(game, desv, dtw, c_i, 0x8a1a96); //3d
// 	}
// 	else
// 	{
// 		draw_line(game, x, y, (int)c_x, (int)c_y, 0x2c8f1d); //minimapa
// 		//draw_line(game, x, y, (int)c_x, (int)c_y, 0x8a1a96); //minimapa
// 		//draw_v_line(game, desv, dtw, c_i, 0x2c8f1d);	//3d
// 	}
// }

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

//Función para dibujar una línea hasta una pared según la dirección dada
// void draw_line_to_direction(t_game *game, int x, int y, double length, double desv, int c_i)
// {
// 	int grid_size = game->window.size->w / game->map.size->w; // Tamaño de la cuadrícula

// 	double end_x = x; // Coordenada x actual/final inicializada con la posición inicial
// 	double end_y = y; // Coordenada y actual/final inicializada con la posición inicial

// 	int steps = 0;
// 	int inter = 0; //interseccion, nos dice si es una pared H V o Esquina //3 H //2 V //1 ESQ

// 	int grid_x; //posicion en el grid en la que estamos evaluando
// 	int grid_y;	//posicion en el grid en la que estamos evaluando
	
// 	double old_x; //variable para guardarme la ultima vez que un punto ha cruzado una linea
// 	double old_y; //variable para guardarme la ultima vez que un punto ha cruzado una linea
	
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
// 			double distance = sqrt(pow(end_x - old_x, 2) + pow(end_y - old_y, 2));//varibale de tolerancia por si cortamos la linea 2 veces muy cerca
// 			if (distance > 1.5)
// 			{
// 				printf("HEMOS CRUZADO UNA LINEA\n");

// 				grid_x = (int)(end_x / grid_size);
// 				grid_y = (int)(end_y / grid_size);
				
// 				//VERTICALMENTE
// 				if (inter ==3)
// 				{
// 					if (y > (int)end_y)
// 					{
// 						printf("y arriba\n");
// 						grid_y -= 1;
// 					}
// 					else if (y < (int)end_y && inter == 3)
// 					{
// 						printf("y abajo\n");
// 						grid_y += 1;
// 					}
// 				}
				
// 				//HORIZONTALMENTE
// 				if (inter == 2)
// 				{
// 					if (x < (int)end_x)
// 					{
// 						printf("x derecha\n");
// 						grid_x += 1;
// 					}
// 					else if (x > (int)end_x)
// 					{
// 						printf("x izquierda\n");
// 						grid_x -= 1;
// 					}
// 				}
				
// 				//DIAGONALMENTE //AQUI NO SE MUY BIEN QUE HACER
// 				if (inter == 1)
// 				{
// 					// if (y > (int)end_y)
// 					// {
// 					// 	printf("y arriba\n");
// 					// 	grid_y -= 1;
// 					// }
// 					// else if (y < (int)end_y && inter == 3)
// 					// {
// 					// 	printf("y abajo\n");
// 					// 	grid_y += 1;
// 					// }

// 					// if (x < (int)end_x)
// 					// {
// 					// 	printf("x derecha\n");
// 					// 	grid_x += 1;
// 					// }
// 					// else if (x > (int)end_x)
// 					// {
// 					// 	printf("x izquierda\n");
// 					// 	grid_x -= 1;
// 					// }
// 				}
				
// 				printf("cuadricula evaluando: x %i y %i\n", grid_x, grid_y);
// 				printf("->%c<-\n", game->map.grid[grid_y][grid_x]);
// 				printf ("inter es %i\n\n\n", inter);
				
// 				if (game->map.grid[grid_y][grid_x] == '1')
// 					break;
				
// 			}
// 			old_x = end_x;
// 			old_y = end_y;
// 		}
// 	}

// 	// Imprimir las coordenadas antes de dibujar la línea
// 	printf("Coordenadas antes de dibujar la línea:\n");
// 	printf("Inicio: (%d, %d)\n", x, y);
// 	printf("Fin: (%d, %d)\n", (int)end_x, (int)end_y);

// 	// Dibuja la línea en el minimapa
// 	if (inter == 1)
// 	{
// 		//No dibujamos las diagonales
// 		//draw_line(game, x, y, (int)end_x, (int)end_y, 0xeb4034);
// 	}
// 	else if (inter == 2)
// 		draw_line(game, x, y, (int)end_x, (int)end_y, 0x2a5cb8);
// 	else if (inter == 3)
// 		draw_line(game, x, y, (int)end_x, (int)end_y, 0xcc12a7);
// }

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
	
	// printf("La posicion del jugador es %f\n", game->p->rad);
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
			double distance = sqrt(pow(end_x - old_x, 2) + pow(end_y - old_y, 2));//varibale de tolerancia por si cortamos la linea 2 veces muy cerca
			if (distance > 1.5)
			{
				// printf("HEMOS CRUZADO UNA LINEA\n");
				// if (game->p->rad + desv <= 0 && game->p->rad + desv >= M_PI)
				// 	grid_x = ceil(end_x / grid_size);
				// else
				// 	grid_x = (int)(end_x / grid_size);
				// if (game->p->rad + desv <= (M_PI / 2) && game->p->rad + desv >= (3 * M_PI / 2))
				// 	grid_y = ceil(end_y / grid_size);
				// else
				// 	grid_y = (int)(end_y / grid_size);

				//LO QUE TENIAS
				grid_x = (int)(end_x / grid_size);
				grid_y = (int)(end_y / grid_size);
				
				//VERTICALMENTE
				if (inter ==3)
				{
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
				
				//HORIZONTALMENTE
				if (inter == 2)
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
				}
				
				//DIAGONALMENTE //AQUI NO SE MUY BIEN QUE HACER
				if (inter == 1)
				{
					// if (y > (int)end_y)
					// {
					// 	printf("y arriba\n");
					// 	grid_y -= 1;
					// }
					// else if (y < (int)end_y && inter == 3)
					// {
					// 	printf("y abajo\n");
					// 	grid_y += 1;
					// }

					// if (x < (int)end_x)
					// {
					// 	printf("x derecha\n");
					// 	grid_x += 1;
					// }
					// else if (x > (int)end_x)
					// {
					// 	printf("x izquierda\n");
					// 	grid_x -= 1;
					// }
				}
				
				// printf("cuadricula evaluando: x %f y %f\n", grid_x, grid_y);
				// printf("->%c<-\n", game->map.grid[(int)grid_y][(int)grid_x]);
				// printf ("inter es %i\n\n\n", inter);
				
				if (game->map.grid[(int)grid_y][(int)grid_x] == '1')
					break;
				
			}
			old_x = end_x;
			old_y = end_y;
		}
	}

	// Imprimir las coordenadas antes de dibujar la línea
	// printf("Coordenadas antes de dibujar la línea:\n");
	// printf("Inicio: (%d, %d)\n", x, y);
	// printf("Fin: (%d, %d)\n", (int)end_x, (int)end_y);

	// Dibuja la línea en el minimapa
	if (inter == 1)
	{
		//No dibujamos las diagonales
		//draw_line(game, x, y, (int)end_x, (int)end_y, 0xeb4034);
		draw_line(game, x, y, (int)end_x, (int)end_y, 0x2a5cb8);
	}
	else if (inter == 2)
		draw_line(game, x, y, (int)end_x, (int)end_y, 0x2a5cb8);
	else if (inter == 3)
		draw_line(game, x, y, (int)end_x, (int)end_y, 0xcc12a7);
}

// t_position *h_intersection(t_player *player)
// {
// 	double	ay;
// 	double	ax;

// 	if (player->rad >= 0 && player->rad <= M_PI)
// 		ay = floor(player->pos.y) * (-1);
// 	else
// 		ay = floor(player->pos.y) * (1);
// 	ax = 1 / tan(player->rad);
	
// }

// void draw_line_to_direction(t_game *game, int x, int y, double length, double desv, int c_i)
// {
// 	int			end_x;      // End x-coordinate of the line
// 	int			end_y;      // End y-coordinate of the line
// 	double		steps;   // Number of steps to take along the line
// 	double		dx;      // Change in x-coordinate per step
// 	double		dy;      // Change in y-coordinate per step
// 	double		c_x;     // Current x-coordinate during line traversal
// 	double		c_y;     // Current y-coordinate during line traversal
// 	int			dtw;     // Distance to wall (distance to the first wall encountered)
// 	int			color;
// 	double		map_y;
// 	double		map_x;
// 	int			i;

// 	i = 0;
// 	map_x = 0;
// 	map_y = 0;
// 	color = 0xfa2e0a;
// 	dtw = -1;
// 	end_x = x + (length * cos(game->p->rad + desv));
// 	end_y = y + (length * sin(game->p->rad + desv));
// 	if (abs(end_x - x) > abs(end_y - y))
// 		steps = abs(end_x - x);
// 	else
// 		steps = abs(end_y - y);

// 	dx = (end_x - x) / steps;
// 	dy = (end_y - y) / steps;
// 	c_x = x;
// 	c_y = y;

// 	while (i <= steps)
// 	{
// 		map_x = (c_x / ((game->window.size->w / RES) / game->map.size->w));
// 		map_y = (c_y / ((game->window.size->h / RES) / game->map.size->h));

// 		if ((int)map_x >= 0 && (int)map_x < game->map.size->w && (int)map_y >= 0 && (int)map_y < game->map.size->h &&
// 			game->map.grid[(int)map_y][(int)map_x] == '1')
// 		{
// 			dtw = 11000 / cal_distance(game->p, c_x, c_y, x, y);
// 			break;
// 		}

// 		c_x += dx;
// 		c_y += dy;
// 		i++;
// 	}
// 	if (fmod(map_y, 1) > 0.96 || fmod(map_y, 1) < 0.040)
// 	{
// 		// draw_line(game, x, y, (int)c_x, (int)c_y, 0x8a1a96); //minimapa
// 		draw_v_line(game, desv, dtw, c_i, 0x8a1a96); //3d
// 	}
// 	else
// 	{
// 		//draw_line(game, x, y, (int)c_x, (int)c_y, 0x2c8f1d); //minimapa
// 		// draw_line(game, x, y, (int)c_x, (int)c_y, 0x8a1a96); //minimapa
// 		draw_v_line(game, desv, dtw, c_i, 0x2c8f1d);	//3d
// 	}
// }

//Draws the fov fo the player
void	draw_fov(t_game *game, double px_rela, double py_rela)
{
	double start;
	double	end;
	int		i;
	double	l;			//len of the line

	//l = INT32_MAX;
	l = 1000000000;
	i = 0;
	start = ANGLE_S;	//Angle start to the left
	end = ANGLE_E;		//Angle end to the right
	
	double num_lines = game->window.size->w / ITER / 10;
	double angle_increment = (end - start) / num_lines; // Calcula el incremento del ángulo

	draw_line_to_direction(game, px_rela, py_rela, l, (0 * M_PI / 180.0), i);

	// while (start <= end)
	// {
	// 	draw_line_to_direction(game, px_rela, py_rela, l, (start * M_PI / 180.0), i);
	// 	//start += angle_increment; //less number equals to more lines
	// 	start += 10;
	// 	i++;
	// }
}

// void	ft_print_minimap(t_game *game, int px_rela, int py_rela, int posx, int posy)
// {
// 	int		y;
// 	int		x;
// 	int		c_y;		//current y

// 	c_y = 0;
// 	y = 0;
// 	while ( y < (game->window.size->h / RES))
// 	{
// 		x = 0;
// 		while (x < (game->window.size->w / RES))
// 		{
// 			if ((((x - px_rela) * (x - px_rela)) + ((y - py_rela) * (y - py_rela))) <= 20)
// 			{
// 				//If para printear circulito
// 				my_mlx_pixel_put(game, x, y + 540, 0xfa2e0a);
// 			}
// 			else if ((posx != ((x * 5) / (game->window.size->w / RES))) || (c_y != posy))
// 			{
// 				//If para printear lineas grid
// 				my_mlx_pixel_put(game, x, y + 540, 0x000000);
// 				posx = ((x * 5) / (game->window.size->w / RES));
// 				posy = ((y * 5) / (game->window.size->h / RES));
// 			}
// 			else
// 			{
// 				//Else para printear todo lo demas
// 				posx = ((x * 5) / (game->window.size->w / RES));
// 				posy = ((y * 5) / (game->window.size->h / RES));
// 				if (game->map.grid[posy][posx] == '0')
// 					my_mlx_pixel_put(game, x, y + 540, 0xFFFFFF);
// 				else if (game->map.grid[posy][posx] == '1')
// 				{
// 					my_mlx_pixel_put(game, x, y + 540, 0x8a8787);
// 				}
// 				else if (game->map.grid[posy][posx] == ' ')
// 					my_mlx_pixel_put(game, x, y + 540, 0x000000);
// 				else
// 					my_mlx_pixel_put(game, x, y + 540, 0xFFFFFF);
// 			}
// 			x++;
// 		}
// 		//Actualizamos que estamos en nueva fila
// 		c_y = ((y * 5) / (game->window.size->h / RES));
// 		y++;
// 	}
// }

void	ft_print_minimap(t_game *game, int px_rela, int py_rela, int posx, int posy)
{
	int		y;
	int		x;
	int		c_y;		//current y

	c_y = 0;
	y = 1;
	while ( y < (game->window.size->h))
	{
		x = 1;
		while (x < (game->window.size->w))
		{
			if ((((x - px_rela) * (x - px_rela)) + ((y - py_rela) * (y - py_rela))) <= 20)
			{
				//If para printear circulito
				my_mlx_pixel_put(game, x, y , 0xfa2e0a);
			}
			else if ((posx != ((x * game->map.size->w) / (game->window.size->w))) || (c_y != posy))
			{
				//If para printear lineas grid
				my_mlx_pixel_put(game, x, y , 0x000000);
				posx = ((x * game->map.size->w) / (game->window.size->w));
				posy = ((y * game->map.size->h) / (game->window.size->h));
			}
			else
			{
				//Else para printear todo lo demas
				posx = ((x * game->map.size->w) / (game->window.size->w));
				posy = ((y * game->map.size->h) / (game->window.size->h));
				if (game->map.grid[posy][posx] == '0')
					my_mlx_pixel_put(game, x, y , 0xFFFFFF);
				else if (game->map.grid[posy][posx] == '1')
				{
					my_mlx_pixel_put(game, x, y , 0x8a8787);
				}
				else if (game->map.grid[posy][posx] == ' ')
					my_mlx_pixel_put(game, x, y , 0x000000);
				else
					my_mlx_pixel_put(game, x, y , 0xFFFFFF);
			}
			x++;
		}
		//Actualizamos que estamos en nueva fila
		c_y = ((y * game->map.size->h) / (game->window.size->h));
		y++;
	}
}


// Main function which prints the map into the window.
void	ft_print_map(t_game *game)
{
	int		posx;		//saved x position
	int		posy;		//saved y position
	int		px_rela;	//player relative x position
	int		py_rela;	//player relative y position
	posx = 0;
	posy = 0;
	px_rela = ((game->p->pos.x * game->window.size->w / RES) / game->map.size->w);
	py_rela = ((game->p->pos.y * game->window.size->h / RES) / game->map.size->h);

	//ft_print_grid(game->map.grid);
	ft_print_minimap(game, px_rela, py_rela, posx, posy);
	draw_fov(game, px_rela, py_rela);
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