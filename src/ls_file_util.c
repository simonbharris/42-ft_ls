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

t_list	*make_ls_lst(struct dirent de, char *parent)
{
	t_list		*lst;
	t_lsfile	*lsfile;
	char		fileloc[1024];
	struct stat	*st;

	ft_strcpy(fileloc, parent);
	ft_strcat(fileloc, "/");
	ft_strcat(fileloc, de.d_name);
	lsfile = (t_lsfile *)malloc(sizeof(t_lsfile));
	lsfile->stats = (struct stat *)malloc(sizeof(struct stat));
	lsfile->dirent = (struct dirent *)malloc(sizeof(struct dirent));
	*(lsfile->dirent) = de;
	if ((lstat(fileloc, lsfile->stats)) != 0)
	{
		free(lsfile->stats);
		free(lsfile->dirent);
		lst = NULL;
	}
	else
		lst = ft_lstnew(lsfile, sizeof(t_lsfile));
	free(lsfile);
	return (lst);
}

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
			free(LST_TO_LSFILE(pre)->stats);
			free(LST_TO_LSFILE(pre)->dirent);
			free(pre->content);
			free(pre);
			pre = tmp;
			if (pre)
				tmp = pre->next;
		}
		*head = NULL;
	}
}
