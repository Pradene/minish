/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 16:03:13 by tmalless          #+#    #+#             */
/*   Updated: 2023/06/28 16:32:35 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
			while (cmds[i][j] == ' ' && cmds[i][j + 1] \
			&& cmds[i][j + 1] == ' ')
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
	new = ft_calloc(1, sizeof(char));
	while (cmd[++i])
	{
		if ((quote == 0 && ft_strchr("\'\"", cmd[i])) \
		|| (quote == 1 && cmd[i] == '\'') \
		|| (quote == 2 && cmd[i] == '\"'))
			quote_status(cmd[i], &quote);
		else
		{
			new = ft_addchar(new, cmd[i]);
			if (!new)
				return (cmd);
		}
	}
	free(cmd);
	return (new);
}

void	addtocmd(char **new, char **cmds, int *i, int *j)
{
	char	**tmp;
	int		k;

	cmds[*i] = clean_cmd(cmds[*i]);
	tmp = ft_split(cmds[*i], ' ');
	if (!tmp)
		return ;
	k = -1;
	while (tmp[++k])
	{
		new[*i + *j] = ft_strdup(tmp[k]);
		*j += 1;
	}
	dfree(tmp);
}

char	**clean_cmds(char **cmds)
{
	int		i;
	int		j;
	char	**new;

	if (!cmds)
		return (NULL);
	new = malloc(sizeof(char *) * (dsize(cmds) + count(cmds) + 1));
	if (!new)
		return (cmds);
	new[dsize(cmds) + count(cmds)] = NULL;
	i = -1;
	j = 0;
	while (cmds && cmds[++i])
	{
		if (space(cmds[i]))
			addtocmd(new, cmds, &i, &j);
		else
		{
			cmds[i] = clean_cmd(cmds[i]);
			new[i + j] = ft_strdup(cmds[i]);
		}
	}
	dfree(cmds);
	return (new);
}
