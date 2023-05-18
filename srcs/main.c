/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:09:53 by lpradene          #+#    #+#             */
/*   Updated: 2023/04/04 17:10:27 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit = 0;

/*
-faire les heredocs dans un fork sinon signaux compliquer
-parsing du echo
-expand segfault quand ya rien
-^C status != 130
- ">a" gerer ca etpas segfault
-exit|exit (ne pas exit)
*/

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		exit(EXIT_FAILURE);
	data.env = envcp(envp);
	data.root = NULL;
	set_attribute();
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sig_handler);
	while (1)
		get_cmd(&data);
	return (0);
}
