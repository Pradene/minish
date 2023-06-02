/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:31:21 by lpradene          #+#    #+#             */
/*   Updated: 2023/06/02 16:31:22 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_export(char **env)
{
	int	i;
	int	j;

	i = -1;
	while (env[++i])
	{
		j = -1;
		printf("declare -x ");
		while (env[i][++j] && env[i][j] != '=')
			printf("%c", env[i][j]);
		if (!env[i][j])
		{
			printf("\n");
			continue ;
		}
		printf("=\"");
		while (env[i][++j])
			printf("%c", env[i][j]);
		printf("\"\n");
	}
}
