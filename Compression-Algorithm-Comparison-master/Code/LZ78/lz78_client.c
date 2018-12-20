#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>


#include "lz78.c"

//returns the duration from start to end times in sec

void lz78(char * text , char *outputFile)
{
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start); //start timestamp
    lz78_encoding(text,outputFile);
    clock_gettime(CLOCK_REALTIME, &end); //end timestamp
    FILE *output = fopen(outputFile, "r");
    fseek(output, 0, SEEK_END);
    int length_comp = ftell(output);
    fclose(output);
    printf("Compression ratio%f\n",(float)length_comp/strlen(text));
     printf("%lf\n", time_elapsed(&start, &end));
     free(text);
}