
#include <ft_ls.h>

void putftls(char *file, int flags)
{
	DIR *dirs;
	struct dirent *dent;
	t_list *fnames;
	t_list dirnames;

	fnames = NULL;
	dirs = opendir(file);
	if (flags & FTLS_MULTIFILE)
		ft_printf("%s:\n", file);
	while ((dent = readdir(dirs)))
		ft_lstadd(&fnames, ft_lstnew(dent->d_name, ft_strlen(dent->d_name)));
	fnames = ft_merge_sort(fnames, merge_strcmp_f);
	putftls(fnames, flags);
	if (flags & FTLS_RR)
		dirnames =
}

void ft_ls(char **argv, int flags)
{
	t_list ldirs;
	int i;

	i = 0;
	if (argv == NULL)
	{
		putftls("./", flags);
	}
	else
	{
		while (argv[i] && argv[i][0] == '-')
			i++;

	}
}