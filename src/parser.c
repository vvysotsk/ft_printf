/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 16:59:08 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/02 16:59:09 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

t_bool			set_len(const char **format, t_data *data)
{
	const char	len[] = "hhlljz";
	int			index;

	index = 0;
	if (ISLEN(**format))
	{
		index = ft_find_char(len, **format);
		if (index == 0)
		{
			if (*(*format + 1) == 'h')
				++*format;
			else
				index = 1;
		}
		if (index == 2)
			index = (*(*format + 1) == 'l') ? 3 : 2;
		data->length = BIGGER(index, data->length);
		++*format;
		return (true);
	}
	return (false);
}

t_bool			set_flags(const char **format, t_data *data)
{
	const char	flags[] = "-+ 0#";
	size_t		index;

	index = 0;
	while (flags[index] != **format && flags[index])
		index++;
	if (flags[index])
	{
		data->flags |= (1 << index);
		(*format)++;
		return (true);
	}
	return (false);
}

t_bool			set_precision(const char **format, t_data *data, va_list ap)
{
	int			new_prec;

	new_prec = 0;
	if (**format != '.')
		return (false);
	data->pset = 1;
	(*format)++;
	if (**format == '*')
	{
		data->prec = va_arg(ap, int);
		if (data->prec < -1)
			data->prec = -1;
		(*format)++;
		return (true);
	}
	while (ISDIGIT(**format))
	{
		new_prec = new_prec * 10 + (**format - '0');
		(*format)++;
	}
	data->prec = new_prec;
	return (true);
}

t_bool			set_width(const char **format, t_data *data, va_list ap)
{
	int			width;

	width = 0;
	if (**format == '*')
	{
		data->width = va_arg(ap, int);
		if (data->width < 0)
		{
			if (!(data->flags & LEFT))
				data->flags ^= LEFT;
			data->width *= -1;
		}
		(*format)++;
		return (true);
	}
	if (!ISDIGIT(**format))
		return (false);
	while (ISDIGIT(**format))
	{
		width = width * 10 + (**format - '0');
		(*format)++;
	}
	data->width = width;
	return (true);
}
