/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   08_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:11:21 by emimenza          #+#    #+#             */
/*   Updated: 2024/04/15 15:22:32 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

void	ft_print_error(int type)
{
	if (type == 0)
		printf("\033[1;31m [KO] \033[0m \n  WRONG FILE NAME  \n");
	else if (type == 1)
		printf("\033[1;31m [KO] \033[0m\n mlx_init() failed\n");
	else if (type == 2)
		printf("\033[1;31m [KO] \033[0m\nERROR READING THE FILE\n");
	else if (type == 3)
		printf("\033[1;31m [KO] \033[0m\nERROR CREATING THE GRID\n");
	else if (type == 4)
		printf("\033[1;31m [KO] \033[0m\nWRONG MAP SIZE!\n");
	else if (type == 5)
		printf("\033[1;31m [KO] \033[0m\nMAP MUST BE WITHIN WALL \n");
	else if (type == 6)
		printf("\033[1;31m [KO] \033[0m\nTHE MAP IS NOT SOLVEABLE\n");
	else if (type == 7)
		printf("\033[1;31m [KO] \033[0m\nFOUND A NON VALID CHAR\n");
	else if (type == 8)
		printf("\033[1;31m [KO] \033[0m\nMUST BE ONLY 1 PLAYER\n");
	else if (type == 9)
		printf("\033[1;31m [KO] \033[0m\nMUST BE ONLY 1 EXIT\n");
	else if (type == 10)
		printf("\033[1;31m [KO] \033[0m\nMUST BE MIN 1 COLL\n");
}
