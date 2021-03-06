/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sharris <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/22 15:23:55 by sharris           #+#    #+#             */
/*   Updated: 2018/10/22 15:24:09 by sharris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long long	ft_pow(long long nbr, int p)
{
	int out;

	out = 1;
	if (p == 0)
		return (1);
	while (p-- > 0)
		out *= nbr;
	return (out);
}
