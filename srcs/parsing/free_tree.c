/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:33:19 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/30 22:17:33 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	free_node(t_node **node)
{
	if (!(*node))
		return ;
	if ((*node) && (*node)->type == CMD)
		dfree((*node)->cmd);
	if ((*node) && ((*node)->type == R_IN \
	|| (*node)->type == R_OUT || (*node)->type == R_OUT2))
		free((*node)->file);
	if ((*node) && (*node)->fd_in != -1)
		close((*node)->fd_in);
	if ((*node) && (*node)->fd_out != -1)
		close((*node)->fd_out);
	(*node)->fd_out = -1;
	(*node)->fd_in = -1;
	if ((*node) && (*node)->right)
		free_node(&(*node)->right);
	if ((*node) && (*node)->left)
		free_node(&(*node)->left);
	free(*node);
	(*node) = NULL;
}

void	free_data(t_data *data)
{
	if (data->tokens)
		lstclear(&data->tokens);
	if (data->fd1 != -1)
		close(data->fd1);
	if (data->fd0 != -1)
		close(data->fd0);
	data->fd0 = -1;
	data->fd1 = -1;
	dfree(data->env);
	free_node(&data->root);
	data->root = NULL;
	lclear(&data->tmp);
}

int	size_tree(t_node *node)
{
	if (!node || node->type == R_IN \
	|| node->type == R_OUT || node->type == R_OUT2)
		return (0);
	return (size_tree(node->left) + 1 + size_tree(node->right));
}
