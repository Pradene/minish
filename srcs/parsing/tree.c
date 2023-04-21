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

void	free_cmd(t_node *node)
{
	if (node->cmd)
		free(node->cmd);
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
	if (node->in)
		free(node->in);
	if (node->dbl_in)
		free(node->dbl_in);
	if (node->out)
		free(node->out);
	if (node->dbl_out)
		free(node->dbl_out);
	free(node);
}

void	print_redir(t_node *node)
{
	if (node->in)
		printf("IN: %s\n", node->in);
	else if (node->dbl_in)
		printf("DBL_IN: %s\n", node->dbl_in);
	else if (node->out)
		printf("OUT: %s\n", node->out);
	else if (node->dbl_out)
		printf("DBL_OUT: %s\n", node->dbl_out);
}

void	print_cmd(t_node *node)
{
	if (node->type == ERR)
		printf("ERR\n");
	else if (node->type == CMD)
		printf("CMD: %s\n", node->cmd);
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

void	print_tree(t_node *node)
{
	if (!node)
		return ;
	if (node->type == OPEN_BRACKET)
		print_cmd(node);
	print_tree(node->left);
	if (node->type != OPEN_BRACKET)
		print_cmd(node);
	print_redir(node);
	print_tree(node->right);
}
