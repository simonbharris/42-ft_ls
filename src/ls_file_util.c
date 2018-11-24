
#include <ft_ls.h>
#include <errno.h>


t_list *   make_ls_lst(struct dirent de, char *parent)
{
	t_list *lst;
	t_lsfile *lsfile;
	char fileloc[ft_strlen(parent) + ft_strlen(de.d_name) + 2];
	struct stat *st;

	ft_strcpy(fileloc, parent);
	ft_strcat(fileloc, "/");
	ft_strcat(fileloc, de.d_name);
	lsfile = (t_lsfile *)malloc(sizeof(t_lsfile));
	lsfile->stats = (struct stat *)malloc(sizeof(struct stat));
	lsfile->dirent = (struct dirent *)malloc(sizeof(struct dirent));
	*(lsfile->dirent) = de;
	if ((stat(fileloc, lsfile->stats)) != 0)
	{
		ft_printf("%s\n", fileloc);
		perror("ft_ls-lslst");
	}
	lst = ft_lstnew(lsfile, sizeof(t_lsfile));
	free(lsfile);
	return (lst);
}

void free_ls_lst(t_list **head)
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
			free (pre->content);
			free (pre);
			pre = tmp;
			if (pre)
				tmp = pre->next;
		}
		*head = NULL;
	}
}