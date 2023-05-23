/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:26:00 by tmalless          #+#    #+#             */
/*   Updated: 2023/04/07 16:38:26 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static int	ft_cmp(const char *little, const char *big, size_t	len)
// {
// 	size_t	i;

// 	i = 0;
// 	while (little[i] && little[i] == big[i] && i < len)
// 		i++;
// 	if (little[i] == '\0')
// 		return (0);
// 	else
// 		return (1);
// }

// char	*ft_strnstr(const char *big, const char *little, size_t len)
// {
// 	size_t	i;

// 	i = 0;
// 	if (little[0] == '\0')
// 		return ((char *)big);
// 	while (big[i] && i < len)
// 	{
// 		if (little[0] == big[i] && ft_cmp(little, &big[i], len - i) == 0)
// 			return ((char *)&big[i]);
// 		i++;
// 	}
// 	return (0);
// }

char	*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (!ft_strlen(s2))
		return ((char *)s1);
	if ((size_t)ft_strlen(s2) > n)
		return (0);
	i = 0;
	while (i + ft_strlen(s2) <= n && s1[i])
	{
		if (memcmp(s1 + i, s2, ft_strlen(s2)) == 0)
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
