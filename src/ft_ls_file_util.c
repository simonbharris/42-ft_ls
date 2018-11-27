/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_file_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 18:41:40 by sharris           #+#    #+#             */
/*   Updated: 2018/11/25 18:41:40 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** creates the t_list to hold t_lsfiles and initializes them with the
** appropriate data
*/

t_list	*make_ls_lst(char *file, char *parent)
{
	t_list		*lst;
	t_lsfile	*lsfile;
	char		fileloc[1024];

	ft_strcpy(fileloc, parent);
	if (!ft_strequ(parent, ""))
		ft_strcat(fileloc, "/");
	ft_strcat(fileloc, file);
	lsfile = (t_lsfile *)malloc(sizeof(t_lsfile));
	lsfile->stats = (struct stat *)malloc(sizeof(struct stat));
	if ((lstat(fileloc, lsfile->stats)) != 0)
	{
		free(lsfile->stats);
		lst = NULL;
	}
	else
	{
		lsfile->name = ft_strdup(file);
		lst = ft_lstnew(lsfile, sizeof(t_lsfile));
	}
	free(lsfile);
	return (lst);
}

/*
** Frees the entire linked list passed into head, t_list assumes
** everything was created by the make_ls_lst constructor.
*/

void	free_ls_lst(t_list **head)
{
	t_list	*tmp;
	t_list	*pre;

	if (head && *head)
	{
		pre = *head;
		tmp = pre->next;
		while (pre)
		{
			ft_memdel((void **)&(LST_TO_LSFILE(pre)->stats));
			ft_memdel((void **)&(LST_TO_LSFILE(pre)->name));
			free(pre->content);
			free(pre);
			pre = tmp;
			if (pre)
				tmp = pre->next;
		}
		*head = NULL;
	}
}
