/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 20:08:10 by tmalless          #+#    #+#             */
/*   Updated: 2023/06/30 21:25:00 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	handle_star(char *cmd)
{
	if (cmd && cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] != '*')
		return (0);
	else if (cmd && cmd[0] == '*' && cmd[ft_strlen(cmd) - 1] != '*')
		return (1);
	else if (cmd && cmd[0] != '*' && cmd[ft_strlen(cmd) - 1] == '*')
		return (2);
	else
		return (3);
}

int	wc_in_quotes(char *s)
{
	int	i;
	int	quotes;

	quotes = 0;
	i = -1;
	while (s && s[++i])
	{
		quote_status(s[i], &quotes);
		if (!quotes && s[i] == '*')
			return (1);
	}
	return (0);
}
