/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 21:35:49 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/01 21:35:52 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_tmp(t_node *node)
{
	if (node && node->type == CMD)
		dfree(node->cmd);
	if (node && (node->type == R_IN \
	|| node->type == R_OUT || node->type == R_OUT2))
		free(node->file);
	if (node && node->fd_in != -1)
		close(node->fd_in);
	if (node && node->fd_out != -1)
		close(node->fd_out);
	if (!node)
		return ;
	free(node);
	node = NULL;
}

void	tmp_clear(t_tmp **lst)
{
	t_tmp	*p;

	if (!lst)
		return ;
	while ((*lst))
	{
		p = ((*lst))->next;
		free_tmp((*lst)->node);
		free((*lst));
		(*lst) = p;
	}
	(*lst) = NULL;
}

t_tmp	*tmp_last(t_tmp *lst)
{
	t_tmp	*current;

	if (!lst)
		return (NULL);
	current = lst;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	tmp_add(t_tmp **lst, t_node *node)
{
	t_tmp	*new;

	if (!lst)
		return ;
	new = malloc(sizeof(t_tmp));
	if (!new)
		return ;
	new->node = node;
	new->next = NULL;
	if (*lst)
		tmp_last(*lst)->next = new;
	else
		*lst = new;
}
