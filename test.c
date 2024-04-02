#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>
#include "libft.h"

int main()
{
	//int str[5] = {5, 5, 5, 5, 5};
	char dest[50] = "Hello, World!\n";
	//char *src = "Fuck u, cruel world!\n\0";

	//ft_strlcat(dest, src, 50);
	ft_memset(dest, 'A', 50);
	printf("%s\n", dest);
	//for (int i = 0; i < 10; i++)
	//	printf("%d\n", dest[i]);
}
