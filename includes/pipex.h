/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:14 by xenia             #+#    #+#             */
/*   Updated: 2024/10/17 07:31:31 by xenia            ###   ########.fr       */
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

# define R 0
# define W 1

// structs
typedef struct s_map
{
	char	**envp;
	int		infd;
	char	*infd_n;
	int		outfd;
	int		pid;
	int		pfd[2];
	char	**paths;

	char	**args; // command + args from command line
	char	*cmd_f; // path to the binary
	char	*cmd_n; // name of the command

	// char	**cmd_a; // args of the command
	// char	*cmd_p; // path of the command

	pid_t	pid1;
	pid_t	pid2;

	int		state;
	int		state2;

}	t_map;

// prototypes

// ft_init.c
void	ft_init_map(t_map *map);
// ft_free.c
void	ft_free_map(t_map *map, int flag);
void	ft_free_paths(t_map *map);
void	ft_free_arr(char **arr);
// ft_parse.c
void	ft_parse_files(t_map *map, int argc, char *argv[]);
// *
int ft_parse_cmd(t_map *map, char *arg);
// ft_cmd.c
void	ft_process_cmd1(t_map *map, char *argv[], char *envp[]);
void	ft_process_cmd2(t_map *map, char *argv[], char *envp[]);

#endif
