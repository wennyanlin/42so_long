/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_s.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 12:41:55 by wlin              #+#    #+#             */
/*   Updated: 2023/10/08 19:56:27 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	put_str(char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		if (write(1, "(null)", 6) == -1)
			return (-1);
		return (6);
	}
	while (s[i] != '\0')
	{
		if (write(1, &s[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	put_char(char c)
{
	if (write(1, &c, 1) == -1)
		return (-1);
	return (1);
}
