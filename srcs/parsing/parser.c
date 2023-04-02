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

void	clear_cmds(t_cmd **cmds)
{
	t_cmd	*cc;

	if (!cmds)
		return ;
	cc = (*cmds);
	while ((*cmds))
	{
		cc = ((*cmds))->next;
		ft_lstclear(&cc->arg);
		free((*cmds));
		(*cmds) = cc;
	}
}

t_cmd	*last_cmd(t_cmd *cmds)
{
	t_cmd	*cc;

	if (!cmds)
		return (NULL);
	cc = cmds;
	while (cc->next)
		cc = cc->next;
	return (cc);
}

void	next_cmd(t_cmd **cmds, t_cmd *cmd)
{
	if (!cmds)
		return ;
	if (*cmds)
		last_cmd(*cmds)->next = cmd;
	else
		*cmds = cmd;
}

t_cmd	*new_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->arg = NULL;
	cmd->redir = NONE;
	cmd->rfile = NULL;
	cmd->next = NULL;
	return (cmd);
}

void	print_cmds(t_cmd *cmds)
{
	t_cmd	*cc;
	t_list	*current;

	if (!cmds)
		return ;
	cc = cmds;
	while (cc)
	{
		if (!cc->arg)
			continue ;
		current = cc->arg;
		printf("args: ");
		while (current)
		{
			printf("%s ", current->s);
			current = current->next;
		}
		printf("\n");
		printf("redir: %d, file: %s \n", cc->redir, cc->rfile);
		cc = cc->next;
	}
}

int	check_redir(char *s)
{
	if (strcmp(s, "<") == 0
		|| strcmp(s, "<<") == 0
		|| strcmp(s, ">") == 0
		|| strcmp(s, ">>") == 0)
		return (1);
	return (0);
}

t_redir	get_redir(char *s)
{
	if (strcmp(s, "<") == 0)
		return (IN);
	else if (strcmp(s, "<<") == 0)
		return (DBL_IN);
	else if (strcmp(s, ">") == 0)
		return (OUT);
	else if (strcmp(s, ">>") == 0)
		return (DBL_OUT);
	else
		return (NONE);
}

void	next_arg(t_list **lst, char *s)
{
	t_list	*arg;

	arg = malloc(sizeof(t_list));
	if (!arg)
		return ;
	arg->s = strdup(s);
	arg->next = NULL;
	ft_lstadd(lst, arg);
}

void	parse(t_cmd **cmds, t_list *tokens)
{
	t_list	*cc;
	t_cmd	*cmd;

	cmd = new_cmd();
	if (!cmd)
		return ;
	cc = tokens;
	while (cc)
	{
		if (strcmp(cc->s, "|") != 0 && !check_redir(cc->s))
			next_arg(&cmd->arg, cc->s);
		if (check_redir(cc->s))
		{
			cmd->redir = get_redir(cc->s);
			cc = cc->next;
			if (!cc || !strcmp(cc->s, "|") || check_redir(cc->s))
				break ;
			cmd->rfile = cc->s;
		}
		if (strcmp(cc->s, "|") == 0)
		{
			next_cmd(cmds, cmd);
			cmd = new_cmd();
			if (!cmd)
				return ;
		}
		cc = cc->next;
	}
	next_cmd(cmds, cmd);
}
