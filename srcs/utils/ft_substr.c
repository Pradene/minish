/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 16:20:46 by tmalless          #+#    #+#             */
/*   Updated: 2023/03/20 13:12:30 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*ft_sub(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	i = 0;
	sub = (char *) ft_calloc(len + 1, sizeof(char));
	if (!sub)
		return (0);
	while (i < len)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	return (sub);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	s_len;
	char	*empty;

	s_len = ft_strlen(s);
	if (s_len < start)
	{
		empty = ft_calloc(1, sizeof(char));
		return (empty);
	}
	if (len < 1)
	{
		empty = ft_calloc(1, sizeof(char));
		return (empty);
	}
	else if (len > s_len - start)
	{
		return (ft_sub((char *) s, start, s_len - start));
	}
	else
	{
		return (ft_sub((char *) s, start, len));
	}
}
