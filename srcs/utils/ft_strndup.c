char	*ft_strndup(const char *str, int n)
{
	char	*dest;
	int		i;

	dest = malloc(sizeof(char) * (n + 1));
	if (!dest)
		return (NULL);
	i = -1;
	while (++i < n)
		dest[i] = str[i];
	dest[n] = 0;
	return (dest);
}
