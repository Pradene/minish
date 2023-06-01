/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmalless <tmalless@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 22:09:53 by lpradene          #+#    #+#             */
/*   Updated: 2023/05/23 15:23:57 by tmalless         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	g_exit = 0;

t_data	*singleton(t_data *data)
{
	static t_data	*d;

	if (!data)
		return (d);
	d = data;
	return (d);
}

int	main(int ac, char **av, char **envp)
{
	t_data	data;

	(void)av;
	if (ac > 1)
		exit(EXIT_FAILURE);
	data.env = envcp(envp);
	data.root = NULL;
	data.tmp = NULL;
	data.tokens = NULL;
	data.exec = 0;
	data.fd0 = -1;
	data.fd1 = -1;
	set_attribute();
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
	singleton(&data);
	while (1)
		get_cmd(&data);
	return (0);
}
