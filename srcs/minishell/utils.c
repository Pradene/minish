/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:12:59 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/14 22:13:16 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	d_free(char **ss)
{
	int	i;

	if (!ss)
		return ;
	i = -1;
	while (ss[++i])
		free(ss[i]);
	free(ss);
}

int	last_index(char *s, int c)
{
	char	*p;
	int		index;

	p = ft_strrchr(s, c);
	index = p - s;
	return (index);
}

int	get_size(char **ss)
{
	int	c;

	if (!ss)
		return (0);
	c = 0;
	while (ss[c])
		c += 1;
	return (c);
}
