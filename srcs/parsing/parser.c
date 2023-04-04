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

static int	isredir(char *s)
{
	if (!strcmp(s, ">>")
		|| !strcmp(s, "<<")
		|| !strcmp(s, ">")
		|| !strcmp(s, "<"))
		return (1);
	return (0);
}

static int	issep(char *s)
{
	if (!strcmp(s, "||")
		|| !strcmp(s, "&&")
		|| !strcmp(s, "|")
		|| !strcmp(s, "&")
		|| !strcmp(s, ";"))
		return (1);
	return (0);
}

void	redir(t_node *node, char *redir_type)
{
	if (!strcmp(redir_type, ">>"))
		node->redir_type = DBL_OUT;
	else if (!strcmp(redir_type, "<<"))
		node->redir_type = DBL_IN;
	else if (!strcmp(redir_type, ">"))
		node->redir_type = OUT;
	else if (!strcmp(redir_type, "<"))
		node->redir_type = IN;
	else
		node->redir_type = NONE;
}

static void	redir_file(t_node *node, char *redir_file)
{
	if (isredir(redir_file) || issep(redir_file))
		return ;
	node->redir_file = strdup(redir_file);
	if (!node->redir_file)
		return ;
}

static t_node	*new_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->s = NULL;
	node->redir_type = NONE;
	node->redir_file = NULL;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

static void	create_child(t_node **node, char *sep)
{
	t_node	*left;
	t_node	*right;

	left = new_node();
	right = new_node();
	if (!left || !right)
		return ;
	left->s = (*node)->s;
	(*node)->s = strdup(sep);
	(*node)->left = left;
	(*node)->right = right;
	(*node) = (*node)->right;
}

static void	print_tree(t_node *node)
{
	if (!node)
		return ;
	print_tree(node->left);
	printf("%s \n", node->s);
	print_tree(node->right);
}

void	parse(t_node **root, char *s)
{
	char	*token;
	char	*tmp;
	t_node	*cmd;

	(*root) = new_node();
	if (!(*root))
		return ;
	cmd = *root;
	tmp = s;
	token = next_token(&tmp);
	while (token)
	{
		if (cmd->redir_type && !cmd->redir_file)
			redir_file(cmd, token);
		else if (isredir(token))
			redir(cmd, token);
		else if (issep(token))
			create_child(&cmd, token);
		else
			cmd->s = ft_stradd(cmd->s, strcat(token, " "));
		free(token);
		token = next_token(&tmp);
	}
	print_tree(*root);
}
