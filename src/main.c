/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 03:46:54 by sharris           #+#    #+#             */
/*   Updated: 2018/11/12 03:46:55 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** if there are no arguments, running ft_ls with NULL
** will use the current directory.
** Otherwise, captures flags then passes ft_ls the remaining arguments.
*/

int		main(int ac, char **av)
{
	int i;

	i = 1;
	g_ftls_flags = 0;
	if (ac == 1)
		ft_ls(NULL);
	else if (ac > 1)
	{
		set_opt_flags(av);
		while (av[i] && av[i][0] == '-')
			i++;
		if (av[i] && av[i + 1])
			g_ftls_flags |= FTLS_MULTIFILE;
		ft_ls(&av[i]);
	}
	return (0);
}
