/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 18:55:08 by tmalless          #+#    #+#             */
/*   Updated: 2023/04/07 20:17:43 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// char	*ft_strjoin(char *s1, char *s2)
// {
// 	size_t	size;
// 	size_t	i;
// 	size_t	j;
// 	char	*join;

// 	size = ft_strlen(s1) + ft_strlen(s2);
// 	i = 0;
// 	j = 0;
// 	join = (char *) ft_calloc(size + 1, sizeof(char));
// 	if (!join)
// 		return (0);
// 	while (s1[i])
// 	{
// 		join[i] = s1[i];
// 		i++;
// 	}
// 	while (s2[j])
// 	{
// 		join[i] = s2[j];
// 		i++;
// 		j++;
// 	}
// 	return (join);
// }

char	*ft_strjoin(char *s1, char *s2)
{
	int		size1;
	int		size2;
	char	*str;

	size1 = ft_strlen(s1);
	size2 = ft_strlen(s2);
	str = malloc((size1 + size2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, s1, size1);
	ft_memcpy(str + size1, s2, size2);
	str[size1 + size2] = 0;
	if (s1)
		free(s1);
	return (str);
}
