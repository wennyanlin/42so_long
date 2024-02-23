#include "so_long.h"

typedef struct s_word
{
	int		continue_from;
	char	*content;
} t_word;

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
}


int	count_word(char *str, char seperator)
{
	int	i;
	int	count_words;
	char *str_copy;

	i = 0;
	count_words = 0;
	str_copy = str;
	while (str_copy[i])
	{
		while (str_copy[i] && str_copy[i] == seperator)
			i++;
		if (str_copy[i] && str_copy[i] != seperator)
			count_words++;
		while (str_copy[i] && str_copy[i] != seperator)
			i++;
	}
	return (count_words);
}
t_word	get_next_word(char *str, char seperator, int continue_from)
{
	int		i;
	int		j;
	int		start;
	char	*word;
	t_word	result_word;

	i = continue_from;
	j = 0;
	result_word.content = NULL;
	while (str[i] && str[i] == seperator)
		i++;
	if (str[i] && str[i] != seperator)
		start = i;
	while (str[i] && str[i] != seperator)
		i++;
	word = malloc(sizeof(char) * (i - start + 1));
	if (!word)
		return (result_word);
	while (start < i)
		word[j++] = str[start++];
	word[j] = '\0';
	result_word.content = word;
	result_word.continue_from = i;
	return (result_word);
}

char	**ft_split(char *str, char seperator)
{
	char	**words;
	int		i;
	int		num_words;
	t_word	word;

	word.continue_from = 0;
	num_words = count_word(str, seperator);
	words = malloc(sizeof(char *) * (num_words + 1));
	if (!words)
		return (NULL);
	i = 0;
	while (i < num_words)
	{
		word = get_next_word(str, seperator, word.continue_from);
		words[i++] = word.content;
	}
	words[i] = NULL;
	if (!words[0])
		array_playground_exit(words, 1);
	return (words);
}
