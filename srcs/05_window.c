/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   05_window.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:35:31 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/30 16:05:41 by anurtiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//This function closes the window.
static int	ft_close(void)
{
	exit(0);
}

//This function creates a window struct.
t_window	ft_new_window(void *mlx, int widht, int height, char *name)
{
	t_window	window;
	window.size = malloc(sizeof(t_size));
	window.size->w = widht;
	window.size->h = height;
	printf("h %i\n", height);
	printf("w %i\n", widht);
	window.mlx = mlx;
	window.win = mlx_new_window(mlx, widht, height, name);
	window.img = mlx_new_image(mlx, widht, height);
	window.addrs = mlx_get_data_addr(window.img, &window.bpp, &window.line_len, &window.endian);
	
	printf("w %i h %i\n", widht, height);
	mlx_hook(window.win, 17, 0, ft_close, 0);
	return (window);
}
