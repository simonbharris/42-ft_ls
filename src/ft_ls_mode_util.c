/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_mode_util.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:23:56 by sharris           #+#    #+#             */
/*   Updated: 2018/11/26 18:24:01 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** returns the appropriate character for the type of file.
** Mode is from the struct stat
*/

char	get_file_type(mode_t mode)
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

/*
** Popultes an array to hold the various permissions of a file.
** This replicates the format of 'ls'
** Owner | Group | Others
** Example: "rwxr-x-r-x"
*/

void	get_userperms(char perms[10], mode_t mode)
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
