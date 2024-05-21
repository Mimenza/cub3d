/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_draw_line_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 10:46:08 by anurtiag          #+#    #+#             */
/*   Updated: 2024/05/21 09:38:53 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//Returns whether the wall is h, v or a corner
static int	c_dir(int x, int y, int grid_size)
{
	if (x % grid_size == 0 && y % grid_size == 0)
		return (1);
	else if (x % grid_size == 0)
		return (2);
	else if (y % grid_size == 0)
		return (3);
	return (0);
}

static void	add_v_step(double (*array_d)[7], int (*array_i)[3], int rel_pos[2])
{
	if ((*array_i)[INTER] == 3)
	{
		if (rel_pos[Y] > (int)(*array_d)[END_Y])
		{
			(*array_i)[DIR] = 1;
			(*array_d)[GRID_Y] -= 1;
		}
		else if (rel_pos[Y] < (int)(*array_d)[END_Y])
		{
			(*array_i)[DIR] = 2;
			(*array_d)[GRID_Y] = ceil((*array_d)[GRID_Y]) + 0.9;
		}
	}
}

static void	add_h_step(double (*array_d)[7], int (*array_i)[3], int rel_pos[2])
{
	if ((*array_i)[INTER] == 2)
	{
		if (rel_pos[X] < (int)(*array_d)[END_X])
		{
			(*array_i)[DIR] = 3;
			(*array_d)[GRID_X] = ceil((*array_d)[GRID_X]) + 0.9;
		}
		else if (rel_pos[X] > (int)(*array_d)[END_X])
		{
			(*array_i)[DIR] = 4;
			(*array_d)[GRID_X] -= 1;
		}
	}
}

static void	add_c_step(double (*array_d)[7], int (*array_i)[3], int rel_pos[2])
{
	if ((*array_i)[INTER] == 1)
	{
		if (rel_pos[X] < (int)(*array_d)[END_X])
			(*array_d)[GRID_X] = ceil((*array_d)[GRID_X]) + 0.9;
		else if (rel_pos[X] > (int)(*array_d)[END_X])
			(*array_d)[GRID_X] -= 1;
		if (rel_pos[Y] > (int)(*array_d)[END_Y])
			(*array_d)[GRID_Y] -= 1;
		else if (rel_pos[Y] < (int)(*array_d)[END_Y] && (*array_i)[INTER] == 3)
			(*array_d)[GRID_Y] = ceil((*array_d)[GRID_Y]) + 0.9;
	}
	if ((*array_d)[GRID_Y] < 0)
		(*array_d)[GRID_Y] = 0;
	if ((*array_d)[GRID_X] < 0)
		(*array_d)[GRID_X] = 0;
}

int	draw_line_utils(t_game *game, int rel_pos[2], \
double (*array_d)[7], int (*array_i)[3])
{
	(*array_d)[END_X] += cos(game->p->rad + static_double(0, 1));
	(*array_d)[END_Y] += sin(game->p->rad + static_double(0, 1));
	(*array_i)[STEPS]++;
	(*array_i)[INTER] = c_dir((*array_d)[END_X], (*array_d)[END_Y], GRID_SIZE);
	if ((*array_i)[INTER] != 0)
	{
		(*array_d)[GRID_X] = (int)((*array_d)[END_X] / GRID_SIZE);
		(*array_d)[GRID_Y] = (int)((*array_d)[END_Y] / GRID_SIZE);
		add_v_step(array_d, array_i, rel_pos);
		add_h_step(array_d, array_i, rel_pos);
		add_c_step(array_d, array_i, rel_pos);
		if ((game->map.grid[(int)(*array_d)[GRID_Y]][(int)(*array_d)[GRID_X]] \
		&& (game->map.grid[(int)(*array_d)[GRID_Y]][(int)(*array_d)[GRID_X]] \
		== '1' || game->map.grid[(int)(*array_d)[GRID_Y]] \
		[(int)(*array_d)[GRID_X]] == ' ')))
		{
			(*array_d)[DTW] = 50000 / (cal_distance(game->p, \
			ceil((*array_d)[END_X]), ceil((*array_d)[END_Y]), \
			rel_pos));
			(*array_d)[REAL_X] = (*array_d)[END_X] / GRID_SIZE;
			(*array_d)[REAL_Y] = (*array_d)[END_Y] / GRID_SIZE;
			return (0);
		}
	}
	return (1);
}
