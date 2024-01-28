#include "so_long.h"

int	string_contain(char *str, char target)
{
	int	i;

	i = 0;
	if (!str)
		return (1);
	while (str[i])
	{
		if (str[i] == target)
			return (1);
		i++;
	}
	return (0);
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while(str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *str, int len)
{
	int		i;
	char	*result;

	if (!str)
		return (NULL);

	i = 0;
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	while (str[i] && i < len)
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		i;
	int		str1_len;
	int		str2_len;
	char	*result;

	i = 0;
	str1_len = ft_strlen(str1);
	str2_len = ft_strlen(str2);
	result = malloc(sizeof(char) * (str1_len + str2_len + 1));
	if (!result)
		return (NULL);
	str1_len = 0;
	str2_len = 0;

	while (str1[str1_len])
		result[i++] = str1[str1_len++];
	while (str2[str2_len])
		result[i++] = str2[str2_len++];
	result[i] = '\0';
	return (result);
}

void	test_string_utils()
{
	printf("strjoin result: '%s'\n", ft_strjoin("Hello", " World!"));
	printf("\nstring_contain result: %d expected: 1\n", string_contain("Hello,\nHow are you?", '\n'));
	printf("\nstring_contain result: %d expected: 0\n", string_contain("Hello, How are you?", 'f'));
	printf("\nft_strdup result: '%s' expected: '111111'\n", ft_strdup("111111\n234", 6));
}
