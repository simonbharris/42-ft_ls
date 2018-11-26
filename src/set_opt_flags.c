/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_opt_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 18:41:09 by sharris           #+#    #+#             */
/*   Updated: 2018/11/25 18:41:10 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** input opt should begin with a '-' character.
*/

static void		ftls_put_usage(void)
{
	ft_putendl("usage: ls [-" FT_LS_SUPPORTED_FLAGS "] [file ...] ");
	exit(1);
}

static int		get_opt_value(char c)
{
	const char	*cinputs = FT_LS_SUPPORTED_FLAGS;
	const int	cvals[6] = {FTLS_RR, FTLS_A, FTLS_L, FTLS_R, FTLS_T};

	return (cvals[ft_strchr(FT_LS_SUPPORTED_FLAGS, c) - cinputs]);
}

static int		get_opt_flags(char *opt)
{
	int f;
	int i;

	i = 0;
	f = 0;
	while (opt[i])
	{
		if (ft_strchr(FT_LS_SUPPORTED_FLAGS, opt[i]))
			f |= get_opt_value(opt[i]);
		else
		{
			ft_printf("ls: illegal option -- %c\n", opt[i]);
			ftls_put_usage();
		}
		i++;
	}
	return (f);
}

void			set_opt_flags(char **argv)
{
	int f;
	int i;

	i = 1;
	f = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1])
	{
		g_ftls_flags |= get_opt_flags(argv[i] + 1);
		i++;
		i++;
	}
}
