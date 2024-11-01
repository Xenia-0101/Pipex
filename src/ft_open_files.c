/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:42:44 by xenia             #+#    #+#             */
/*   Updated: 2024/11/01 21:27:56 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_check_fd(t_map *map, char *f1, char *f2)
{
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
}

void	ft_read_here_doc(t_map *map)
{
	char	*input;

	input = get_next_line(STDIN_FILENO);
	while (strncmp(input, map->argv[2], ft_strlen_gnl(map->argv[2])))
	{
		write(map->in_fd, input, ft_strlen_gnl(input));
		free(input);
		input = get_next_line(STDIN_FILENO);
	}
	free(input);
}

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
	if (!ft_strncmp(f1, "here_doc", 8) && (ft_strlen(f1) == 8)
		&& map->argc > 5)
	{
		map->in_fd = open("here_doc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		ft_read_here_doc(map);
		map->in_fd = open("here_doc", O_RDONLY, 0666);
		if (access(f2, F_OK))
			open(f2, O_CREAT, 0666);
		map->out_fd = open(f2, O_RDWR | O_APPEND, 0666);
		ft_check_fd(map, f1, f2);
		return (3);
	}
	else
	{
		map->in_fd = open(f1, O_RDONLY, 0666);
		map->out_fd = open(f2, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		ft_check_fd(map, f1, f2);
		write(map->out_fd, "", 0);
	}
	return (2);
}
