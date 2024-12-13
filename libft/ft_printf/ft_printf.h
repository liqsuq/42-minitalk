/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kadachi <kadachi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 19:33:47 by kadachi           #+#    #+#             */
/*   Updated: 2024/12/09 16:36:40 by kadachi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include "libft.h"

# define DEC "01234567"
# define HEX_LO "0123456789abcdef"
# define HEX_UP "0123456789ABCDEF"

int		ft_printf(const char *format, ...);
int		ft_dprintf(int fd, const char *format, ...);
int		print_char(int fd, int c);
int		print_str(int fd, char *str);
int		print_ptr(int fd, unsigned long ptr);
int		print_int(int fd, int n, int is_unsigned, char *base);
int		print_raw(int fd, const char *format);

#endif