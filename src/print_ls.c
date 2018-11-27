/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ls.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 18:41:23 by sharris           #+#    #+#             */
/*   Updated: 2018/11/25 18:41:24 by sharris          ###   ########.fr       */
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

/*
** Handles the iteration through the files linked list to print
** it's contents to the screen. Here it also checks the global flags
** to see how it prints the files, and whether to print hidden files.
*/

void		print_ls(t_list *files, char *parent, int ls_flags)
{
	t_list *tmp;

	if (g_ftls_flags & FTLS_L)
		ft_printf("total %d\n", get_block_size(files));
	tmp = files;
	while (tmp)
	{
		if (!(ls_flags & FTLS_A)
			&& ft_strncmp(GET_LS_NAME(tmp->content), ".", 1) == 0)
		{
			skip_hidden_files(&tmp);
			continue ;
		}
		else if (g_ftls_flags & FTLS_L)
			ftls_put_longlist(tmp->content, parent);
		else
			printf("%s\n", GET_LS_NAME(tmp->content));
		tmp = tmp->next;
	}
}
