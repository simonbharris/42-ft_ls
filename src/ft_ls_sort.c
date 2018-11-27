/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mrgsrt_ls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/20 10:49:49 by sharris           #+#    #+#             */
/*   Updated: 2018/11/20 10:49:57 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

/*
** Please note:
** t_list points to the contents of the t_list passed to it
** So here in the contents of ft_ls, we are being passed the t_lsfile.
**
** Lots of macro use here due to the amount of casting required.
** IE:
*/

static int	mrgsrt_ls_name(void *v1, void *v2)
{
	return (ft_strcmp((GET_LS_NAME(v1)), (GET_LS_NAME(v2))));
}

/*
** Sorts by time modified in seconds > time modified by nanoseconds > file name.
*/

static int	mrgsrt_ls_time(void *v1, void *v2)
{
	if (GET_LS_TMOD(v1).tv_sec == GET_LS_TMOD(v2).tv_sec)
	{
		if (GET_LS_TMOD(v1).tv_nsec == GET_LS_TMOD(v2).tv_nsec)
			return (ft_strcmp(GET_LS_NAME(v1), GET_LS_NAME(v2)));
		else
			return (GET_LS_TMOD(v1).tv_nsec < GET_LS_TMOD(v2).tv_nsec ? 1 : -1);
	}
	else
		return (GET_LS_TMOD(v1).tv_sec < GET_LS_TMOD(v2).tv_sec ? 1 : -1);
}

/*
** Delegates teh needed sort according to the global flags.
*/

t_list		*ft_ls_sort(t_list *head)
{
	if (g_ftls_flags & FTLS_T)
		return (ft_merge_sort(head, mrgsrt_ls_time, g_ftls_flags & FTLS_R));
	else
		return (ft_merge_sort(head, mrgsrt_ls_name, g_ftls_flags & FTLS_R));
}
