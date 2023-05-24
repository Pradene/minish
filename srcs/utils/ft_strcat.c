/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 18:11:12 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/07 18:11:13 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strcat(char *s1, char *s2)
{
	char	*s;
	int		size_s1;
	int		size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	s = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (!s)
		return (NULL);
	ft_memcpy(s, s1, size_s1);
	ft_memcpy(s + size_s1, s2, size_s2 + 1);
	return (s);
}

char	*ft_stradd(char *s1, char *s2)
{
	char	*s;
	int		size_s1;
	int		size_s2;

	if (!s2)
		return (s1);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	s = malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (!s)
		return (s1);
	ft_memcpy(s, s1, size_s1);
	ft_memcpy(s + size_s1, s2, size_s2 + 1);
	if (s1)
		free(s1);
	return (s);
}
