/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpradene <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 19:41:58 by lpradene          #+#    #+#             */
/*   Updated: 2023/03/18 19:42:06 by lpradene         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	builtin(char ***env, char *s)
{
	if (ft_strncmp(s, "cd", 3) == 0)
		cd(*env, "./srcs");
	else if (ft_strncmp(s, "echo", 5) == 0)
		echo("echo\n", 0);
	else if (ft_strncmp(s, "env", 4) == 0)
		print_env(*env);
	else if (ft_strncmp(s, "exit", 5) == 0)
		ex();
	else if (ft_strncmp(s, "export", 7) == 0)
		*env = export(*env, "COOL=COOL");
	else if (ft_strncmp(s, "unset", 6) == 0)
		*env = unset(*env, "COOLe");
	return ;
}
