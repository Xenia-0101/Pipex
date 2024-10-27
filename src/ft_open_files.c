/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:42:44 by xenia             #+#    #+#             */
/*   Updated: 2024/10/27 23:03:06 by xenia            ###   ########.fr       */
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
int	ft_open_files(t_map *map, char *f1, char *f2)
{
	// check if "here_doc"
	// -- compare bytes
	// -- compare length
	// check if limiter
	// -- argc > 5
	// save limiter
	if (!ft_strncmp(f1, "here_doc", 8) && (ft_strlen(f1) == 8)
		&& map->argc > 5)
	{
		char *input;
		// open here_doc
		map->in_fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		// read from std in
		input = get_next_line(STDIN_FILENO);
		// -- check for limiter
		while (strncmp(input, map->argv[2], ft_strlen_gnl(map->argv[2])))
		{
			write(map->in_fd, input, ft_strlen_gnl(input));
			free(input);
			input = get_next_line(STDIN_FILENO);
		}
		// write to here_doc
		map->in_fd = open("here_doc", O_RDONLY, 0644);
		map->out_fd = open(f2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		return (3);
	}
	map->in_fd = open(f1, O_RDONLY, 0644);
	map->out_fd = open(f2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (map->in_fd == -1)
	{
		perror(f1);
		map->in_fd = open("/dev/null", O_RDONLY);
	}
	if (map->out_fd == -1)
	{
		perror(f2);
		exit(1);
	}
	return (2);
}
