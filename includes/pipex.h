/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xenia <xenia@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:23:14 by xenia             #+#    #+#             */
/*   Updated: 2024/10/23 16:32:53 by xenia            ###   ########.fr       */
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
	int		state;
	// 0 - nothing to free,
	// 1 - free map,
	// 2 - free paths,

	int		in_fd;
	int		out_fd;
	char	**paths;

}	t_map;

// prototypes
// ** ft_init_map.c
void	ft_init_map(t_map *map);
// ** ft_open_files.c
int		ft_open_files(t_map *map, char *f1, char *f2);
// ** ft_utils.c
void	ft_put_error(char *error);
// ** ft_exec_cmd.c
void	ft_exec_cmd(t_map *map, char *cmd, char *env[]);


#endif
