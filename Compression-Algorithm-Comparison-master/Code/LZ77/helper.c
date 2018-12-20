#include <stdio.h>
#include <stdlib.h>



//read the entire file 'filename'
char* read_text_file(char *filename)
{
    FILE *fp = fopen(filename, "r");
    if(!fp)
    {
        perror(filename);
        exit(EXIT_FAILURE);
    }
    
    char *buffer = NULL;
    long length;
    
    fseek(fp, 0, SEEK_END);
    length = ftell(fp);
    fseek (fp, 0, SEEK_SET);
        
    buffer = (char*)malloc((length+1)*sizeof(char));
    if(buffer)
        fread(buffer, 1, length, fp);
        
    fclose(fp);
    
    buffer[length] = '\0';
    
    return buffer;
}
