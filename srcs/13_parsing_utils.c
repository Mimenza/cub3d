/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:42:48 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/07 12:43:32 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

char	*parse_textures(char *line)
{
	char * r_line;
	
	while (*line != ' ' && *line != '\t' && *line != '\0')
		line++;

	while (*line == ' ' || *line == '\t')
		line++;

	r_line = ft_substr(line, 0, ft_strchr(line, '\n') - line);//REMOVES THE LAST JUMP LINE
	//free(line);
	return (r_line);
}

int		parse_colors(char *line)
{
	int	r;
	int	g;
	int	b;

	while (*line != ' ' && *line != '\t' && *line != '\0')
		line++;

	while (*line == ' ' || *line == '\t')
		line++;
			
	r = atoi(line);
	g = atoi(ft_strchr(line, ',') + 1); //Ref to the first ,
	b = atoi(ft_strchr(ft_strchr(line, ',') + 1, ',') + 1); // Ref to the second ,
	
	return((r << 16) | (g << 8) | b);
}

//CHECKS THE PREV LINES
int	check_flags(int *flag, int empty_flag)
{
	//error si empezamos nuevo grupo (flag == 1) y la anterio linea no esta vacia (empty_flag != 0)
	//error si no empezamos nuevo grupo (flag == 0) y la anterior linea esta vacia (empty_flag == 1)
	
	if ((empty_flag == 0 && *flag == 1) || (empty_flag == 1 && *flag == 0))
	{
		if (*flag == 1)
			*flag = 0;
		return (0);
	}
	if (*flag == 1)
		*flag = 0;
	
	return (1);
}

//CHECKS IF THE LINE IS EMPTY
int is_empty(char *str)
{
	while (*str != '\0')
	{
		if (*str != ' ' && *str != '\t' && *str != '\n')
		{
			return (0);
		}
		str++;
	}
	return (1);
}
