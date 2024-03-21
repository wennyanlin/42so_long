#include "so_long.h"

typedef struct s_row
{
	int		continue_from;
	char	*content;
} t_row;

int	count_rows(char *str, char seperator)
{
	int	i;
	int	count_rows;
	char *str_copy;

	i = 0;
	count_rows = 0;
	str_copy = str;
	while (str_copy[i])
	{
		while (str_copy[i] && str_copy[i] == seperator)
			i++;
		if (str_copy[i] && str_copy[i] != seperator)
			count_rows++;
		while (str_copy[i] && str_copy[i] != seperator)
			i++;
	}
	return (count_rows);
}
t_row	get_next_row(char *str, char seperator, int continue_from)
{
	int		i;
	int		j;
	int		start;
	char	*row;
	t_row	result_row;

	i = continue_from;
	j = 0;
	result_row.content = NULL;
	while (str[i] && str[i] == seperator)
		i++;
	if (str[i] && str[i] != seperator)
		start = i;
	while (str[i] && str[i] != seperator)
		i++;
	row = malloc(sizeof(char) * (i - start + 1));
	if (!row)
		return (result_row);
	while (start < i)
		row[j++] = str[start++];
	row[j] = '\0';
	result_row.content = row;
	result_row.continue_from = i;
	return (result_row);
}

char	**ft_split(char *str, char seperator)
{
	char	**rows;
	int		i;
	int		num_rows;
	t_row	row;

	row.continue_from = 0;
	num_rows = count_rows(str, seperator);
	rows = malloc(sizeof(char *) * (num_rows + 1));
	if (!rows)
		return (NULL);
	i = 0;
	while (i < num_rows)
	{
		row = get_next_row(str, seperator, row.continue_from);
		rows[i++] = row.content;
	}
	rows[i] = NULL;
	if (!rows[0])
		return (NULL);
	return (rows);
}
