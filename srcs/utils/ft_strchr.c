/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 00:39:33 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/14 00:39:43 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	int	size;
	int	i;

	size = ft_strlen(s);
	i = -1;
	while (++i < size)
	{
		if (s[i] == c)
			return ((char *)s + i);
	}
	return (NULL);
}
