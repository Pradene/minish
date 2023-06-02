/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addchar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:37:06 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/01 21:37:08 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*addchar(char *s, char c)
{
	int		size;
	char	*new;

	size = ft_strlen(s);
	new = malloc(sizeof(char) * (size + 1 + 1));
	if (!new)
		return (s);
	memcpy(new, s, size);
	new[size] = c;
	new[size + 1] = '\0';
	if (s)
		free(s);
	return (new);
}
