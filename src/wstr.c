/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wstr.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:01:20 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/02 17:01:22 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

wchar_t			*ft_wstrdup(wchar_t *wstr)
{
	wchar_t		*new_wstr;
	size_t		size;

	size = 0;
	while (wstr[size])
		++size;
	new_wstr = (wchar_t *)malloc(sizeof(wchar_t) * (size + 1));
	if (!new_wstr)
		return (NULL);
	size = 0;
	while (wstr[size])
	{
		new_wstr[size] = wstr[size];
		size++;
	}
	new_wstr[size] = '\0';
	return (new_wstr);
}

size_t			ft_wstrlen(wchar_t *wstr)
{
	size_t		counter;
	size_t		index;

	index = 0;
	counter = 0;
	while (wstr[index])
	{
		counter += ft_unicode_b(wstr[index]);
		index++;
	}
	return (counter);
}

void			ft_prec_wstr(t_data *data, wchar_t *wstr)
{
	size_t		counter;
	size_t		index;

	index = 0;
	counter = 0;
	if (data->prec == -1)
		return ;
	if (ft_wstrlen(wstr) <= (size_t)data->prec)
		return ;
	while (wstr[index] && counter <= (size_t)data->prec)
	{
		counter += ft_unicode_b(wstr[index]);
		index++;
	}
	wstr[index - 1] = '\0';
}

char			*ft_wstr_to_str(wchar_t *wstr)
{
	char		*result;
	size_t		index;
	size_t		pos;

	index = 0;
	pos = 0;
	result = ft_strnew(ft_wstrlen(wstr));
	while (wstr[index])
	{
		ft_uni(wstr[index], result + pos);
		pos += ft_unicode_b(wstr[index]);
		index++;
	}
	return (result);
}

void			ft_wstr(t_f_out *f_out, t_data *data, va_list ap)
{
	wchar_t		*tmp;
	char		*new_str;

	tmp = va_arg(ap, wchar_t *);
	if (!tmp)
		new_str = ft_put_null(data);
	else
	{
		tmp = ft_wstrdup(tmp);
		ft_prec_wstr(data, tmp);
		new_str = ft_wstr_to_str(tmp);
		free(tmp);
	}
	ft_handle_zer(data, &new_str);
	ft_set_data(f_out, new_str);
	free(new_str);
}
