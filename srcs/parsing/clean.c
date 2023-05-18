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

static void	quote_status(char c, int *quote)
{
	if ((*quote == 1 && c == '\'')
		|| (*quote == 2 && c == '\"'))
		*quote = 0;
	else if (*quote == 0 && c == '\'')
		*quote = 1;
	else if (*quote == 0 && c == '\"')
		*quote = 2;
	else
		return ;
}

char	*clean_cmd(char *cmd)
{
	char	*new_cmd;
	int		i;
	int		j;
	int		quote;

	new_cmd = ft_calloc(ft_strlen(cmd) + 1, sizeof(char));
	if (!new_cmd)
		return (NULL);
	i = -1;
	j = -1;
	quote = 0;
	while (cmd[++i])
	{
		if (quote == 0 && ft_strchr("\'\"", cmd[i]))
			quote_status(cmd[i], &quote);
		else if (quote == 1 && cmd[i] == '\'')
			quote_status(cmd[i], &quote);
		else if (quote == 2 && cmd[i] == '\"')
			quote_status(cmd[i], &quote);
		else
			new_cmd[++j] = cmd[i];
	}
	free(cmd);
	return (new_cmd);
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