#include    "minishell.h"

//tokens = {echo, -nnhnnnn, -n, Hello, World, NULL}
//echo -nnnnnnn -n -n -n Hello World


//s1 = "hello World" s2 = "ll"

static int	ft_strcmp(const char *s1, const char *s2)
{
	int i = 0;

	while(s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (unsigned char)s1[i] - (unsigned char)s2[i];
}

static int validate_flag(char *flag)
{
	int i;

	if(flag[0] != '-')
		return 0;
	
	i = 1;

	if(flag[i] != 'n')
		return 0;

	while(flag[i] != '\0')
	{
		if(flag[i] != 'n')
			return 0;
		i++;
	}
	return 1;
}

int	run_echo(char **tokens)
{
	int i;
	i = 1;
	while(tokens[i] != NULL)
	{
		printf("%s", tokens[i]);
		if(tokens[i+1] != NULL)
			printf(" ");
		i++;
	}
	printf("\n");
	return 1;
}