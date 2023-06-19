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

// char	*clean_cmd(char *cmd)
// {
// 	char	*new;
// 	int		i;
// 	int		quote;

// 	if (!cmd)
// 		return (NULL);
// 	i = -1;
// 	quote = 0;
// 	new = calloc(1, sizeof(char));
// 	while (cmd[++i])
// 	{
// 		if ((quote == 0 && ft_strchr("\'\"", cmd[i])) \
// 		|| (quote == 1 && cmd[i] == '\'') \
// 		|| (quote == 2 && cmd[i] == '\"'))
// 			quote_status(cmd[i], &quote);
// 		else
// 		{
// 			new = addchar(new, cmd[i]);
// 			if (!new)
// 				return (cmd);
// 		}
// 	}
// 	free(cmd);
// 	return (new);
// }

// char	**clean_cmds(char **cmds)
// {
// 	int	i;

// 	if (!cmds)
// 		return (NULL);
// 	i = -1;
// 	while (cmds[++i])
// 		cmds[i] = clean_cmd(cmds[i]);
// 	return (cmds);
// }

int	space(char *cmd)
{
	int	i;
	int	count;
	int	quote;

	i = -1;
	count = 0;
	quote = 0;
	while (cmd[++i])
	{
		quote_status(cmd[i], &quote);
		if (!quote && cmd[i] == ' ')
			count++;
		while (cmd[i] == ' ' && cmd[i + 1] && cmd[i + 1] == ' ')
			i++;
	}
	return (count);
}

int	count(char **cmds)
{
	int	i;
	int	j;
	int	quote;
	int	count;

	i = -1;
	quote = 0;
	count = 0;
	while (cmds[++i] && i < 1)
	{
		j = -1;
		while (cmds[i][++j])
		{
			quote_status(cmds[i][j], &quote);
			if (!quote && cmds[i][j] == ' ')
				count++;
			while (cmds[i][j] == ' ' && cmds[i][j + 1] && cmds[i][j + 1] == ' ')
				j++;
		}
	}
	return (count);
}

char	*clean_cmd(char *cmd)
{
	char	*new;
	int		i;
	int		quote;

	if (!cmd)
		return (NULL);
	i = -1;
	quote = 0;
	new = calloc(1, sizeof(char));
	while (cmd[++i])
	{
		if ((quote == 0 && ft_strchr("\'\"", cmd[i])) \
		|| (quote == 1 && cmd[i] == '\'') \
		|| (quote == 2 && cmd[i] == '\"'))
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
	int		i;
	int		j;
	int		k;
	char	**new;
	char	**tmp;

	if (!cmds)
		return (NULL);
	new = malloc(sizeof(char *) * (dsize(cmds) + count(cmds) + 1));
	if (!new)
		return (cmds);
	new[dsize(cmds) + count(cmds)] = NULL;
	i = -1;
	j = 0;
	while (cmds[++i])
	{
		if (space(cmds[i]))
		{
			cmds[i] = clean_cmd(cmds[i]);
			tmp = ft_split(cmds[i], ' ');
			k = -1;
			while (tmp[++k])
			{
				new[i + j] = strdup(tmp[k]);
				j++;
			}
			dfree(tmp);
		}
		else
		{
			cmds[i] = clean_cmd(cmds[i]);
			new[i + j] = strdup(cmds[i]);
		}
	}
	dfree(cmds);
	return (new);
}
