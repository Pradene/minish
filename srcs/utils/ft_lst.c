/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 06:28:29 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/01 06:28:30 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*lstlast(t_list *lst)
{
	t_list	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current && current->next)
		current = current->next;
	return (current);
}

int	lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	lstadd(t_list **lst, t_list *new)
{
	if (!lst)
		return ;
	if (*lst)
		lstlast(*lst)->next = new;
	else
		*lst = new;
}

void	lstclear(t_list **lst)
{
	t_list	*p;

	if (!lst || !(*lst))
		return ;
	while ((*lst))
	{
		p = ((*lst))->next;
		free((*lst)->s);
		free((*lst));
		(*lst) = p;
	}
	(*lst) = NULL;
}

void	lstprint(t_list *lst)
{
	t_list	*e;

	e = lst;
	while (e)
	{
		printf("%s\n", e->s);
		e = e->next;
	}
}

t_list	*lstnew(char *s)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->s = s;
	new->next = 0;
	return (new);
}

