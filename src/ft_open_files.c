/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:42:44 by xenia             #+#    #+#             */
/*   Updated: 2024/10/25 23:22:06 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief	Open infile and outfile.
 * 			Exit on failure.
 *
 * @param	map	Project data struct
 * @param	f1	Infile
 * @param	f2	Outfile
 */
void	ft_open_files(t_map *map, char *f1, char *f2)
{
	map->in_fd = open(f1, O_RDONLY, 0644);
	map->out_fd = open(f2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (map->in_fd == -1)
	{
		perror(f1);
		exit(1);
	}
	if (map->out_fd == -1)
	{
		perror(f2);
		exit(1);
	}
}
