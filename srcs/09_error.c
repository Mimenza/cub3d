/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:11:21 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/06 17:07:39 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	ft_print_ok(void)
{
	printf("\033[0;32m [OK] \033[0m \n\n");
}
void	ft_print_error(int type)
{
	if (type == 0)
		printf("\033[1;31m [KO] \033[0m \n  WRONG FILE NAME  \n"); //X
	else if (type == 1)
		printf("\033[1;31m [KO] \033[0m\n mlx_init() failed\n");
	else if (type == 2)
		printf("\033[1;31m [KO] \033[0m\nERROR READING THE FILE\n"); //X
	else if (type == 3)
		printf("\033[1;31m [KO] \033[0m\nERROR CREATING THE GRID\n"); //X
	else if (type == 4)
		printf("\033[1;31m [KO] \033[0m\ndata missing in the .cub file\n"); //X
	else if (type == 6)
		printf("\033[1;31m [KO] \033[0m\nTHE MAP MUST BE WITHIN WALLS\n");//X
	else if (type == 7)
		printf("\033[1;31m [KO] \033[0m\nFOUND A NON VALID CHAR\n"); //X
	else if (type == 8)
		printf("\033[1;31m [KO] \033[0m\nMUST BE ONLY 1 PLAYER\n"); //x
}
