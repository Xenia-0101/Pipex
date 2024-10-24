/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:37:49 by xenia             #+#    #+#             */
/*   Updated: 2024/10/24 08:05:20 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	ft_get_paths(t_map *map, char *env[])
{
	int i = 0;
	char *path;

	path = NULL;
	while (*env)
	{
		if (!ft_strncmp("PATH=", *env, 5))
		{
			path = ft_substr(*env, 5, sizeof (*path) - 5 );
		}
		env++;
	}
	if (path != NULL)
	{
		map->paths = ft_split(path, ':');
		free(path);
		map->state = 2;
		return (0);
	}
	else
	{
		ft_put_error("PATH not found");
		free(path);
		return (1);
	}
}
