#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "lz77.c"



void lz77(char *text , char *outputFile)
{
    
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start); //start timestamp
    lz77_encoding(text,outputFile);
    clock_gettime(CLOCK_REALTIME, &end); //end timestamp
    FILE *output = fopen(outputFile, "r");
    fseek(output, 0, SEEK_END);
    int length_comp = ftell(output);
    // fseek(output, 0, SEEK_SET);
    fclose(output);
    printf("Compression ratio%f",(float)length_comp/strlen(text));
    printf("%lf\n", time_elapsed(&start, &end));
    free(text);
}
