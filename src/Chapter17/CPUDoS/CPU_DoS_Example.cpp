/*
  CPU_DoS_Example.cpp
  This application shows the effects of two
  different methods of removing duplicate backslash
  characters.

  There are many, many ways to accomplish this task. These 
  are meant as examples only.
  */

#include <windows.h>
#include <stdio.h>
#include <assert.h>

/*
  This method reuses the same buffer, but is inefficient.
  The work done will vary with the square of the size of the input.

  It returns true if it removed a backslash.
  */

//We're going to assume that buf is null-terminated.
bool StripBackslash1(char* buf)
{
    char* tmp = buf;
    bool ret = false;

    for(tmp = buf; *tmp != '\0'; tmp++)
    {
        if(tmp[0] == '\\' && tmp[1] == '\\')
        {
            //Move all the characters down one
            //using a strcpy where source and destination
            //overlap is BAD! This is an example of how NOT to do things.
            //This is a professional stunt application - don't try this 
            //at home.
            strcpy(tmp, tmp+1);
            ret = true;
        }
   }

    return ret;
}

/*
  This is a less CPU-intensive way of doing the same thing.
  It will have slightly higher overhead for shorter strings due to
  the memory allocation, but we only have to go through the string once.
  */

bool StripBackslash2(char* buf)
{
    unsigned long len, written;
    char* tmpbuf = NULL;
    char* tmp;
    bool foundone = false;

    len = strlen(buf) + 1;

    if(len == 1)
        return false;

    tmpbuf = (char*)malloc(len);
   
    //This is less than ideal - we should really return an error.
    if(tmpbuf == NULL)
    {
        assert(false);
        return false;
   }

    written = 0;
    for(tmp = buf; *tmp != '\0'; tmp++)
    {
        if(tmp[0] == '\\' && tmp[1] == '\\')
        {
            //Just don't copy this one into the other buffer.
            foundone = true;
        }
        else
        {
            tmpbuf[written] = *tmp;
            written++;
        }
    }

    if(foundone)
    {
        //Copying the temporary buffer over the input
        //using strncpy allows us to work with a buffer 
        //that isn't null-terminated.
        //tmp was incremented one last time as it fell out of the loop.
        strncpy(buf, tmpbuf, written);
        buf[written] = '\0';
    }

    if(tmpbuf != NULL)
        free(tmpbuf);

    return foundone;
}



bool StripBackslash3(char* str)
{
	char* read;
	char* write;

	//Always check assumptions.
	assert(str != NULL);

	if(strlen(str) < 2)
	{
		//No possible duplicates.
		return false;
	}

	//Initialize both pointers.
	for(read = write = str + 1; *read != '\0'; read++)
	{
		// If this character and last character are both backslashes,
		// don't write - only read gets incremented.

		if(*read == '\\' && *(read - 1) == '\\')
		{
			continue;
		}
		else
		{
			*write = *read;
			write++;
		}
	}

	//Write trailing null.
	*write = '\0';

	return true;

}


int main(int argc, char* argv[])
{
    char* input;
    char* end = "foo";
    DWORD tickcount;
    int i, j;

    //Now we have to build the string.

    for(i = 10; i < 10000001; i *= 10)
    {
        input = (char*)malloc(i);

        if(input == NULL)
        {
            assert(false);
            break;
        }

        //Now populate the string.
        //Account for the trailing "foo" on the end.
        //We're going to write 2 bytes past input[j], 
        //then append "foo\0".
        for(j = 0; j < i - 5; j += 3)
        {
            input[j] = '\\';
            input[j+1] = '\\';
            input[j+2] = 'Z';
        }

        //Remember that j was incremented before the conditional 
          //was checked.
        strncpy(input + j, end, 4);

        tickcount = GetTickCount();
        StripBackslash1(input);
        printf("StripBackslash1: input = %d chars, time = %d ms\n", 
               i, GetTickCount() - tickcount);

        //Reset the string - this test is destructive.
        for(j = 0; j < i - 5; j += 3)
        {
            input[j] = '\\';
            input[j+1] = '\\';
            input[j+2] = 'Z';
        }

        //Remember that j was incremented before the conditional
          //was checked.
        strncpy(input + j, end, 4);

        tickcount = GetTickCount();
        StripBackslash2(input);
        printf("StripBackslash2: input = %d chars, time = %d ms\n", 
               i, GetTickCount() - tickcount);

        free(input);
    }

    return 0;
}
