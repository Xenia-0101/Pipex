/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:14 by xenia             #+#    #+#             */
/*   Updated: 2024/10/25 23:23:06 by xenia            ###   ########.fr       */
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

// structs
typedef struct s_map
{
	int		in_fd;
	int		out_fd;
	char	**paths;
	char	*full_path;
	char	**cmd_args;
}	t_map;

// prototypes
// ** ft_init_map.c
void	ft_init_map(t_map *map);
// ** ft_open_files.c
void	ft_open_files(t_map *map, char *f1, char *f2);
// ** ft_utils.c
void	ft_put_error(char *error);
// ** ft_exec_cmd.c
void	ft_exec_cmd(t_map *map, char *cmd, char *env[]);
// ** ft_get_paths.c
void	ft_get_paths(t_map *map, char *env[]);
// ** ft_free.c
void	ft_free_arr(char **arr);
// ** ft_get_full_path.c
int		ft_get_full_path(t_map *map, char *cmd);

#endif
