/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards_motif.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 21:04:10 by tmalless          #+#    #+#             */
/*   Updated: 2023/06/30 21:20:37 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*del_quotes(char *mot, int i, int j, int c)
{
	char	*new_mot;

	if (!mot)
		return (0);
	while (mot[++i])
	{
		if (is_quote(mot[i]))
			c++;
	}
	new_mot = ft_calloc(ft_strlen(mot) - c + 1, sizeof(char *));
	i = 0;
	while (mot[i])
	{
		if (is_quote(mot[i]))
			i++;
		else
		{
			new_mot[j] = mot[i];
			j++;
			i++;
		}
	}
	free(mot);
	return (new_mot);
}

int	is_quote(char c)
{
	if (ft_strchr("\'\"", c))
		return (1);
	return (0);
}

char	**clean_motif(char **motif, int i)
{
	while (motif && motif[i])
	{
		motif[i] = del_quotes(motif[i], -1, 0, 0);
		i++;
	}
	return (motif);
}

char	**fill_motif(char *cmd, char **motif, int m_count)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (cmd[i] == '*')
		i++;
	while (k < m_count)
	{
		j = i;
		while (cmd[i] && cmd[i] != '*')
			i++;
		motif[k] = ft_substr(cmd, j, i - j);
		k++;
		while (cmd[i] == '*')
			i++;
	}
	return (clean_motif(motif, 0));
}

char	**create_motif(char *cmd, char **motif)
{
	int	i;
	int	m_count;

	i = 0;
	m_count = 0;
	while (cmd[i])
	{
		while (cmd[i] == '*')
			i++;
		if (cmd[i] && !ft_strchr(" ", cmd[i]))
			m_count++;
		else
			break ;
		while (cmd[i] && cmd[i] != '*')
			i++;
	}
	motif = ft_calloc(sizeof(char *), m_count + 1);
	return (fill_motif(cmd, motif, m_count));
}
