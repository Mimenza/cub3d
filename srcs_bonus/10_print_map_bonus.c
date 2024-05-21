/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_print_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 11:11:08 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/21 10:54:26 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

double	cal_distance(t_player *player, double c_x, \
double c_y, int rel_pos[2])
{
	double	a;
	double	b;
	double	distance;

	a = 0;
	b = 0;
	if (player->rad == 0 || player->rad == M_PI)
		return (fabs(rel_pos[X] - (c_x)));
	else if (player->rad == (M_PI / 2) || player->rad == (3 * M_PI / 2))
		return (fabs(rel_pos[Y] - (c_y)));
	else
	{
		a = ((tan(player->rad + (M_PI / 2))));
		b = (rel_pos[Y] - (rel_pos[X] * a));
	}
	distance = fabs((-(a * c_x) + c_y - b) / sqrt((a * a) + (1)));
	return (distance);
}

static void	draw_v_line(t_game *game, double size, int *texture, double column)
{
	int	y;
	int	textel_x;
	int	textel_y;
	int	draw_start;
	int	draw_end;

	draw_start = ((game->window.size->h - size) / 2);
	draw_end = (draw_start + size);
	textel_x = round(column * 64);
	y = 0;
	while (y < game->window.size->h)
	{
		if (y < game->window.size->h / 2)
			my_mlx_pixel_put(game, static_int(0, 1), y, game->map.c_color);
		else if (y > game->window.size->h / 2)
			my_mlx_pixel_put(game, static_int(0, 1), y, game->map.f_color);
		if (y > draw_start && y < draw_end)
		{
			textel_y = round((y - draw_start) * \
			64 / abs(draw_start - draw_end));
			my_mlx_pixel_put(game, static_int(0, 1), \
			y, (int)texture[(textel_y * 64) + textel_x]);
		}
		y++;
	}
}

static void	draw_v_line_utils(t_game *game, double array_d[7], int array_i[3])
{
	if (array_i[INTER] == 2)
	{
		if (array_i[DIR] == 3)
			draw_v_line(game, array_d[DTW], game->window.imgs[2]->addrs, \
			array_d[REAL_Y] - (int)array_d[REAL_Y]);
		else
			draw_v_line(game, array_d[DTW], game->window.imgs[3]->addrs, \
			array_d[REAL_Y] - (int)array_d[REAL_Y]);
	}
	else if (array_i[INTER] == 3)
	{
		if (array_i[DIR] == 1)
			draw_v_line(game, array_d[DTW], game->window.imgs[0]->addrs, \
			array_d[REAL_X] - (int)array_d[REAL_X]);
		else
			draw_v_line(game, array_d[DTW], game->window.imgs[1]->addrs, \
			array_d[REAL_X] - (int)array_d[REAL_X]);
	}
}

static void	draw_line_to_direction(t_game *game, int rel_pos[2], double length)
{
	static int	old_inter = 0;
	static int	old_dir = 0;
	double		array_d[7];
	int			array_i[3];

	array_d[END_X] = rel_pos[X];
	array_d[END_Y] = rel_pos[Y];
	array_i[STEPS] = 0;
	array_i[INTER] = 0;
	array_i[DIR] = 0;
	while (array_i[STEPS] < length)
	{
		if (draw_line_utils(game, rel_pos, &array_d, &array_i) == 0)
			break ;
	}
	if (array_i[INTER] == 1)
	{
		array_i[INTER] = old_inter;
		array_i[DIR] = old_dir;
	}
	draw_v_line_utils(game, array_d, array_i);
	old_inter = array_i[INTER];
	old_dir = array_i[DIR];
}

//Draws the fov fo the player
void	draw_fov(t_game *game, int rel_pos[2])
{
	int		end;
	int		i;
	double	start;
	double	l;
	double	angle_increment;

	l = 1000000;
	i = 0;
	start = ANGLE_S;
	end = ANGLE_E;
	angle_increment = (end - start) / (game->window.size->w / ITER / 10);
	while (start <= end)
	{
		static_double((start * M_PI / 180.0), 0);
		static_int(i, 0);
		draw_line_to_direction(game, rel_pos, l);
		start += angle_increment;
		i++;
	}
}
