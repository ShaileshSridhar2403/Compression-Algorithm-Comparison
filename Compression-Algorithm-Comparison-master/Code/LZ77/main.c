#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include "helper.c"
#include "lz77.c"



void lz77(char *text , char *outputFile)
{
    
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start); //start timestamp
    lz77_encoding(text);
    clock_gettime(CLOCK_REALTIME, &end); //end timestamp
    free(text);
    printf("%lf\n", time_elapsed(&start, &end));
    return 0;
}
