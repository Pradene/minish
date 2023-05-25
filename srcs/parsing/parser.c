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
	node->file = NULL;
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

t_list	*go(t_list *lst, int index)
{
	t_list	*e;

	e = lst;
	while (e && index--)
		e = e->next;
	return (e);
}

int	max(int n1, int n2)
{
	if (n1 > n2)
		return (n1);
	return (n2);
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

int	create_redir(t_node *node, t_type type, char *file)
{
	t_node	*tmp;

	tmp = node;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = new_node();
	if (!tmp->right)
		return (1);
	tmp = tmp->right;
	tmp->type = type;
	tmp->file = ft_strdup(file);
	return (0);
}

void	handle_redir(t_data *data, t_node *node, char *type, char *file)
{
	if (!strcmp(type, ">"))
		create_redir(node, R_OUT, file);
	else if (!strcmp(type, ">>"))
		create_redir(node, R_OUT2, file);
	else if (!strcmp(type, "<"))
		create_redir(node, R_IN, file);
	else if (!strcmp(type, "<<"))
		heredoc(data, node, file);
}

char	**add_to_cmd(char **cmds, char *cmd)
{
	char	**new;
	int		size;
	int		i;

	if (!cmd)
		return (cmds);
	size = dsize(cmds) + 1;
	new = malloc(sizeof(char *) * (size + 1));
	if (!new)
		return (cmds);
	new[size] = NULL;
	i = 0;
	while (cmds && cmds[i])
	{
		new[i] = ft_strdup(cmds[i]);
		if (!new[i])
			return (dfree(new), cmds);
		i += 1;
	}
	new[i] = ft_strdup(cmd);
	if (!new[i])
		return (dfree(new), cmds);
	dfree(cmds);
	return (new);
}

t_node	*create_leaf(t_data *data, t_list *lst, int first, int last)
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
			first += 1;
			if (first > last \
			|| issep(current->next->s) || isredir(current->next->s))
				return (free(new), NULL);
			handle_redir(data, new, current->s, current->next->s);
			current = current->next;
		}
		else
		{
			new->cmd = add_to_cmd(new->cmd, current->s);
			if (!new->cmd)
				return (free_node(new), NULL);
		}
		current = current->next;
	}
	return (new);
}

t_node	*create_child(t_data *data, t_list *lst, int first, int last)
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
	new->left = create_tree(data, lst, first + 1, last - 1);
	if (!new->left)
		return (free_node(new), NULL);
	return (new);
}

t_node	*create_node(t_data *data, t_list *lst, int first, int last)
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
	new->left = create_tree(data, lst, first, first + pos);
	if (!new->left)
		return (free_node(new), NULL);
	new->right = create_tree(data, lst, first + pos + 1, last);
	if (!new->right)
		return (free_node(new), NULL);
	return (new);
}

t_node	*create_tree(t_data *data, t_list *lst, int first, int last)
{
	t_list	*current;
	t_node	*new;
	int		pos;

	pos = -1;
	new = NULL;
	current = go(lst, first);
	if (search_sep(current, &pos, last - first))
		new = create_node(data, lst, first, last);
	else if (search_openbrackets(lst, first, last) != -1
		|| search_closebrackets(lst, first, last) != -1)
		new = create_child(data, lst, first, last);
	else
		new = create_leaf(data, lst, first, last);
	return (new);
}

void	parse(t_data *data, t_node **root, char **s)
{
	data->tokens = tokens(s);
	if (!data->tokens)
		return ;
	*root = create_tree(data, data->tokens, 0, lstsize(data->tokens));
	if (!(*root))
	{
		prerror("Syntax error\n");
		g_exit = 2;
	}
	lstclear(&data->tokens);
}
