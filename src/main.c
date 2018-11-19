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
#include <ft_printf.h>



/*
** Displays usage, then exits.
*/
void ftls_put_usage(void)
{
	ft_putendl("usage: ls [-" FT_LS_SUPPORTED_FLAGS "] [file ...] ");
	exit(1);
}

int main(int ac, char **av)
{

	int flags;
	int i;

	i = 0;
	fnames = NULL;
	if(ac == 1)
	{
		ft_ls(NULL, 0);
	}
	else if (ac > 1)
	{
		flags = check_for_opt_flags(av);
		while (av[i] && av[i][0] == '-')
			i++;
		if (av[i] && av[i + 1])
			flags |= FTLS_MULTIFILE;
		ft_ls(av[i], flags);
		// check what arguments are
		// if flags (pesence of '-' before anything else)
		// if illegal flag, display usage
		// then gather flag contents.
		// branch depending on flags.
	}
	return (0);
}
