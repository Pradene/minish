/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 15:41:55 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/28 15:41:27 by tmalless         ###   ########.fr       */
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
		if (!ft_isalnum(arg[i]) && arg[i] != '_')
			return (1);
	if (!arg[i])
		return (0);
	return (0);
}
