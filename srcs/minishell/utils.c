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

void	quote_status(char c, int *quote)
{
	if ((*quote == 1 && c == '\'')
		|| (*quote == 2 && c == '\"'))
		*quote = 0;
	else if (*quote == 0 && c == '\'')
		*quote = 1;
	else if (*quote == 0 && c == '\"')
		*quote = 2;
	else
		return ;
}

void	dfree(char **ss)
{
	int	i;

	if (!ss)
		return ;
	i = -1;
	while (ss[++i])
		free(ss[i]);
	free(ss);
}

int	dsize(char **ss)
{
	int	c;

	if (!ss)
		return (0);
	c = 0;
	while (ss[c])
		c += 1;
	return (c);
}

int	last_index(char *s, int c)
{
	char	*p;
	int		index;

	p = ft_strrchr(s, c);
	index = p - s;
	return (index);
}

void	lclear(t_tmp **lst)
{
	t_tmp	*p;

	if (!lst)
		return ;
	while ((*lst))
	{
		p = ((*lst))->next;
		free((*lst));
		(*lst) = p;
	}
	(*lst) = NULL;
}
