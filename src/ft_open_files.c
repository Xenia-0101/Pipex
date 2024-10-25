/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:42:44 by xenia             #+#    #+#             */
/*   Updated: 2024/10/25 11:56:12 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

/**
 * @brief	Check if infile and outfile are accessble and open them.
 * 			Exit on failure.
 *	Check file access:
 *	infile - exists and can be read
 *	outfile - does not exist or exists and can be written into
 *	Open files:
 *	infile - open for reading
 *	outfile - if exists, truncate and open for writing, else open for writing
 *
 *
 * @param	map	Project data struct
 * @param	f1	Infile
 * @param	f2	Outfile
 */
int	ft_open_files(t_map *map, char *f1, char *f2)
{
	if (access(f1, F_OK) | (!access(f1, F_OK) && access(f1, R_OK)))
	{
		ft_put_error("Check infile permissions.");
		return (1);
	}
	if (!access(f2, F_OK) && access(f2, W_OK))
	{
		ft_put_error("Check outfile permissions.");
		return (1);
	}
	map->in_fd = open(f1, O_RDONLY, 0644);
	map->out_fd = open(f2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if ((map->in_fd == -1) | (map->out_fd == -1))
	{
		ft_put_error("Infile or outfile could not be opened.");
		return (1);
	}
	return (0);
}
