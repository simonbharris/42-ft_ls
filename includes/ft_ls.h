/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 00:16:37 by sharris           #+#    #+#             */
/*   Updated: 2018/11/12 00:16:37 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <time.h>
# include <dirent.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>
# include <sys/xattr.h>
# include <stdio.h>
# include <string.h>
# include <err.h>
# include <errno.h>
# include <sys/types.h>
# include <libft.h>
# include <ft_printf.h>

/*
** Since Norminette doesn't allow lower case letters in the define names,
** I am using double characters int he defines to define uppercase,
** single character means lower case.
**
** (Legend for what the option flags mean below.)
** -R -- Recursive
** -a -- include hidden files.
** -l -- disp[ay long-list format.
** -r -- reverse sort.
** -t -- sort by time
** Multifile-- More than 1 file passed as params.
*/

# define FTLS_RR		0x01
# define FTLS_A			0x02
# define FTLS_L			0x04
# define FTLS_R			0x08
# define FTLS_T			0x10
# define FTLS_MULTIFILE	0x20

# define FT_LS_SUPPORTED_FLAGS "Ralrt"

/*
** LST_TO_LSFILE is used to get the t_lstfile from a t_list.
** The GET_LS* macros have casted values since I often pass void* to them.
** (usually from a t_list.)
*/

# define LST_TO_LSFILE(val) ((t_lsfile *)(((t_list *)val)->content))
# define GET_LS_NAME(val) ((t_lsfile *)val)->name
# define GET_LS_TMOD(val) ((t_lsfile *)val)->stats->st_mtimespec

typedef struct	s_lsfile
{
	char			*name;
	struct stat		*stats;
}				t_lsfile;

/*
** Using a global for the flags,
** otherwise I need to pass them to nearly every function.
*/

int				g_ftls_flags;

/*
** All functions have their own file, with the exception of ls_file_util.c
** Of course, within these files will likely have other statics.
*/

void			ft_ls(char **argv);
t_list			*ft_ls_sort(t_list *head);
void			print_ls(t_list *files, char *parent);
void			set_opt_flags(char **argv);
void			skip_hidden_files(t_list **files);
void			print_basic_long_list(t_lsfile *file);
void			ftls_put_longlist(t_lsfile *file, char *parent);
void			ftls_print_file(t_list *filel, char *parent);
void			ftls_put_dir(char *file);

/*
** ls_file_util.c holds functions to both create
** and destroy the ls_file linked list.
*/

t_list			*make_ls_lst(char *file, char *parent);
void			free_ls_lst(t_list **head);

char			get_file_type(mode_t mode);
void			get_userperms(char perms[10], mode_t mode);

#endif
