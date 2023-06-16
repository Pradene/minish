/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 06:29:28 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/01 06:29:29 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_node	*new_node(t_data *data, t_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = type;
	node->cmd = NULL;
	node->file = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->left = NULL;
	node->right = NULL;
	tmp_add(&data->tmp, node);
	return (node);
}

void	parse(t_data *data, t_node **root, char **s)
{
	data->tokens = tokens(s);
	if (!data->tokens)
		return ;
	*root = create_tree(data, data->tokens, 0, lstsize(data->tokens));
	if (!(*root))
		g_exit = 2;
	lstclear(&data->tokens);
}
