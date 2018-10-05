/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvysotsk <vvysotsk@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 17:08:30 by vvysotsk          #+#    #+#             */
/*   Updated: 2018/10/02 17:08:31 by vvysotsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTF_H
# define PRINTF_H

# include <stdarg.h>
# include "libft.h"

# define ISLEN(c) (c == 'h' || c == 'l' || c == 'j' || c == 'z')
# define BIGGER(x, y) (((x) > (y)) ? (x) : (y))
# define SMALLER(x, y) (((x) < (y)) ? (x) : (y))
# define IS_X(a) (((unsigned)a | 32) - 97 == 23u)
# define IS_O(a) (((unsigned)a | 32) - 97 == 14u)
# define IS_D(a) (((unsigned)a | 32) - 97 == 3u)
# define IS_U(a) (((unsigned)a | 32) - 97 == 20u)
# define ISX0(a) ((IS_X(a)) || (IS_O(a)))
# define TOUPPER(a) (((unsigned)a - 97) < 26u ? a - 32 : a)
# define ISDIGIT(a) (((unsigned)a-48) < 10u)
# define ISALPHA(a) (((unsigned)a | 32) - 97 < 26u)

typedef enum	e_bool
{
	false,
	true
}				t_bool;

typedef struct	s_f_out
{
	size_t		len;
	size_t		space;
	char		*data;
}				t_f_out;

typedef enum	e_islen
{
	hh,
	h,
	l,
	ll,
	j,
	z
}				t_islen;

typedef enum	e_flag
{
	LEFT = 1 << 0,
	POS = 1 << 1,
	INV = 1 << 2,
	ZER = 1 << 3,
	HTG = 1 << 4
}				t_flag;

typedef struct	s_data
{
	char		flags;
	char		length;
	char		spec;
	int			width;
	int			prec;
	int			pset:1;
}				t_data;

typedef struct	s_conv_opt
{
	char c;
	void (*f)(t_f_out *, t_data *, va_list);
}				t_conv_opt;

int				ft_printf(const char *format, ...);
int				ft_check_printf(char **m_str, const char *format, va_list ap);
int				ft_start_printf(char **m_str, const char *format, va_list ap);
int				ft_dprintf(int fd, const char *format, ...);
void			ft_handle(t_f_out *f_out, const char **format, \
				t_data *data, va_list ap);
void			ft_conversion(t_f_out *f_out, t_data *data, va_list ap);
void			ft_percent_conversion(t_f_out *f_out, t_data *data, va_list ap);
void			ft_handle_zer(t_data *data, char **str);
void			ft_build_new(t_data *data, char **str, char *new_str);
void			ft_prec_handle(t_data *data, char **str);
void			ft_prec_nums(t_data *data, char **str);
int				ft_form_out(t_f_out *f_out, size_t space);
void			ft_form_new(t_f_out *f_out, size_t size);
void			ft_set_form(t_f_out *f_out, char *data, size_t size);
void			ft_set_data(t_f_out *f_out, char *data);
void			ft_form_free(t_f_out *f_out);
t_bool			set_width(const char **format, t_data *data, va_list ap);
t_bool			set_precision(const char **format, t_data *data, va_list ap);
t_bool			set_flags(const char **format, t_data *data);
t_bool			set_len(const char **format, t_data *data);
intmax_t		ft_set_int_len(char length, va_list ap);
void			ft_num(t_f_out *f_out, t_data *data, va_list ap);
void			ft_hex(t_f_out *f_out, t_data *data, va_list ap);
void			ft_octal(t_f_out *f_out, t_data *data, va_list ap);
void			ft_dec(t_f_out *f_out, t_data *data, va_list ap);
uintmax_t		ft_num_len(char length, va_list ap);
void			ft_handle_alt(t_data *data, char **str);
void			ft_x_toupper(char *str, char spec);
void			ft_num_handle(char **str, t_data *data);
wchar_t			*ft_wstrdup(wchar_t *wstr);
size_t			ft_wstrlen(wchar_t *wstr);
void			ft_prec_wstr(t_data *data, wchar_t *wstr);
char			*ft_wstr_to_str(wchar_t *wstr);
void			ft_wstr(t_f_out *f_out, t_data *data, va_list ap);
char			*ft_put_null(t_data *data);
void			ft_str(t_f_out *f_out, t_data *data, va_list ap);
void			ft_uni(wchar_t c, char *str);
int				ft_unicode_b(wchar_t chr);
int				ft_handle_wchar(char **str, va_list ap);
void			ft_null_chr(t_f_out *f_out, char *str);
void			ft_char(t_f_out *f_out, t_data *data, va_list ap);
void			ft_float(t_f_out *f_out, t_data *data, va_list ap);
void			ft_binary(t_f_out *f_out, t_data *data, va_list ap);
intmax_t		*ft_printf_n_len(t_data *data, va_list ap);
void			ft_none(t_f_out *f_out, t_data *data, va_list ap);
t_bool			ft_color(t_f_out *f_out, const char **format);
#endif
