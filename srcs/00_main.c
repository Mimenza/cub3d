/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:46:06 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/06 16:49:46 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

//This function checks if the str given ends in the ext.
static int	ft_check_ext(char *str, char *ext)
{
	int	size_s;
	int	size_ext;

	printf("CHECKING FILE EXT...");
	size_s = ft_strlen(str);
	size_ext = ft_strlen(ext);
	while (size_ext != 0 && size_s != 0)
	{
		if (str[size_s] != ext[size_ext])
			return (ft_print_error(0), 0);
		size_ext--;
		size_s--;
	}
	return (ft_print_ok(),1);
}

int	main(int argc, char **argv)
{
	t_game		game;

	if (argc == 2 && ft_check_ext(*(argv + 1), ".cub"))
	{
		ft_create_game(*(argv + 1), &game);
	}
}
