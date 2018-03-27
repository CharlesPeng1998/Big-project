#include "stdio.h"

int main()
{
	char *p, *q = NULL;
	char buf[100];
	int space = 1;
	while (gets(buf) && strlen(buf) != 0)
	{
		space += strlen(buf);
		p = (char *)malloc(space);
		if (q == NULL) { strcpy(p, buf); }
		else
		{
			strcpy(p, q);
			free(q);
			strcat(p, buf);
		}
		q = p;
	}
	printf("%s\n", p);
	return 0;
}