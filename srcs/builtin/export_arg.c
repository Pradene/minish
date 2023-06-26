/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:41:55 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/14 15:41:56 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	export_arg(char *arg)
{
	int	i;

	if (arg[0] == '=')
		return (1);
	i = -1;
	while (arg[++i] && arg[i] != '=')
		if (!ft_isalpha(arg[i]))
			return (1);
	if (!arg[i])
		return (0);
	return (0);
}
