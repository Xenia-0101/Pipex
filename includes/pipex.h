/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:14 by xenia             #+#    #+#             */
/*   Updated: 2024/10/14 11:47:47 by xenia            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/// includes
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <fcntl.h>
# include <sys/wait.h>

# include "../libft/include/libft.h"

# define READ 0
# define WRITE 1

// structs
typedef struct s_map
{
	int		infd;
	char	*infd_n;
	int		outfd;
	int		pfd[2];
	char	**paths;

	char	**args; // command + args from command line
	char	**cmd_a; // args of the command
	char	*cmd_n; // name of the command
	char	*cmd_p; // path of the command

	pid_t	pid1;
	pid_t	pid2;

	int		state1;
	int		state2;

}	t_map;

// prototypes

// ft_init.c
void	ft_init_map(t_map **map);
// ft_free.c
void	ft_free_map(t_map **map);
void	ft_free_paths(t_map **map);
// ft_parse.c
void	ft_parse_args(t_map **map, int argc, char *argv[], char *envp[]);
void	ft_parse_files(t_map **map, int argc, char *argv[]);
void	ft_parse_cmd(t_map **map, char *argv[]);
// ft_cmd.c
void	ft_process_cmd1(t_map **map, char *argv[], char *envp[]);
void	ft_process_cmd2(t_map **map, char *argv[], char *envp[]);

#endif
