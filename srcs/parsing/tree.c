/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 19:20:33 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/05 19:20:34 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_rlist(t_rlist **lst)
{
	t_rlist	*current;

	if (!lst)
		return ;
	while ((*lst))
	{
		current = ((*lst))->next;
		free((*lst)->file);
		free((*lst));
		(*lst) = current;
	}
}

void	free_cmd(t_node *node)
{
	if (node->s)
		free(node->s);
	free_rlist(&node->redir);
}

void	free_node(t_node *node)
{
	if (!node || node->type == ERR)
		return ;
	else if (node->type == CMD)
		free_cmd(node);
	if (node->right)
		free_node(node->right);
	if (node->left)
		free_node(node->left);
	free(node);
}

void	print_cmd(t_node *node)
{
	if (node->type == ERR)
		printf("ERR\n");
	else if (node->type == CMD)
		printf("CMD: %s\n", node->s);
	else if (node->type == PIPE)
		printf("PIPE\n");
	else if (node->type == DBL_PIPE)
		printf("DBL_PIPE\n");
	else if (node->type == AMP)
		printf("AMP\n");
	else if (node->type == DBL_AMP)
		printf("DBL_AMP\n");
	else if (node->type == SEMICOL)
		printf("SEMICOL\n");
	else if (node->type == OPEN_BRACKET)
		printf("OPEN_BRACKET\n");
	else if (node->type == CLOSE_BRACKET)
		printf("CLOSE_BRACKET\n");
}

void	print_redir(t_rlist *lst)
{
	t_rlist	*current;

	current = lst;
	while (current)
	{
		if (current->type == IN)
			printf("IN ");
		else if (current->type == DBL_IN)
			printf("DBL_IN ");
		else if (current->type == OUT)
			printf("OUT ");
		else if (current->type == DBL_OUT)
			printf("DBL_OUT ");
		printf("%s\n", current->file);
		current = current->next;
	}
}

void	print_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->type == OPEN_BRACKET)
		print_cmd(node);
	print_tree(node->left);
	if (node->type != OPEN_BRACKET)
		print_cmd(node);
	if (node->redir != NULL)
		print_redir(node->redir);
	print_tree(node->right);
}
