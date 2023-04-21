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

static t_node	*new_node(void)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	if (!node)
		return (NULL);
	node->type = ERR;
	node->cmd = NULL;
	node->in = NULL;
	node->dbl_in = NULL;
	node->out = NULL;
	node->dbl_out = NULL;
	node->fd_in = -1;
	node->fd_out = -1;
	node->left = NULL;
	node->right = NULL;
	return (node);
}

t_list	*search_token(t_list *lst, char *token, int *pos, int size)
{
	t_list	*e;
	t_list	*c;
	int		brackets;
	int		current;

	if (!lst)
		return (NULL);
	c = NULL;
	e = lst;
	current = 0;
	brackets = 0;
	while (size--)
	{
		if (!strcmp(e->s, "("))
			brackets++;
		else if (!strcmp(e->s, ")"))
			brackets--;
		else if (!brackets && !strcmp(e->s, token))
		{
			*pos = current;
			c = e;
		}
		e = e->next;
		current++;
	}
	return (c);
}

t_list	*search_sep(t_list *lst, int *pos, int size)
{
	t_list	*token;

	token = search_token(lst, ";", pos, size);
	if (token)
		return (token);
	token = search_token(lst, "||", pos, size);
	if (token)
		return (token);
	token = search_token(lst, "&&", pos, size);
	if (token)
		return (token);
	token = search_token(lst, "|", pos, size);
	if (token)
		return (token);
	token = search_token(lst, "&", pos, size);
	if (token)
		return (token);
	return (NULL);
}

t_list	*go(t_list *lst, int index)
{
	t_list	*e;

	e = lst;
	while (e && index--)
		e = e->next;
	return (e);
}

int	search_openbrackets(t_list *lst, int first, int last)
{
	t_list	*current;

	current = go(lst, first);
	while (first < last)
	{
		if (!strcmp(current->s, "("))
			return (first);
		current = current->next;
		first += 1;
	}
	return (-1);
}

int	search_closebrackets(t_list *lst, int first, int last)
{
	t_list	*current;
	int		status;

	status = 0;
	current = go(lst, first);
	while (first < last)
	{
		if (!strcmp(current->s, ")") && status > 0)
			status -= 1;
		if (!strcmp(current->s, ")") && status == 0)
			return (first);
		else if (!strcmp(current->s, "("))
			status += 1;
		current = current->next;
		first += 1;
	}
	return (-1);
}

t_type	get_type(char *s)
{
	if (!strcmp(s, "("))
		return (OPEN_BRACKET);
	else if (!strcmp(s, ")"))
		return (CLOSE_BRACKET);
	else if (!strcmp(s, "||"))
		return (DBL_PIPE);
	else if (!strcmp(s, "|"))
		return (PIPE);
	else if (!strcmp(s, "&&"))
		return (DBL_AMP);
	else if (!strcmp(s, "&"))
		return (AMP);
	else if (!strcmp(s, ";"))
		return (SEMICOL);
	return (ERR);
}

int	isredir(char *s)
{
	if (!strcmp(s, ">"))
		return (1);
	else if (!strcmp(s, ">>"))
		return (1);
	else if (!strcmp(s, "<"))
		return (1);
	else if (!strcmp(s, "<<"))
		return (1);
	return (0);
}

int	issep(char *s)
{
	if (!strcmp(s, "("))
		return (1);
	else if (!strcmp(s, ")"))
		return (1);
	else if (!strcmp(s, "||"))
		return (1);
	else if (!strcmp(s, "|"))
		return (1);
	else if (!strcmp(s, "&&"))
		return (1);
	else if (!strcmp(s, "&"))
		return (1);
	else if (!strcmp(s, ";"))
		return (1);
	return (0);
}

void	handle_redir(t_node *node, char *type, char *file)
{
	if (!strcmp(type, ">"))
	{
		if (node->out)
			free(node->out);
		if (node->dbl_out)
			free(node->dbl_out);
		node->dbl_out = NULL;
		node->out = strdup(file);
	}
	else if (!strcmp(type, ">>"))
	{
		if (node->out)
			free(node->out);
		if (node->dbl_out)
			free(node->dbl_out);
		node->out = NULL;
		node->dbl_out = strdup(file);
	}
	else if (!strcmp(type, "<"))
	{
		if (node->in)
			free(node->in);
		if (node->dbl_in)
			free(node->dbl_in);
		node->dbl_in = NULL;
		node->in = strdup(file);
	}
	else if (!strcmp(type, "<<"))
	{
		if (node->in)
			free(node->in);
		if (node->dbl_in)
			free(node->dbl_in);
		node->in = NULL;
		node->dbl_in = strdup(file);
	}
}

t_node	*create_leaf(t_list *lst, int first, int last)
{
	t_node	*new;
	t_list	*current;

	if (last - first <= 0)
		return (NULL);
	current = go(lst, first);
	new = new_node();
	if (!new)
		return (NULL);
	new->type = CMD;
	while (current && ++first <= last)
	{
		if (isredir(current->s))
		{
			if (first + 1 > last)
				return (free(new), NULL);
			handle_redir(new, current->s, current->next->s);
			current = current->next;
			first += 1;
		}
		else
		{
			new->cmd = ft_stradd(new->cmd, strcat(current->s, " "));
			if (!new->cmd)
				return (free(new), NULL);
		}
		current = current->next;
	}
	return (new);
}

t_node	*create_child(t_list *lst, int first, int last)
{
	t_node	*new;

	if (search_openbrackets(lst, first, last) != first
		|| search_closebrackets(lst, first, last) != last - 1)
		return (NULL);
	new = new_node();
	if (!new)
		return (NULL);
	new->type = OPEN_BRACKET;
	new->right = new_node();
	if (!new->right)
		return (free_node(new), NULL);
	new->right->type = CLOSE_BRACKET;
	new->left = create_tree(lst, first + 1, last - 1);
	if (!new->left)
		return (free_node(new), NULL);
	return (new);
}

t_node	*create_node(t_list *lst, int first, int last)
{
	t_list	*token;
	t_list	*current;
	t_node	*new;
	int		pos;

	pos = -1;
	current = go(lst, first);
	token = search_sep(current, &pos, last - first);
	if (!token || pos <= 0 || pos >= last - first - 1)
		return (NULL);
	new = new_node();
	if (!new)
		return (NULL);
	new->type = get_type(token->s);
	new->left = create_tree(lst, first, first + pos);
	if (!new->left)
		return (free_node(new), NULL);
	new->right = create_tree(lst, first + pos + 1, last);
	if (!new->right)
		return (free_node(new), NULL);
	return (new);
}

t_node	*create_tree(t_list *lst, int first, int last)
{
	t_list	*current;
	t_node	*new;
	int		pos;

	pos = -1;
	new = NULL;
	current = go(lst, first);
	if (search_sep(current, &pos, last - first))
		new = create_node(lst, first, last);
	else if (search_openbrackets(lst, first, last) != -1
		|| search_closebrackets(lst, first, last) != -1)
		new = create_child(lst, first, last);
	else
		new = create_leaf(lst, first, last);
	return (new);
}

void	parse(t_node **root, char **s)
{
	t_list	*lst;

	lst = tokens(s);
	if (!lst)
		return ;
	*root = create_tree(lst, 0, ft_lstsize(lst));
	if (!(*root))
	{
		ft_lstclear(&lst);
		printf("Error\n");
	}
	ft_lstclear(&lst);
	print_tree(*root);
}
