#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>
int main()
{
	char s[100];
	char d[120];
    getcwd(s, 100);
	sprintf(d,"mkdir %s/decade1",s);
	int i=system(d);
	printf("%d\n",i);
	// printing current working directory
	//printf("%s\n",s);

	// using the command
	//chdir("..");

	// printing current working directory
	//printf("%s\n", getcwd(s, 100));

	// after chdir is executed
	return 0;
}
