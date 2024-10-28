/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:37:30 by xenia             #+#    #+#             */
/*   Updated: 2024/10/27 22:53:38 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_init_map(t_map *map, int argc, char *argv[])
{
	map->in_fd = 0;
	map->out_fd = 0;
	map->argv = argv;
	map->argc = argc;
	map->paths = NULL;
	map->full_path = NULL;
}
