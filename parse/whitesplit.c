/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   whitesplit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag < idelfag@student.1337.ma>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 02:01:20 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/31 01:48:57 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse.h"

int	search(char c, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (charset[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	get_total_words(char *str, char *charset)
{
	int	i;
	int	_string_count;

	_string_count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && search(str[i], charset))
			i++;
		if (str[i])
			_string_count++;
		while (str[i] && !search(str[i], charset))
			i++;
	}
	return (_string_count);
}

int	get_word_len(char *str, char *charset)
{
	int	len;

	len = 0;
	while (str[len] && !search(str[len], charset))
		len++;
	return (len);
}

char	*copy_word(char *str, char *charset)
{
	char	*dest;
	int		i;
	int		word_len;

	i = 0;
	word_len = get_word_len(str, charset);
	dest = (char *) malloc(sizeof(char) * word_len + 1);
	if (!dest)
		return (NULL);
	while (str[i] && !search(str[i], charset))
	{
		dest[i] = str[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

char	**ft_split_two(char *str, char *charset)
{
	char	**array;
	char	**start;
	int		total_words;

	total_words = get_total_words(str, charset);
	array = (char **) malloc(sizeof(char *) * (total_words + 1));
	if (!array)
		return (NULL);
	start = array;
	while (*str)
	{
		while (*str && search(*str, charset))
			str++;
		if (*str)
		{
			*array = copy_word(str, charset);
			array++;
		}
		while (*str && !search(*str, charset))
			str++;
	}
	*array = 0;
	return (start);
}
