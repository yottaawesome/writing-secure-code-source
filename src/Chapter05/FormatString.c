#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef void (*ErrFunc)(unsigned long);

void GhastlyError(unsigned long err)
{
	printf("Unrecoverable error! - err = %d\n", err);

	//This is, in general, a bad practice.
	//Exits buried deep in the X Window libraries once cost
	//me over a week of debugging effort.
	//All application exits should occur in main, ideally in one place.
	exit(-1);
}

void RecoverableError(unsigned long err)
{
	printf("Something went wrong, but you can fix it - err = %d\n", err);
}

void PrintMessage(char* file, unsigned long err)
{
	ErrFunc fErrFunc;
	char buf[512];

	if(err == 5)
	{
		//access denied
		fErrFunc = GhastlyError;
	}
	else
	{
		fErrFunc = RecoverableError;
	}

	_snprintf(buf, sizeof(buf)-1, "Cannot find %s", file);

	//just to show you what is in the buffer
	printf("%s", buf);
	//just in case your compiler changes things on you
	printf("\nAddress of fErrFunc is %p\n", &fErrFunc);

	//Here's where the damage is done!
	//Don't do this in your code.
	fprintf(stdout, buf);

	printf("\nCalling ErrFunc %p\n", fErrFunc);
	fErrFunc(err);

}

void foo(void)
{
	printf("Augh! We've been hacked!\n");
}

int main(int argc, char* argv[])
{
	FILE* pFile;

	//a little cheating to make the example easy
	printf("Address of foo is %p\n", foo);

	//this will only open existing files
	pFile = fopen(argv[1], "r");

	if(pFile == NULL)
	{
		PrintMessage(argv[1], errno);
	}
	else
	{
		printf("Opened %s\n", argv[1]);
		fclose(pFile);
	}
	
	return 0;
}
