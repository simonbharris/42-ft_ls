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

static char	get_file_type(int mode)
{
	if (S_ISBLK(mode))
		return ('b');
	else if (S_ISCHR(mode))
		return ('c');
	else if (S_ISDIR(mode))
		return ('d');
	else if (S_ISLNK(mode))
		return ('l');
	else if (S_ISSOCK(mode))
		return ('s');
	else if (S_ISFIFO(mode))
		return ('p');
	else if (S_ISREG(mode))
		return ('-');
	else
		return ('?');
}

static void	get_userperms(char perms[10], int mode)
{
	ft_bzero(perms, 10);
	perms[0] = (char)((mode & S_IRUSR) ? 'r' : '-');
	perms[1] = (char)((mode & S_IWUSR) ? 'w' : '-');
	perms[2] = (char)((mode & S_IXUSR) ? 'x' : '-');
	perms[3] = (char)((mode & S_IRGRP) ? 'r' : '-');
	perms[4] = (char)((mode & S_IWGRP) ? 'w' : '-');
	perms[5] = (char)((mode & S_IXGRP) ? 'x' : '-');
	perms[6] = (char)((mode & S_IROTH) ? 'r' : '-');
	perms[7] = (char)((mode & S_IWOTH) ? 'w' : '-');
	perms[8] = (char)((mode & S_IXOTH) ? 'x' : '-');
	perms[9] = 0;
}

static void	putnormallist(t_lsfile *file)
{
	char	time1[26];
	char	time2[8];
	time_t	timev;
	char	perms[10];

	time(&timev);
	ft_bzero(time2, 8);
	ft_strcpy(time1, ctime(&(file->stats->st_mtimespec.tv_sec)));
	if (timev - 60 * 60 * 24 * 180 > file->stats->st_mtimespec.tv_sec)
		ft_strncpy(time2, time1 + 20, 4);
	else
		ft_strncpy(time2, time1 + 11, 5);
	ft_strncpy(time1, time1 + 4, 7);
	time1[6] = 0;
	get_userperms(perms, file->stats->st_mode);
	ft_printf("%c%s  %5d %12s %12s %10d %s %5s %s", \
		get_file_type(file->stats->st_mode), \
		perms, file->stats->st_nlink, getpwuid(file->stats->st_uid)->pw_name, \
		getgrgid(file->stats->st_gid)->gr_name, file->stats->st_size,\
		time1, time2, file->dirent->d_name);
}

static void	printlinklocation(t_lsfile *file, char *parent)
{
	char buf[1024];
	char fileloc[2050];

	ft_bzero(buf, 1024);
	ft_strcpy(fileloc, parent);
	if (!ft_strequ(parent, "/"))
		ft_strcat(fileloc, "/");
	ft_strcat(fileloc, file->dirent->d_name);
	readlink(fileloc, buf, 1024);
	ft_printf(" -> %s", buf);
}

void		ftls_put_longlist(t_lsfile *file, char *parent)
{
	putnormallist(file);
	if (S_ISLNK(file->stats->st_mode))
		printlinklocation(file, parent);
	ft_printf("\n");
}
