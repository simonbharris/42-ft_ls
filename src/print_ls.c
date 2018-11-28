/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 18:41:23 by sharris           #+#    #+#             */
/*   Updated: 2018/11/27 16:17:37 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** Gets the block size for the linked listed files pointed ot by files.
*/

static int	get_block_size(t_list *files)
{
	int ct;

	ct = 0;
	while (files)
	{
		if (!(g_ftls_flags & FTLS_A)
			&& ft_strncmp(GET_LS_NAME(files->content), ".", 1) == 0)
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

int has_visible_files(t_list *files)
{
	if (files && !(g_ftls_flags & FTLS_A))
			skip_hidden_files(&files);
	if (files)
		return (1);
	return (0);
}

/*
** Handles the iteration through the files linked list to print
** it's contents to the screen. Here it also checks the global flags
** to see how it prints the files, and whether to print hidden files.
*/

void		print_ls(t_list *files, char *parent)
{
	if (has_visible_files(files))
		ft_printf("total %d\n", get_block_size(files));
	while (files)
	{
		if (!(g_ftls_flags & FTLS_A)
			&& ft_strncmp(GET_LS_NAME(files->content), ".", 1) == 0)
		{
			skip_hidden_files(&files);
			continue ;
		}
		else if (g_ftls_flags & FTLS_L)
			ftls_put_longlist(files->content, parent);
		else
			printf("%s\n", GET_LS_NAME(files->content));
		files = files->next;
	}
}
