#include "minishell.h"

int	main(void)
{
	while (1)
	{
		char * str = readline("Myshell $ ");
        free(str);
	}
}