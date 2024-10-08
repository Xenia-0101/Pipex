/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xvislock <xvislock@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 16:46:33 by xvislock          #+#    #+#             */
/*   Updated: 2024/08/03 19:03:35 by xvislock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*read_fd(int fd, char *cont)
{
	char	*buff;
	int		i;

	buff = (char *)ft_calloc_gnl(BUFFER_SIZE + 1, sizeof (char));
	if (buff == NULL)
	{
		return (NULL);
	}
	i = BUFFER_SIZE;
	while (i > 0 && !has_newline(cont))
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0 || (i == 0 && !cont) || (i == 0 && cont[0] == '\0'))
		{
			free(cont);
			free(buff);
			return (NULL);
		}
		buff[i] = '\0';
		cont = ft_strjoin_gnl(cont, buff);
	}
	free(buff);
	return (cont);
}

char	*get_line(char *cont)
{
	int		i;
	int		j;
	char	*current;

	i = 0;
	if (!cont || cont == NULL)
	{
		return (NULL);
	}
	while (cont[i] && cont[i] != '\n')
	{
		i++;
	}
	current = ft_calloc_gnl(sizeof (char), (i + 2));
	if (!current)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		current[j] = cont[j];
		j++;
	}
	current[j] = '\0';
	return (current);
}

char	*move_next(char *src)
{
	int	i;
	int	j;

	if (src == NULL)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	j = 0;
	while (src[i])
	{
		src[j] = src[i];
		i++;
		j++;
		if (!src[i])
			src[j] = '\0';
	}
	while (src[j])
	{
		src[j] = '\0';
		j++;
	}
	return (src);
}

char	*get_next_line(int fd)
{
	static char	*fd_content[1024];
	char		*current;
	int			i;

	if (fd < 0 || fd > 1023 || BUFFER_SIZE <= 0)
	{
		return (NULL);
	}
	if (!fd_content[fd] || !has_newline(fd_content[fd]))
	{
		fd_content[fd] = read_fd(fd, fd_content[fd]);
	}
	if (fd_content[fd] == NULL)
	{
		free(fd_content[fd]);
		return (NULL);
	}
	current = get_line(fd_content[fd]);
	i = 0;
	while (fd_content[fd][i] && fd_content[fd][i] != '\n')
	{
		i++;
	}
	fd_content[fd] = move_next(fd_content[fd]);
	return (current);
}
// int main(void)
// {
// 	char *res;
// 	int fd;
// 	fd = open("./tests/example.txt", O_RDONLY);

// 	res = get_next_line(fd);
// 	// printf("%s", res);
// 	// free(res);
// 	// res = get_next_line(-1);
// 	// printf("%s", res);
// 	// free(res);
// 	while(res != NULL)
// 	{
// 		printf("%s", res);
// 		free(res);
// 		res = get_next_line(fd);
// 	}

// 	return (0);
// }
