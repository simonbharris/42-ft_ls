/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_hidden_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 12:43:25 by sharris           #+#    #+#             */
/*   Updated: 2018/11/23 12:43:29 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** Simply skips a t_list pointer forward to skip over all the hidden files.
** The linked list must be sorted.
*/

void	skip_hidden_files(t_list **files)
{
	t_list *tmp;

	tmp = *files;
	while (tmp && ft_strncmp(GET_LS_NAME(tmp->content), ".", 1) == 0)
		tmp = tmp->next;
	*files = tmp;
}
