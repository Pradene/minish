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
