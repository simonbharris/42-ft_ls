/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_put_longlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 16:37:55 by sharris           #+#    #+#             */
/*   Updated: 2018/11/25 16:37:56 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** Long-list format:
** Filetype     [bcdlsp-]
** Permissions -- Owner, Group, Others
**		Read:   [r-]
**		Write:	[w-]
**		Execute:[Ssx-] -- (Third character in last group also: [Tt]
** Number of Links (Assuming hard links)
** Owner Name
** Owner Group
** File size (Seems to be in bytes)
** Time of last modification (time since last mod > 6 months,
** displays year instead of hour/minutes)
** File name
*/

/*
** Apprends the location of the symbolic link to the end of the long-list print.
*/

static void	print_link_location(t_lsfile *file, char *parent)
{
	char buf[1024];
	char fileloc[2050];

	ft_bzero(buf, 1024);
	ft_strcpy(fileloc, parent);
	if (!ft_strequ(parent, "/") && !ft_strequ(parent, ""))
		ft_strcat(fileloc, "/");
	ft_strcat(fileloc, file->name);
	readlink(fileloc, buf, 1024);
	ft_printf(" -> %s", buf);
}

/*
** Delegates the structure of the long-list print.
*/

void		ftls_put_longlist(t_lsfile *file, char *parent)
{
	print_basic_long_list(file);
	if (S_ISLNK(file->stats->st_mode))
		print_link_location(file, parent);
	ft_printf("\n");
}

/*
** Prints either long-list format, or simply the file name,
** according to the set options.
*/

void		ftls_print_file(t_list *filel, char *parent)
{
	if (g_ftls_flags & FTLS_L)
		ftls_put_longlist(filel->content, parent);
	else
		printf("%s\n", LST_TO_LSFILE(filel)->name);
}
