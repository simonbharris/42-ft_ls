/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_basic_long_list.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:24:21 by sharris           #+#    #+#             */
/*   Updated: 2018/11/27 16:51:12 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** Populates teh time1 and time2 values with date
** modified indicated by a file's stat
** time1 ends up holding day/month,
** time2 holds an hour:minute or year, based off how old the file is.
*/

static void	ftls_populate_time_values(struct stat st,
										char time1[26], char time2[8])
{
	time_t	timev;

	time(&timev);
	ft_bzero(time2, 8);
	ft_strcpy(time1, ctime(&(st.st_mtimespec.tv_sec)));
	if (timev - 15726000 > st.st_mtimespec.tv_sec)
		ft_strncpy(time2, time1 + 20, 4);
	else
		ft_strncpy(time2, time1 + 11, 5);
	ft_strncpy(time1, time1 + 4, 7);
	time1[6] = 0;
}

/*
** Prints the first part of the long-list,
** file type, permissions, owner name, and group name.
*/

static void	ftls_print_type_perm_owner_group(struct stat st, char perms[10])
{
	ft_printf("%c%s  %5d %12s %12s ", \
		get_file_type(st.st_mode), \
		perms,\
		st.st_nlink, \
		getpwuid(st.st_uid)->pw_name, \
		getgrgid(st.st_gid)->gr_name);
}

/*
** Prints file size,
** if file is a block special or a character special file,
** It instead prints the major and minor device numbers.
*/

static void	ftls_print_file_size(struct stat *st)
{
	if (S_ISBLK(st->st_mode) || S_ISCHR(st->st_mode))
		ft_printf("%4lld, %4lld ", major(st->st_rdev),
				minor(st->st_rdev));
	else
		ft_printf("%10d ", st->st_size);
}

/*
** Simply prints time, followed by file name.
*/

static void	ftls_print_time_filename(const char *mo_day,
									const char *time_year, char *name)
{
	ft_printf("%s %s %s", mo_day, time_year, name);
}

/*
** Prints the long-list format for ftls.
** Example:
** -xwr--r--r sharris may_2018 4242 May 2018 test.txt
**
** due to the complexity of the calls, organization, and conditions,
** they have been broken up for better readability.
*/

void		print_basic_long_list(t_lsfile *file)
{
	char	mo_day[26];
	char	time_year[8];
	char	perms[10];

	ftls_populate_time_values(*file->stats, mo_day, time_year);
	get_userperms(perms, file->stats->st_mode);
	ftls_print_type_perm_owner_group(*file->stats, perms);
	ftls_print_file_size(file->stats);
	ftls_print_time_filename(mo_day, time_year, file->name);
}
