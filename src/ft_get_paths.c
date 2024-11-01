/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:37:49 by xenia             #+#    #+#             */
/*   Updated: 2024/11/01 20:42:21 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_get_paths(t_map *map, char *env[])
{
	char	*path;

	path = NULL;
	while (*env)
	{
		if (!ft_strncmp("PATH=", *env, 5))
		{
			path = ft_substr(*env, 5, sizeof (*path) - 5);
		}
		env++;
	}
	if (path != NULL)
	{
		map->paths = ft_split(path, ':');
		free(path);
		return ;
	}
	else
	{
		perror("PATH not found");
		free(path);
		exit (1);
	}
}
