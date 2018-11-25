#include <ft_ls.h>
#include <stdio.h>

/*
** Long-list format:
** Filetype     [bcdlsp-]
** Permissions -- Owner, Group, Others
**		Read:   [r-]
**		Write:	[w-]
**		Execute:[Ssx-] -- (Third character in last group also: [Tt]
** Number of Links (Assuming hard links)
** Owner Name
** Owner Group
** File size (Seems to be in bytes)
** Time of last modification (time since last mod > 6 months, displays year instead of hour/minutes)
** File name
*/

static char get_file_type(int mode)
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

static void get_userperms(char perms[10], int mode)
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

// TODO: Need to print symbollic links differently, show file size of the file
// TODO: (the symlink directly) not the size of the target.
// TODO: Need to research how to acquire the path of the symlink target as well,
// TODO: may need ot break this function down into a couple functions.
void	ft_lsprintlonglist(t_lsfile *file)
{
	int mode;
	char time1[26];
	char time2[8];
	time_t timev;
	char perms[10];

	time(&timev);
	ft_bzero(time2, 8);
	ft_strcpy(time1, ctime(&(file->stats->st_mtimespec.tv_sec)));
	//ft_printf("%s\n", time1);
	if (timev - 60 * 60 * 24 * 180 > file->stats->st_mtimespec.tv_sec)
		ft_strncpy(time2, time1 + 20, 4);
	else
		ft_strncpy(time2, time1 + 11, 5);
	ft_strncpy(time1, time1 + 4, 7);
	time1[6] = 0;
	mode = file->stats->st_mode;
	get_userperms(perms, mode);
	ft_printf("%c%s  %2d %12s %12s %10d %s %5s %s", \
			get_file_type(mode), perms, \
			file->stats->st_nlink, getpwuid(file->stats->st_uid)->pw_name,\
			getgrgid(file->stats->st_gid)->gr_name,\
			file->stats->st_size, time1, time2, file->dirent->d_name);\
	//if (S_ISLNK(mode))
	//	ft_printf(" -> %s", file->stats->st_nlink)
	ft_printf("\n");
}

int get_block_size(t_list *files)
{
	int ct;

	ct = 0;
	while (files)
	{
		if (!(g_ftls_flags & FTLS_A)
			&& ft_strncmp(GET_LS_DNAME(files->content), ".", 1) == 0)
		{
			skip_hidden_files(&files);
			continue ;
		}
		else
		{
			ct += (LST_TO_LSFILE(files)->stats->st_blocks);
			files = files->next;
		}
	}
	return (ct);
}

void print_ls(t_list *files, int ls_flags)
{
	t_list *tmp;

	if (g_ftls_flags & FTLS_L)
		ft_printf("total %d\n", get_block_size(files));
	tmp = files;
	while (tmp)
	{
		if (!(ls_flags & FTLS_A)
			&& ft_strncmp(GET_LS_DNAME(tmp->content), ".", 1) == 0)
		{
			skip_hidden_files(&tmp);
			continue ;
		}
		else if (g_ftls_flags & FTLS_L)
			ft_lsprintlonglist(tmp->content);
		else
			printf("%s\n", ((t_lsfile *)tmp->content)->dirent->d_name);
		tmp = tmp->next;
	}
}