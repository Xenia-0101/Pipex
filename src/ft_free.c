/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:31:00 by xenia             #+#    #+#             */
/*   Updated: 2024/10/14 11:48:32 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_free_paths(t_map **map)
{
	int	i;

	i = 0;
	while((*map)->paths[i])
	{
		free((*map)->paths[i]);
		i++;
	}
	free((*map)->paths);
}

void	ft_free_map(t_map **map)
{
	(*map)->infd = 0;
	free((*map)->infd_n);
}
