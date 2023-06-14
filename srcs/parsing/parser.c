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

void	print_error(t_data *data, char *token)
{
	if (data->c_heredoc)
		return ;
	write(2, "syntax error near unexpected token \'", 36);
	write(2, token, strlen(token));
	write(2, "\'\n", 2);
}

t_node	*new_node(void)
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
	t_list	*current;
	int		brackets;
	int		c;

	if (!lst)
		return (NULL);
	current = NULL;
	e = lst;
	c = 0;
	brackets = 0;
	while (size--)
	{
		if (!strcmp(e->s, "("))
			brackets++;
		else if (!strcmp(e->s, ")"))
			brackets--;
		else if (!brackets && !strcmp(e->s, token))
		{
			*pos = c;
			current = e;
		}
		e = e->next;
		c++;
	}
	return (current);
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
	t_list	*c;

	c = go(lst, first);
	while (first < last)
	{
		if (!strcmp(c->s, "("))
			return (first);
		c = c->next;
		first += 1;
	}
	return (-1);
}

int	search_closebrackets(t_list *lst, int first, int last)
{
	t_list	*c;
	int		status;

	status = 0;
	c = go(lst, first);
	while (first < last)
	{
		if (!strcmp(c->s, ")") && status > 0)
			status -= 1;
		if (!strcmp(c->s, ")") && status == 0)
			return (first);
		else if (!strcmp(c->s, "("))
			status += 1;
		c = c->next;
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

int	create_redir(t_data *data, t_node *node, t_type type, char *file)
{
	t_node	*tmp;

	tmp = node;
	while (tmp->right)
		tmp = tmp->right;
	tmp->right = new_node();
	if (!tmp->right)
		return (1);
	tmp = tmp->right;
	tmp_add(&data->tmp, tmp);
	tmp->type = type;
	tmp->file = ft_strdup(file);
	return (0);
}

int	handle_redir(t_data *data, t_node *node, char *type, char *file)
{
	if (!strcmp(type, ">"))
		create_redir(data, node, R_OUT, file);
	else if (!strcmp(type, ">>"))
		create_redir(data, node, R_OUT2, file);
	else if (!strcmp(type, "<"))
		create_redir(data, node, R_IN, file);
	else if (!strcmp(type, "<<"))
		if (heredoc(data, node, file))
			return (1);
	return (0);
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
	t_list	*c;

	if (last - first <= 0)
		return (NULL);
	c = go(lst, first);
	new = new_node();
	if (!new)
		return (NULL);
	tmp_add(&data->tmp, new);
	new->type = CMD;
	while (c && ++first <= last)
	{
		if (isredir(c->s))
		{
			first += 1;
			if (first > last || issep(c->next->s) || isredir(c->next->s))
				return (free_node(new), NULL);
			if (handle_redir(data, new, c->s, c->next->s))
			{
				data->c_heredoc = 1;
				return (free_node(new), NULL);
			}
			c = c->next;
		}
		else
		{
			new->cmd = add_to_cmd(new->cmd, c->s);
			if (!new->cmd)
				return (free_node(new), NULL);
		}
		c = c->next;
	}
	return (new);
}

t_node	*create_child(t_data *data, t_list *lst, int first, int last)
{
	t_node	*new;

	if (search_openbrackets(lst, first, last) != first)
		return (print_error(data, ")"), NULL);
	if (search_closebrackets(lst, first, last) != last - 1)
		return (print_error(data, "("), NULL);
	new = new_node();
	if (!new)
		return (NULL);
	tmp_add(&data->tmp, new);
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
	t_list		*token;
	t_list		*c;
	t_node		*new;
	int			pos;

	pos = -1;
	c = go(lst, first);
	token = search_sep(c, &pos, last - first);
	if (!token || pos < 0 || pos > last - first - 1)
		return (NULL);
	new = new_node();
	if (!new)
		return (NULL);
	tmp_add(&data->tmp, new);
	new->type = get_type(token->s);
	new->left = create_tree(data, lst, first, first + pos);
	if (!new->left)
		return (print_error(data, token->s), free_node(new), NULL);
	new->right = create_tree(data, lst, first + pos + 1, last);
	if (!new->right)
		return (print_error(data, token->s), free_node(new), NULL);
	return (new);
}

t_node	*create_tree(t_data *data, t_list *lst, int first, int last)
{
	t_list	*c;
	t_node	*new;
	int		pos;

	pos = -1;
	new = NULL;
	c = go(lst, first);
	if (search_sep(c, &pos, last - first))
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
		g_exit = 2;
	lstclear(&data->tokens);
}
