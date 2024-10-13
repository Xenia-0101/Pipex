/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:31:00 by xenia             #+#    #+#             */
/*   Updated: 2024/10/13 15:33:22 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_map(t_map **map)
{
	int i;
	i = 0;
	while((*map)->args1[i])
	{
		free((*map)->args1[i]);
		i++;
	}
	free((*map)->args1);
	i = 0;
	while((*map)->paths[i])
	{
		free((*map)->paths[i]);
		i++;
	}
	free((*map)->paths);
	i = 0;
	free((*map)->cmd1);
	free(*map);
}
