/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 17:58:57 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/14 17:58:58 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_redir_error(t_data *data, t_node *new, t_list *c)
{
	if (issep(c->next->s) || isredir(c->next->s) \
	|| handle_redir(data, new, c->s, c->next->s))
		return (1);
	return (0);
}

int	handle_redir(t_data *data, t_node *node, char *type, char *file)
{
	if (!ft_strcmp(type, ">"))
		create_redir(data, node, R_OUT, file);
	else if (!ft_strcmp(type, ">>"))
		create_redir(data, node, R_OUT2, file);
	else if (!ft_strcmp(type, "<"))
		create_redir(data, node, R_IN, file);
	else if (!ft_strcmp(type, "<<"))
	{
		if (heredoc(data, node, file))
		{
			data->c_heredoc = 1;
			return (1);
		}
	}
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
