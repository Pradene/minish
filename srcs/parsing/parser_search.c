/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_search.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:59:12 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/14 17:59:13 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*search_token(t_list *lst, char *token, int *pos, int size)
{
	t_list	*e;
	t_list	*current;
	int		brackets;
	int		c;

	current = NULL;
	e = lst;
	c = 0;
	brackets = 0;
	while (size--)
	{
		if (!ft_strcmp(e->s, "("))
			brackets++;
		else if (!ft_strcmp(e->s, ")"))
			brackets--;
		else if (!brackets && !ft_strcmp(e->s, token))
		{
			*pos = c;
			current = e;
		}
		e = e->next;
		c++;
	}
	return (current);
}

t_list	*search_orand(t_list *lst, int *pos, int size)
{
	t_list	*token;
	int		p1;
	int		p2;

	p1 = -1;
	p2 = -1;
	token = search_token(lst, "||", &p1, size);
	token = search_token(lst, "&&", &p2, size);
	if (p1 != -1 || p2 != -1)
	{
		*pos = max(p1, p2);
		return (go(lst, *pos));
	}
	return (NULL);
}

t_list	*search_sep(t_list *lst, int *pos, int size)
{
	t_list	*token;

	token = search_token(lst, ";", pos, size);
	if (token)
		return (token);
	token = search_token(lst, "&", pos, size);
	if (token)
		return (token);
	token = search_orand(lst, pos, size);
	if (token)
		return (token);
	token = search_token(lst, "|", pos, size);
	if (token)
		return (token);
	return (NULL);
}

int	search_openbrackets(t_list *lst, int first, int last)
{
	t_list	*c;

	c = go(lst, first);
	while (first < last)
	{
		if (!ft_strcmp(c->s, "("))
			return (first);
		c = c->next;
		first += 1;
	}
	return (-1);
}

int	search_closebrackets(t_list *lst, int first, int last)
{
	t_list	*c;
	int		status;

	status = 0;
	c = go(lst, first);
	while (first < last)
	{
		if (!ft_strcmp(c->s, ")") && status > 0)
			status -= 1;
		if (!ft_strcmp(c->s, ")") && status == 0)
			return (first);
		else if (!ft_strcmp(c->s, "("))
			status += 1;
		c = c->next;
		first += 1;
	}
	return (-1);
}
