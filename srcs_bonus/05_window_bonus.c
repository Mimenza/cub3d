/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:35:31 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/15 14:00:34 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//This function closes the window.
int	ft_close(t_game *game)
{
	free(game->window.imgs[0]->img);
	free(game->window.imgs[1]->img);
	free(game->window.imgs[2]->img);
	free(game->window.imgs[3]->img);
	free(game->window.imgs[0]);
	free(game->window.imgs[1]);
	free(game->window.imgs[2]);
	free(game->window.imgs[3]);
	free(game->map.ea_texture);
	free(game->map.no_texture);
	free(game->map.we_texture);
	free(game->map.so_texture);
	free(game->map.size);
	free(game->window.size);
	free(game->p);
	ft_free_doubleptr(game->map.grid);
	free(game->window.mlx);
	free(game->window.win);
	exit(0);
}

//This function creates a window struct.
t_window	ft_new_window(void *mlx, int widht, int height, char *name)
{
	t_window	window;

	window.size = malloc(sizeof(t_size));
	window.size->w = widht;
	window.size->h = height;
	window.mlx = mlx;
	window.mouse_in = 0;
	window.win = mlx_new_window(mlx, widht, height, name);
	window.img = mlx_new_image(mlx, widht, height);
	window.addrs = mlx_get_data_addr(window.img, \
	&window.bpp, &window.line_len, &window.endian);
	return (window);
}
