/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wlin <wlin@student.42barcelona.>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 16:27:42 by wlin              #+#    #+#             */
/*   Updated: 2023/10/07 22:22:21 by wlin             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

int	ft_put_digit(long long n);
int	ft_put_recursive(long long n);
int	ft_put_recursive_hexa(unsigned long n, char *hexa_base);
int	ft_put_hexa(unsigned long n, char mode);
int	ft_printf(const	char *str, ...);
int	put_str(char *s);
int	put_char(char c);

#endif
