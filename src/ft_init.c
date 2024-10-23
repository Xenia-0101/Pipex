/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:29:11 by xenia             #+#    #+#             */
/*   Updated: 2024/10/16 08:22:27 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_init_map(t_map *map)
{
	map->state = 0;
	map->infd = 0;
	map->infd_n = 0;
	map->outfd = 0;
	map->pfd[0] = 0;
	map->pfd[1] = 0;
	map->paths = NULL;
	map->args = NULL;
	map->cmd_a = NULL;
	map->cmd_n = NULL;
	map->cmd_p = NULL;
	map->pid1 = 0;
	map->pid2 = 0;
}
