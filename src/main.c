/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 16:29:41 by xenia             #+#    #+#             */
/*   Updated: 2024/10/24 13:30:56 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

void	ft_clean_exit(t_map *map, int status)
{
	ft_free(map);
	exit(status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_map	map;
	int		i;

	if (argc < 5)
	{
		ft_put_error("Incorrect number of arguments");
		exit(1);
	}
	ft_init_map(&map);
	// check and open files
	if (ft_open_files(&map, argv[1], argv[argc - 1]))
		ft_clean_exit(&map, 1);
	// get paths
	if (ft_get_paths(&map, envp))
		ft_clean_exit(&map, 1);
	// redirect infile to stdin
	dup2(map.in_fd, STDIN_FILENO);
	close(map.in_fd);
	i = 2;
	// execute commands
	while (i < argc - 2)
	{
		ft_exec_cmd(&map, argv[i], envp);
		i++;
	}
	dup2(map.out_fd, STDOUT_FILENO);
	close(map.out_fd);
	ft_get_full_path(&map, argv[i]);
	execve(map.full_path, map.cmd_args, envp);

}
