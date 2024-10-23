/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:37:30 by xenia             #+#    #+#             */
/*   Updated: 2024/10/23 16:21:31 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void ft_init_map(t_map *map)
{
	map = ft_calloc(1, sizeof (t_map *));
	map->in_fd = 0;
	map->out_fd = 0;
	map->paths = NULL;
	map->state = 1;

}
