/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:09:53 by xenia             #+#    #+#             */
/*   Updated: 2024/10/26 22:31:09 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_put_error(char *error)
{
	int	len;

	len = ft_strlen(error);
	write(2, "\033[31m", 6);
	write(2, error, len);
	write(2, "\033[0m\n", 6);
}

void	ft_put_error_2(char *error, char *val)
{
	int	len;

	len = ft_strlen_gnl(error);
	write(2, "\033[31m", 6);
	write(2, error, len);
	write(2, ": ", 2);
	len = ft_strlen_gnl(val);
	write(2, val, len);
	write(2, "\033[0m\n", 6);
}

int	ft_arrlen(char **arr)
{
	int	i;

	i = 0;
	if (arr != NULL)
	{
		while (arr[i])
		{
			i++;
		}
	}
	return (i);
}	
