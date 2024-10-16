/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:35:23 by xenia             #+#    #+#             */
/*   Updated: 2024/10/16 05:57:19 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_parse_files(t_map *map, int argc, char *argv[])
{
	// check proper access to infile and outfile
	if (access(argv[1], F_OK)  | access(argv[1], R_OK))
	{
		perror("Infile permissions: ");
		exit(1);
		// ToDo: error handling - file does not exist or can't be read
	}
	if (!access(argv[argc - 1], F_OK) && access(argv[argc - 1], W_OK))
	{
		perror("Outfile permissions: ");
		exit(1);
		// ToDo: error handling - can't write to file
	}
	map->infd = open(argv[1], O_RDONLY);
	map->infd_n = argv[1];
	 // set mode when creating file to 0644 - owner: rw, others: r
	map->outfd = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if ((map->infd == -1) | (map->outfd == -1))
	{
		perror("Open file ");
		exit(1);
	}
}
