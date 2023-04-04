/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 18:26:00 by tmalless          #+#    #+#             */
/*   Updated: 2023/04/04 16:07:35 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_cmp(const char *little, const char *big, size_t	len)
{
	size_t	i;

	i = 0;
	while (little[i] && little[i] == big[i] && i < len)
		i++;
	if (little[i] == '\0')
		return (0);
	else
		return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] && i < len)
	{
		if (little[0] == big[i] && ft_cmp(little, &big[i], len - i) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (0);
}
