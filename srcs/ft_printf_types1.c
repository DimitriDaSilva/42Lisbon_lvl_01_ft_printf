/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/16 21:47:48 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/23 17:23:32 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_types.h"

/*
** Call different print function depending on the type
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
*/

void	print_types(t_format *settings)
{
	if ('c' == settings->type)
		print_char(settings);
	else if ('s' == settings->type)
		print_str(settings);
	else if ('p' == settings->type)
		print_ptr(settings);
	else if (ft_strchr("di", settings->type))
		print_int(settings);
	else if ('u' == settings->type)
		print_uint(settings);
	else if (ft_strchr("xX", settings->type))
		print_hex(settings);
	else if ('%' == settings->type)
		print_pct(settings);
	else if ('f' == settings->type)
		print_flt(settings);
	else if ('n' == settings->type)
		print_n(settings);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
*/

void	print_char(t_format *settings)
{
	char	*str_to_print;

	if (!(str_to_print = calloc(2, sizeof(char))))
		return ;
	str_to_print[0] = va_arg(g_arg_list, int);
	print_left_right(str_to_print, settings);
	free(str_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @3-4		Get argument from arg_list. If arg = NULL, print (null)
**			Edge case: Precision allow enough spacae to print (null)
** @6-7		Edge case: arg = NULL but precision doesn't allow enough space
** 			to print (null), so return emptyable string
** @8-9		Need to work with a duplicate because arg is const
** @11-13	Edge case: A precision has been set and it's lower than the size
**			of the string to print ==> cut str by adding a NULL at precision
*/

void	print_str(t_format *settings)
{
	char	*str_to_print;

	if (!(str_to_print = va_arg(g_arg_list, char *)) &&
		(settings->precision >= 6 || settings->precision <= -1))
		str_to_print = ft_strdup("(null)");
	else if ((!str_to_print && settings->precision < 6) || !*str_to_print)
		str_to_print = ft_strdup("");
	else
		str_to_print = ft_strdup(str_to_print);
	if (settings->precision != -1 &&
		settings->precision < (int)ft_strlen(str_to_print))
		str_to_print[settings->precision] = 0;
	print_left_right(str_to_print, settings);
	free(str_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @5-9		Edge case: for pointers, when value = 0, ignores all other flags
**			and print (nil)
*/

void	print_ptr(t_format *settings)
{
	long long	nb_to_convert;
	char		*nb_to_print;

	nb_to_convert = va_arg(g_arg_list, long long);
	if (nb_to_convert == 0)
	{
		g_count_printed_ch += ft_putstr("(nil)");
		return ;
	}
	else
		nb_to_print = ft_convert_base(nb_to_convert, "0123456789abcdef");
	if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	add_hex_prefix(&nb_to_print, settings->type, settings->flags);
	print_left_right(nb_to_print, settings);
	free(nb_to_print);
}

/*
** @param:	- [t_format] all 5 fields: flags, width, precision, size, type
** @return:	[int] number of printed characters
** Line-by-line comments:
** @9-13	Adding the padding of '0'. The 0s go before the signs and "0x"
*/

void	print_hex(t_format *settings)
{
	unsigned long long	nb_to_convert;
	char				*nb_to_print;

	nb_to_convert = va_arg(g_arg_list, unsigned long long int);
	if (settings->type == 'x')
		nb_to_print = ft_convert_base(nb_to_convert, "0123456789abcdef");
	else
		nb_to_print = ft_convert_base(nb_to_convert, "0123456789ABCDEF");
	if (ft_strchr(settings->flags, '#') && ft_strchr(settings->flags, '0') &&
		!is_all_zeros(nb_to_print))
		add_padding(&nb_to_print, settings->width - 2);
	else if (ft_strchr(settings->flags, '0'))
		add_padding(&nb_to_print, settings->width);
	add_padding(&nb_to_print, settings->precision);
	add_hex_prefix(&nb_to_print, settings->type, settings->flags);
	print_left_right(nb_to_print, settings);
	free(nb_to_print);
}
