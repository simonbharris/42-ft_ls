
#include <ft_ls.h>

/*
** input opt should begin with a '-' character.
*/

int		get_opt_value(char c)
{
	const char	*cinputs = FT_LS_SUPPORTED_FLAGS;
	const int	cvals[6] = {FTLS_RR, FTLS_A, FTLS_L, FTLS_R, FTLS_T};

	return (cvals[ft_strchr(FT_LS_SUPPORTED_FLAGS, c) - cinputs]);
}

int		get_opt_flags(char *opt)
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

int		check_for_opt_flags(char **argv)
{
	int f;
	int i;

	i = 1;
	f = 0;
	while (argv[i] && argv[i][0] == '-' && argv[i][1])
	{
		f |= get_opt_flags(argv[i] + 1);
		i++;
		i++;
	}
	return (f);
}