/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 18:41:59 by sharris           #+#    #+#             */
/*   Updated: 2018/11/25 18:42:00 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** Creates a linked list out of all files called explicitly
** as arguments for ft_ls
*/

static t_list	*get_explicit_files(char **av)
{
	int		i;
	t_list	*head;
	t_list	*hold;

	head = NULL;
	i = 0;
	while (av[i])
	{
		if ((hold = make_ls_lst(av[i++], "")))
			ft_lstadd(&head, hold);
		else
			perror("ft_ls");
	}
	return (head);
}

/*
** Prints all non-directories  that were explicitly called in arguments to ft_ls
** Skips over directories.
*/

static void		ftls_print_explicit_files(t_list *filelist)
{
	while (filelist)
	{
		if (!S_ISDIR(LST_TO_LSFILE(filelist)->stats->st_mode))
		{
			ftls_print_file(filelist, "");
			filelist = filelist->next;
		}
		else
			filelist = filelist->next;
	}
}

/*
** Prints all directories that were explicitly called by ft_ls
*/

static void		ftls_print_dirlist(t_list *argl)
{
	int first;

	first = 1;
	while (argl)
	{
		if (S_ISDIR(LST_TO_LSFILE(argl)->stats->st_mode))
		{
			if (first != 1 || (first = 0))
				ft_printf("\n");
			ftls_put_dir(LST_TO_LSFILE(argl)->name);
		}
		argl = argl->next;
	}
}

/*
** First captures and prints and explicit file called.
*/

void			ft_ls(char **argv)
{
	int		i;
	t_list	*argl;

	i = 0;
	if (!argv || !*argv)
		ftls_put_dir(".");
	else
	{
		argl = get_explicit_files(&(argv[i]));
		argl = ft_ls_sort(argl);
		ftls_print_explicit_files(argl);
		ftls_print_dirlist(argl);
		free_ls_lst(&argl);
	}
}
