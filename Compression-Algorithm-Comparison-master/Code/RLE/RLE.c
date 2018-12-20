#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include<string.h>
#include <time.h>
double time_elapsed(struct timespec *start, struct timespec *end);
int length_of_occurences(int n)
{
	int l = 0;
	while(n!=0)
	{
		l++;
		n=n/10;
	}
	return l;
}
void Rle(char text[],char *outputFile)
{
	struct timespec start;
	struct timespec end;
	clock_gettime(CLOCK_REALTIME, &start);
	FILE *fp = fopen(outputFile,"w");
	char *dest = (char*)malloc(sizeof(char)*100000000);
	int length = strlen(text);
	int j = 0;
	int rlen;
	int digit;
	for(int i = 0 ; i<length ; i++) 
	{
		if(text[i]=='\n')
		{
			dest[j++] = '\n';
			continue;
		}
		dest[j++] = text[i];
		rlen = 1;
		while(i+1<length && text[i]== text[i+1])
		{
			rlen++;
			i++;
		}
		int l = length_of_occurences(rlen);
		int k = l;
		while(rlen!=0)
		{
			digit = rlen%10;
			rlen=rlen/10;
			dest[j+l-1] = digit+'0';
			l--;
		}
		j=j+k;
		
	}
	fprintf(fp,"%s",dest);
	clock_gettime(CLOCK_REALTIME, &end);
	printf("\nCompression factor %f\n",(float)strlen(dest)/strlen(text));
	printf("Time taken:%lf\n", time_elapsed(&start, &end));
	fclose(fp);
	
}
int isDigit(char ch)
{
	if(ch>='0' && ch<='9')
		return 1;
	else
		return 0;
}
void RLE_DECRYPT(char text[],char dest[])
{
	int rlen = 0;
	int l = strlen(text);
	int j = 0 ;
	int k ;
	char c;
	for(int i = 0 ; i<l ;i++)
	{
		if(isDigit(text[i])==0)
		{
			c = text[i];
		}
		while(isDigit(text[i])==1)
		{
			rlen = rlen *10 + text[i] - '0';
			if(isDigit(text[i+1])==0)
				break;
			else
				i++;
		}
		if(text[i]=='\n')
		{
			dest[j++]=text[i]; 
			continue;
		}

		while(rlen>0)
		{
			dest[j] = c;
			j++;
			rlen--;
		}
		
	}

}	

double time_elapsed(struct timespec *start, struct timespec *end) {
	double t;
	t = (end->tv_sec - start->tv_sec); // diff in seconds
	t += (end->tv_nsec - start->tv_nsec) * 0.000000001; //diff in nanoseconds
	return t;
}
