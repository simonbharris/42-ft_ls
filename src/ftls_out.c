#include <ft_ls.h>
#include <stdio.h>
# define LS_A_FLAG 0x01

static void skip_hidden(t_list **files)
{
	t_list *tmp;

	tmp = *files;
	while (tmp && ft_strncmp(tmp->content, ".", 1) == 0)
			tmp = tmp->next;
	*files = tmp;
}

void put_files(t_list *files, int ls_flags)
{
	t_list *tmp;
	int i = 0;

	tmp = files;
	if (!(ls_flags & LS_A_FLAG))
		skip_hidden(&tmp);
	while (tmp)
	{
		printf("%s\n", (char *)tmp->content);
		tmp = tmp->next;
	}
}