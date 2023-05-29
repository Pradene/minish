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

void	lclear(t_l **lst)
{
	t_l	*p;

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

void	free_data(t_data *data)
{
	if (data->tokens)
		lstclear(&data->tokens);
	if (data->fd1 != -1)
		close(data->fd1);
	if (data->fd0 != -1)
		close(data->fd0);
	dfree(data->env);
	free_node(data->root);
	data->root = NULL;
	lclear(&data->tmp);
}
