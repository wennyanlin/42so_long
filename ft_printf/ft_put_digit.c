/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_i.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 13:30:30 by wlin              #+#    #+#             */
/*   Updated: 2023/10/08 17:05:40 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_recursive(long long n)
{
	char	digit;
	int		i;
	int		ret;

	i = 0;
	if (n > 9)
	{
		ret = ft_put_recursive(n / 10);
		if (ret == -1)
			return (-1);
		i += ret + 1;
		digit = n % 10 + '0';
		if (write(1, &digit, 1) == -1)
			return (-1);
	}
	else
	{
		digit = n + '0';
		if (write(1, &digit, 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_put_digit(long long n)
{
	int		i;
	int		k;
	int		len;

	i = 0;
	k = 0;
	if (n == -2147483648)
	{
		if (write(1, "-2147483648", 11) == -1)
			return (-1);
		return (11);
	}
	else if (n < 0)
	{
		if (write(1, "-", 1) == -1)
			return (-1);
		n = -n;
		k = 1;
	}
	len = ft_put_recursive(n);
	if (len == -1)
		return (-1);
	i = len + k;
	return (i);
}

int	ft_put_recursive_hexa(unsigned long n, char *hexa_base)
{
	int		digit;
	int		i;
	int		ret;

	i = 0;
	if (n > 15)
	{
		digit = n % 16;
		ret = ft_put_recursive_hexa(n / 16, hexa_base);
		if (ret == -1)
			return (-1);
		i += ret + 1;
		if (write(1, &hexa_base[digit], 1) == -1)
			return (-1);
	}
	else
	{
		digit = n % 16;
		if (write(1, &hexa_base[digit], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	ft_put_hexa(unsigned long n, char mode)
{
	int	len;

	len = 0;
	if (mode == 'x')
		len = ft_put_recursive_hexa(n, "0123456789abcdef");
	else if (mode == 'X')
		len = ft_put_recursive_hexa(n, "0123456789ABCDEF");
	else if (mode == 'p')
	{
		if (write(1, "0x", 2) == -1)
			return (-1);
		len = ft_put_recursive_hexa(n, "0123456789abcdef");
		if (len == -1)
			return (-1);
		len += 2;
	}
	if (len == -1)
		return (-1);
	return (len);
}
/*
int	main()
{
	int	n = -1;
	int result = ft_put_hexa(n, 'p');
	int org_result = printf("%d", result);
	printf("\n%i|%i", result, org_result);
	return (0);
}*/
