
#include <stdio.h>

void read_strings(char* filename);

int main(void)
{
    read_strings("Empty.txt");
    read_strings("Whitespaceonly.txt");
    read_strings("WhitespaceafterString.txt");
    read_strings("EOFafterString.txt");
    return 0;
}

void read_strings(char* filename)
{
    char str1[64] = "";
    char str2[64] = "";
    
    FILE* fp;
    int result;

    printf("Reading %s\n", filename);
    
    fp = fopen(filename, "r");
    
    result = fscanf(fp, "%63s", str1);
    printf("First read result is %d %s\n", result, str1);

    result = fscanf(fp, "%63s", str2);
    printf("Second read result is %d %s\n", result, str2);
    
    fclose(fp);

}



/* input files
Empty.txt is completely empty

Whitespaceonly.txt has a few spaces only

WhitespaceafterString.txt has the following:
   hello
there is only spaces after the string

EOFafterString.txt
   hello
there is no whitespace after the string
 
*/
/*
output on Xcode 5 C89
Reading Empty.txt
First read result is -1 
Second read result is -1 
Reading Whitespaceonly.txt
First read result is -1 
Second read result is -1 
Reading WhitespaceafterString.txt
First read result is 1 hello
Second read result is -1 
Reading EOFafterString.txt
First read result is 1 hello
Second read result is -1
*/

/* output on gcc 4.4.7 on CAEN
-bash-4.1$ gcc -std=c89 EOFDemo.c
-bash-4.1$ ./a.out
First read result is -1
Second read result is -1 
Reading Whitespaceonly.txt
First read result is -1 
Second read result is -1 
Reading WhitespaceafterString.txt
First read result is 1 hello
Second read result is -1 
Reading EOFafterString.txt
First read result is 1 hello
Second read result is -1
*/
