/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:03:13 by tmalless          #+#    #+#             */
/*   Updated: 2023/05/10 16:14:33 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*clean_cmd(char *cmd)
{
	char	*new;
	int		i;
	int		j;
	int		quote;

	i = -1;
	j = -1;
	quote = 0;
	new = malloc(1);
	new[0] = '\0';
	while (cmd[++i])
	{
		if (quote == 0 && ft_strchr("\'\"", cmd[i]))
			quote_status(cmd[i], &quote);
		else if (quote == 1 && cmd[i] == '\'')
			quote_status(cmd[i], &quote);
		else if (quote == 2 && cmd[i] == '\"')
			quote_status(cmd[i], &quote);
		else
		{
			new = addchar(new, cmd[i]);
			if (!new)
				return (cmd);
		}
	}
	free(cmd);
	return (new);
}

char	**clean_cmds(char **cmds)
{
	int	i;

	if (!cmds)
		return (NULL);
	i = -1;
	while (cmds[++i])
		cmds[i] = clean_cmd(cmds[i]);
	return (cmds);
}
