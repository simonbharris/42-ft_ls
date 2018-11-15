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

static void outusage(void)
{
	ft_putendl("usage: ls [-lRart] ");
}

int main(int ac, char **av)
{
	DIR *dirs;
	struct dirent *dent;

	if(ac == 1)
	{
		dirs = opendir("./");
		dent = readdir(dirs);		
		ft_printf("%s\n", dent->d_name);
	}
	else if (ac > 1)
	{
		dirs = opendir(av[1]);
		readdir(dirs);
		// check what arguments are
		// if flags (pesence of '-' before anything else)
		// if illegal flag, display usage
		// then gather flag contents.
		// branch depending on flags.
	}
	return (0);
}
