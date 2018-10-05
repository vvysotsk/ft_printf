/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uni.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 16:58:40 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/02 16:58:42 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void		ft_uni(wchar_t c, char *str)
{
	if (c < (MB_CUR_MAX == 1 ? 0xFF : 0x7F))
		str[0] = (unsigned char)c;
	else if (c < (1 << 11))
	{
		str[0] = (unsigned char)((c >> 6) | 0xC0);
		str[1] = (unsigned char)((c & 0x3F) | 0x80);
	}
	else if (c < (1 << 16))
	{
		str[0] = (unsigned char)(((c >> 12)) | 0xE0);
		str[1] = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		str[2] = (unsigned char)((c & 0x3F) | 0x80);
	}
	else if (c < (1 << 21))
	{
		str[0] = (unsigned char)(((c >> 18)) | 0xF0);
		str[1] = (unsigned char)(((c >> 12) & 0x3F) | 0x80);
		str[2] = (unsigned char)(((c >> 6) & 0x3F) | 0x80);
		str[3] = (unsigned char)((c & 0x3F) | 0x80);
	}
}

int			ft_unicode_b(wchar_t chr)
{
	if (chr < (1 << 7))
		return (1);
	else if (chr < (1 << 11))
		return (2);
	else if (chr < (1 << 16))
		return (3);
	else if (chr < (1 << 21))
		return (4);
	return (0);
}

int			ft_handle_wchar(char **str, va_list ap)
{
	wchar_t	chr;
	int		len;

	chr = va_arg(ap, wchar_t);
	len = ft_unicode_b(chr);
	*str = ft_strnew(len);
	ft_uni(chr, *str);
	return (chr == '\0');
}

void		ft_null_chr(t_f_out *f_out, char *str)
{
	int		index;
	int		len;

	index = 0;
	len = ft_strlen(str);
	while (index < len)
	{
		if (str[index] == 1)
			str[index] = 0;
		index++;
	}
	ft_set_form(f_out, str, len);
}

void		ft_char(t_f_out *f_out, t_data *data, va_list ap)
{
	char	c;
	char	*str;
	int		zero;

	zero = 0;
	if (data->spec == 'C' || data->length == l)
	{
		zero = ft_handle_wchar(&str, ap);
		if (zero)
			str[0] = zero;
	}
	else
	{
		c = va_arg(ap, int);
		str = ft_strnew(1);
		zero = (c == '\0') ? 1 : 0;
		str[0] = c + zero;
	}
	ft_handle_zer(data, &str);
	if (zero)
		ft_null_chr(f_out, str);
	else
		ft_set_data(f_out, str);
	free(str);
}
