/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/04 15:58:58 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/04 15:58:59 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

uintmax_t		ft_num_len(char length, va_list ap)
{
	if (length == hh)
		return ((unsigned char)va_arg(ap, int));
	if (length == h)
		return ((unsigned short)va_arg(ap, int));
	if (length == l)
		return (va_arg(ap, unsigned long));
	if (length == ll)
		return (va_arg(ap, unsigned long long));
	if (length == j)
		return (va_arg(ap, uintmax_t));
	if (length == z)
		return (va_arg(ap, size_t));
	return (va_arg(ap, unsigned int));
}

void			ft_handle_alt(t_data *data, char **str)
{
	char		*new_str;

	if (!(ISX0(data->spec) || data->spec == 'p' || data->spec == 'b'))
		return ;
	new_str = ft_strdup(*str);
	if (data->spec == 'p')
		ft_save_to_str(&new_str, "0x");
	else if (data->flags & HTG)
	{
		if (data->spec == 'b' && ft_strcmp("0", *str) \
			&& ft_strcmp("\0", *str))
			ft_save_to_str(&new_str, "0b");
		else if (IS_X(data->spec) && ft_strcmp("0", *str) \
			&& ft_strcmp("\0", *str))
			ft_save_to_str(&new_str, "0x");
		else if (IS_O(data->spec) && **str != '0')
			ft_save_to_str(&new_str, "0");
	}
	free(*str);
	*str = new_str;
}

void			ft_x_toupper(char *str, char spec)
{
	if (spec != 'X')
		return ;
	while (*str)
	{
		if (ISALPHA(*str))
			*str = TOUPPER(*str);
		str++;
	}
}

void			ft_num_handle(char **str, t_data *data)
{
	if (data->flags & ZER && data->prec == 0)
		data->flags ^= ZER;
	if (data->prec == 0 && !ft_strcmp(*str, "0"))
		**str = '\0';
	ft_prec_nums(data, str);
	if (data->flags & ZER && data->spec == 'p')
	{
		data->width = BIGGER(data->width - 2, 0);
		ft_handle_zer(data, str);
	}
	else if (data->flags & ZER && data->flags & HTG && (IS_X(data->spec) \
		|| data->spec == 'b'))
	{
		data->width = BIGGER(data->width - 2, 0);
		ft_handle_zer(data, str);
	}
	ft_handle_alt(data, str);
	if (!(data->flags & ZER && data->flags & HTG && (IS_X(data->spec) \
		|| data->spec == 'p' || data->spec == 'b')))
		ft_handle_zer(data, str);
	ft_x_toupper(*str, data->spec);
}
