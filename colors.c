/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atoi_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:48:01 by esalmela          #+#    #+#             */
/*   Updated: 2024/03/12 18:44:39 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	to_lower(char c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

int	get_digit(char c, int digits_in_base)
{
	int	max_digit;

	if (digits_in_base <= 10)
		max_digit = digits_in_base + '0';
	else
		max_digit = digits_in_base - 10 + 'a';
	if (c >= '0' && c <= '9' && c <= max_digit)
		return (c - '0');
	else if (c >= 'a' && c <= 'f' && c <= max_digit)
		return (10 + c - 'a');
	else
		return (-1);
}

unsigned int	ft_atoi_base(const char *str, int str_base)
{
	unsigned int	result;
	int				digit;

	result = 0;
	digit = get_digit(to_lower(*str), str_base);
	while (digit >= 0)
	{
		result = result * str_base;
		result = result + digit;
		++str;
		digit = get_digit(to_lower(*str), str_base);
	}
	result = result * str_base;
	result = result + 15;
	result = result * str_base;
	result = result + 15;
	return (result);
}

unsigned int	check_colors(char *str)
{
	while (*str)
	{
		if (*str == ',')
		{
			str++;
			str++;
			str++;
			return (ft_atoi_base(str, 16));
		}
		str++;
	}
	return (4294967294);
}

unsigned int	determine_color(char *str, int z)
{
	if (check_colors(str) == 4294967294)
	{
		if (z < 0)
			return (ft_atoi_base("FF0000", 16));
		if (z == 0)
			return (ft_atoi_base("0000FF", 16));
		if (z > 0 && z <= 10)
			return (ft_atoi_base("FF00FF", 16));
		return (ft_atoi_base("00FF00", 16));
	}
	return (check_colors(str));
}
