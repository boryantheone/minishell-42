#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>

int	main(void)
{
	while (1)
	{
		char * str = readline("Myshell $ ");
        free(str);
	}
}