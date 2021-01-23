/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_types.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dda-silv <dda-silv@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 17:17:14 by dda-silv          #+#    #+#             */
/*   Updated: 2021/01/23 17:17:15 by dda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_TYPES_H
# define FT_PRINTF_TYPES_H

# include "ft_printf.h"

void	print_types(t_format *settings);
void	print_char(t_format *settings);
void	print_str(t_format *settings);
void	print_ptr(t_format *settings);
void	print_int(t_format *settings);
void	print_uint(t_format *settings);
void	print_hex(t_format *settings);
void	print_pct(t_format *settings);
void	print_flt(t_format *settings);
void	print_n(t_format *settings);
void	print_left_right(char *str, t_format *settings);

#endif
