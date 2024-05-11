/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: emimenza <emimenza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:42:48 by emimenza          #+#    #+#             */
/*   Updated: 2024/05/11 17:25:27 by emimenza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/cub3d.h"

int	assign_data_t(char *line, char **ref)
{
	char	*r_line;

	if (*ref != NULL)
		return (0);
	while (*line != ' ' && *line != '\t' && *line != '\0')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	r_line = ft_substr(line, 0, ft_strchr(line, '\n') - line);
	*ref = r_line;
	return (1);
}

int	assign_data_c(char *line, int *ref)
{
	int	r;
	int	g;
	int	b;

	if (*ref != 0)
		return (0);
	while (*line != ' ' && *line != '\t' && *line != '\0')
		line++;
	while (*line == ' ' || *line == '\t')
		line++;
	r = atoi(line);
	g = atoi(ft_strchr(line, ',') + 1);
	b = atoi(ft_strchr(ft_strchr(line, ',') + 1, ',') + 1);
	*ref = (r << 16) | (g << 8) | b;
	return (1);
}

//CHECKS THE PREV LINES
int	check_flags(int *flag, int empty_flag)
{
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
int	is_empty(char *str)
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
