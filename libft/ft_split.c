/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idelfag <idelfag@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 16:16:06 by idelfag           #+#    #+#             */
/*   Updated: 2023/12/29 14:23:50 by idelfag          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	words_count(const char *s, char sep)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == sep)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != sep)
			i++;
	}
	return (count);
}

static char	*get_word(const char *s, char sep, size_t *j)
{
	size_t	i;
	size_t	start;
	size_t	len;
	char	*word;

	word = NULL;
	i = 0;
	len = 0;
	while (s[i] == sep)
		i++;
	while (s[i] && s[i] != sep)
	{
		i++;
		len++;
	}
	*j += i;
	start = i - len;
	word = malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	ft_strlcpy(word, s + start, (len + 1));
	return (word);
}

static char	**ft_free(char **tab, int n)
{
	int	i;

	i = 0;
	while (i < n)
		free(tab[i]);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t	nb_word;
	size_t	j;
	char	**tab;
	size_t	i;

	if (s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	nb_word = words_count(s, c);
	tab = malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (NULL);
	while (i < nb_word)
	{
		tab[i] = get_word(s + j, c, &j);
		if (!tab[i])
			return (ft_free(tab, i));
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
