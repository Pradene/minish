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
	int	i;

	if (!node->cmd)
		return ;
	i = -1;
	while (node->cmd[++i])
		free(node->cmd[i]);
	free(node->cmd);
}

void	free_node(t_node *node)
{
	if (!node || node->type == ERR)
		return ;
	else if (node->type == CMD)
		free_cmd(node);
	else if (node->type == R_IN || node->type == HEREDOC \
	|| node->type == R_OUT || node->type == R_OUT2)
		free(node->file);
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
		printf("CMD: %s\n", node->cmd[0]);
	else if (node->type == R_OUT || node->type == R_OUT2 \
	|| node->type == R_IN || node->type == HEREDOC)
		printf("REDIR: %s\n", node->file);
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
	print_tree(node->right);
}
