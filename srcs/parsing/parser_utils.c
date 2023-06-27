/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:59:23 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/27 15:32:38 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_list	*go(t_list *lst, int index)
{
	t_list	*e;

	e = lst;
	while (e && index--)
		e = e->next;
	return (e);
}

int	isredir(char *s)
{
	if (!ft_strcmp(s, ">"))
		return (1);
	else if (!ft_strcmp(s, ">>"))
		return (1);
	else if (!ft_strcmp(s, "<"))
		return (1);
	else if (!ft_strcmp(s, "<<"))
		return (1);
	return (0);
}

int	issep(char *s)
{
	if (!ft_strcmp(s, "("))
		return (1);
	else if (!ft_strcmp(s, ")"))
		return (1);
	else if (!ft_strcmp(s, "||"))
		return (1);
	else if (!ft_strcmp(s, "|"))
		return (1);
	else if (!ft_strcmp(s, "&&"))
		return (1);
	else if (!ft_strcmp(s, "&"))
		return (1);
	else if (!ft_strcmp(s, ";"))
		return (1);
	return (0);
}

void	print_error(t_data *data, char *token)
{
	if (data->c_heredoc)
		return ;
	write(2, "syntax error near unexpected token `", 36);
	write(2, token, ft_strlen(token));
	write(2, "\'\n", 2);
}

t_type	get_type(char *s)
{
	if (!ft_strcmp(s, "("))
		return (OPEN_BRACKET);
	else if (!ft_strcmp(s, ")"))
		return (CLOSE_BRACKET);
	else if (!ft_strcmp(s, "||"))
		return (DBL_PIPE);
	else if (!ft_strcmp(s, "|"))
		return (PIPE);
	else if (!ft_strcmp(s, "&&"))
		return (DBL_AMP);
	else if (!ft_strcmp(s, "&"))
		return (AMP);
	else if (!ft_strcmp(s, ";"))
		return (SEMICOL);
	return (ERR);
}
