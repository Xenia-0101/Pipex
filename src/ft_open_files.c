/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_files.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:42:44 by xenia             #+#    #+#             */
/*   Updated: 2024/10/28 16:23:58 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"
int		ft_open_files(t_map *map, char *f1, char *f2);
void	ft_read_here_doc(t_map *map);
void	ft_check_fd(t_map *map, char *f1, char *f2);

/**
 * @brief	Check if files were opened sucessfully and handle errors.
 *
 * If in_fd == -1, set appropriate error and open an empty file.
 * If out_fd == -1, set appropriate error and exit program.
 *
 * @param map	Map data struct
 * @param f1	Infile name
 * @param f2	Outfile name
 */
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

/**
 * @brief	Read standard input and write contents to here_doc.
 *
 * Read from standard input using get_next_line, save the contents in row var.
 * While row is not equal to the limiter, write row into here_doc (in_fd),
 * free row and read another line.
 * If limiter is read from stdin, free row and return from the function
 *
 * @param	map	Map data struct.
 */
void	ft_read_here_doc(t_map *map)
{
	char	*row;

	row = get_next_line(STDIN_FILENO);
	while (strncmp(row, map->argv[2], ft_strlen_gnl(map->argv[2])))
	{
		write(map->in_fd, row, ft_strlen_gnl(row));
		free(row);
		row = get_next_line(STDIN_FILENO);
	}
	free(row);
}

/**
 * @brief	Handle opening of infile and outfile with proper permissions.
 *
 * If name of the infile is here_doc and the number of arguments is larger
 * than 5:
 * 		create here_doc, open it for writing and call ft_read_here_doc
 * 		(read stdin into here_doc).
 * 		Open here_doc for reading.
 * 		If Outfile does not exist, create it.
 * 		Open outfile for reading and writing, O_APPEND flag means the content
 * 		will be appended instead of rewriting the file.
 * 		Call ft_check_fd function to handle possible errors.
 * Else:
 * 		open infile for reading, and outfile for writing.
 * 		Call ft_check_fd function to handle possible errors.
 *
 * @param	map	Project data struct
 * @param	f1	Infile name
 * @param	f2	Outfile name
 *
 * @return int	The index of the first command line argument.
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
	}
	return (2);
}
