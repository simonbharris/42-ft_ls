/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftls_put_dirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:36:24 by sharris           #+#    #+#             */
/*   Updated: 2018/11/27 17:10:23 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** Prepends the parent (path) to the fileneame and stores teh result in buf.
*/

static void		buildfileloc(char buf[2048], char *parent, char *filename)
{
	if (ft_strlen(parent) + ft_strlen(filename) + 2 > 2048)
		ft_strcpy(buf, "ft_ls: Error, filename is too long.");
	else
	{
		ft_strcpy(buf, parent);
		if (!ft_strequ(parent, "/"))
			ft_strcat(buf, "/");
		ft_strcat(buf, filename);
	}
}

/*
** Part of the recursive function to print the contents of subdirectories.
** Ensures to exclude the relative self and parent directories.
** Does not follow links.
*/

static void		put_subdirs(t_list *namelst, char *parent)
{
	char fileloc[2048];

	while (namelst)
	{
		if (!(g_ftls_flags & FTLS_A) &&
				!ft_strncmp(GET_LS_NAME(namelst->content), ".", 1))
			skip_hidden_files(&namelst);
		else
		{
			buildfileloc(fileloc, parent, GET_LS_NAME(namelst->content));
			lstat(fileloc, LST_TO_LSFILE(namelst)->stats);
			if (!(ft_strcmp(GET_LS_NAME(namelst->content), ".") == 0
				|| ft_strcmp(GET_LS_NAME(namelst->content), "..") == 0)
				&& ((S_ISDIR(LST_TO_LSFILE(namelst)->stats->st_mode))
				&& !S_ISLNK(LST_TO_LSFILE(namelst)->stats->st_mode)))
			{
				ft_printf("\n%s:\n", fileloc);
				ftls_put_dir(fileloc);
			}
			namelst = namelst->next;
		}
	}
}

/*
** collects the files contained withing the directory, 'file'
** Sorts then passed the files to another function to print to the screen.
*/

void			ftls_put_dir(char *file)
{
	DIR				*dirs;
	struct dirent	*dent;
	t_list			*dirnames;
	t_list			*hold;

	dirnames = NULL;
	if (g_ftls_flags & FTLS_MULTIFILE)
		ft_printf("%s:\n", file);
	if (!(dirs = opendir(file)))
		perror("ft_ls");
	else
	{
		while ((dent = readdir(dirs)))
			if ((hold = make_ls_lst(dent->d_name, file)))
				ft_lstadd(&dirnames, hold);
		dirnames = ft_ls_sort(dirnames);
		print_ls(dirnames, file);
		if (g_ftls_flags & FTLS_RR)
			put_subdirs(dirnames, file);
		closedir(dirs);
		free_ls_lst(&dirnames);
		free(dent);
	}
}
