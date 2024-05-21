/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   09_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anurtiag <anurtiag@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:11:21 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/21 10:29:34 by anurtiag         ###   ########.fr       */
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
		printf("\033[1;31m [KO] \033[0m \nWRONG FILE NAME  \n");
	else if (type == 1)
		printf("\033[1;31m [KO] \033[0m\nMlx_init() failed\n");
	else if (type == 2)
		printf("\033[1;31m [KO] \033[0m\nERROR READING THE FILE\n");
	else if (type == 3)
		printf("\033[1;31m [KO] \033[0m\nERROR CREATING THE GRID\n");
	else if (type == 4)
		printf("\033[1;31m [KO] \033[0m\ndata missing in the .cub file\n");
	else if (type == 5)
		printf("\033[1;31m [KO] \033[0m\nFound a duplicated data\n");
	else if (type == 6)
		printf("\033[1;31m [KO] \033[0m\nTHE PLAYER FELL INTO THE VOID :(\n");
	else if (type == 7)
		printf("\033[1;31m [KO] \033[0m\nFOUND A NON VALID CHAR\n");
	else if (type == 8)
		printf("\033[1;31m [KO] \033[0m\nMUST BE ONLY 1 PLAYER\n");
	else if (type == 9)
		printf("\033[1;31m [KO] \033[0m\nINVALID COLOR\n");
}
