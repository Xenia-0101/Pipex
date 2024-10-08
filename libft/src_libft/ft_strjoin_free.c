/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xvislock <xvislock@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 11:14:23 by xvislock          #+#    #+#             */
/*   Updated: 2024/08/21 11:36:01 by xvislock         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
	This funcion is identical to the ft_strjoin_gnl used in get_next_line.
	Compared to ft_strjoin, ft_strjoin_free frees str1.
*/

#include "../include/libft.h"

char	*ft_strjoin_free(char *str1, char const *str2)
{
	int		i;
	int		j;
	char	*str3;

	i = ft_strlen(str1);
	j = ft_strlen(str2);
	str3 = ft_calloc((i + j + 1), sizeof (char));
	if (str3 == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (str1 && str1[i])
	{
		str3[i] = str1[i];
		i++;
	}
	j = 0;
	while (str2[j])
	{
		str3[i + j] = str2[j];
		j++;
	}
	free(str1);
	return (str3);
}
