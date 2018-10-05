/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:00:04 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/02 17:00:05 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

intmax_t		ft_set_int_len(char length, va_list ap)
{
	if (length == hh)
		return ((signed char)va_arg(ap, int));
	if (length == h)
		return ((short)va_arg(ap, int));
	if (length == l)
		return (va_arg(ap, long));
	if (length == ll)
		return (va_arg(ap, long long));
	if (length == j)
		return (va_arg(ap, intmax_t));
	if (length == z)
		return (va_arg(ap, ssize_t));
	return (va_arg(ap, int));
}

void			ft_num(t_f_out *f_out, t_data *data, va_list ap)
{
	intmax_t	num;
	char		*buff;

	if (data->spec == 'D')
		data->length = l;
	if (data->spec == 'i' || data->spec == 'D')
		data->spec = 'd';
	num = ft_set_int_len(data->length, ap);
	buff = ft_imaxtoa(num);
	if (data->prec != -1 && data->flags & ZER)
		data->flags ^= ZER;
	if (data->prec == 0 && !ft_strcmp("0", buff))
		*buff = '\0';
	if (((data->flags & POS || data->flags & INV) && buff[0] != '-') \
		&& data->spec == 'd')
	{
		ft_save_to_str(&buff, (data->flags & INV) ? " " : "+");
		buff[0] = ((data->flags & POS)) ? '+' : buff[0];
	}
	ft_prec_nums(data, &buff);
	ft_handle_zer(data, &buff);
	ft_set_data(f_out, buff);
	free(buff);
}

void			ft_hex(t_f_out *f_out, t_data *data, va_list ap)
{
	uintmax_t	num;
	char		*buff;

	if (data->spec == 'p')
		data->length = j;
	num = ft_num_len(data->length, ap);
	buff = ft_uimaxtoa_base(num, 16, "0123456789abcdef");
	if (data->spec == 'p' && data->flags & ZER && data->pset)
		data->flags ^= ZER;
	ft_num_handle(&buff, data);
	ft_set_data(f_out, buff);
	free(buff);
}

void			ft_octal(t_f_out *f_out, t_data *data, va_list ap)
{
	uintmax_t	num;
	char		*str;

	if (data->spec == 'O')
		data->length = l;
	num = ft_num_len(data->length, ap);
	str = ft_uimaxtoa_base(num, 8, "01234567");
	ft_num_handle(&str, data);
	ft_set_data(f_out, str);
	free(str);
}

void			ft_dec(t_f_out *f_out, t_data *data, va_list ap)
{
	uintmax_t	num;
	char		*str;

	if (data->spec == 'U')
		data->length = l;
	num = ft_num_len(data->length, ap);
	str = ft_uimaxtoa_base(num, 10, "0123456789");
	ft_num_handle(&str, data);
	ft_set_data(f_out, str);
	free(str);
}
