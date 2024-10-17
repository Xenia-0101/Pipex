/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 15:35:23 by xenia             #+#    #+#             */
/*   Updated: 2024/10/17 07:40:32 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_parse_files(t_map *map, int argc, char *argv[])
{
	// check proper access to infile and outfile
	if (access(argv[1], F_OK)  | access(argv[1], R_OK))
	{
		perror("Infile permissions");
		exit(1);
	}
	if (!access(argv[argc - 1], F_OK) && access(argv[argc - 1], W_OK))
	{
		perror("Outfile permissions");
		exit(1);
	}
	map->infd = open(argv[1], O_RDONLY);
	map->infd_n = argv[1];
	 // set mode when creating file to 0644 - owner: rw, others: r
	map->outfd = open(argv[argc - 1], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if ((map->infd == -1) | (map->outfd == -1))
	{
		perror("Open file");
		exit(1);
	}
}

/**
 * @brief 	get command name and its arguments and
 * 			set the full path to the binary
 *
 * @param	map	project data
 * @param	arg	the command as passed in to the pipex
 */
int ft_parse_cmd(t_map *map, char *arg)
{
	int	i;

	// get command name
	map->args = ft_split(arg, ' ');
	map->cmd_n = ft_strjoin("/", map->args[0]);
	// check if binary exists
	i = 0;
	while(map->paths[i])
	{
		map->cmd_f = ft_strjoin(map->paths[i], map->cmd_n);
		if (!access(map->cmd_f, F_OK))
		{
			free(map->cmd_n);
			return (0);
		}
		free(map->cmd_f);
		i++;
	}
	return (1);
}
