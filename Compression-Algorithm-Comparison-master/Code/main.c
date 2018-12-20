#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "RLE/RLE.c"
#include "Huffman/hoofman2.c"
#include "Shannon Fano/shannon_fano.c"
#include "LZW/lzw.c"
#include "LZ77/lz77_client.c"
#include "LZ78/lz78_client.c"
void take_input(char *filename,char*text)
{
	FILE *fp = fopen(filename, "r");
	if(fp==NULL)
	{
		printf("Please Enter valid file name");
		exit(0);
	}
	fread(text, sizeof(char), 100000000, fp);
} 


int main()
{
	char *file_name=(char*)malloc(sizeof(char)*100);
	char *compressed_file_name = (char*)malloc(sizeof(char)*100);
	int choice;
	char * text = (char*)malloc(sizeof(char)*100000000);
	printf("Enter the name of the text file to be compressed\n");
	scanf("%s",file_name);

	printf("Enter the name of the compressed file\n");
	scanf("%s",compressed_file_name);
	printf("Pick the algorithm you want to compress the file with\n");
	printf("1. Run Length Encoding\n");
	printf("2. Huffman Encoding\n");
	printf("3. Shannon Fano\n");
	printf("4. LZW\n");
	printf("5. LZ77\n");
	printf("6. LZ78\n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1: take_input(file_name,text);
				Rle(text,compressed_file_name);
				break;
		case 2: take_input(file_name,text);
				huffman(text,compressed_file_name);
				break;
		case 3: take_input(file_name,text);
				shannon_fano(text,compressed_file_name);
				break;
		case 4: lzw(file_name,compressed_file_name);
				break;
		case 5: take_input(file_name,text);
				lz77(text,compressed_file_name);
				break;
		case 6: take_input(file_name,text);
				lz78(text,compressed_file_name);
				break;
		default: printf("Enter Valid Choice");
				break;
	}


}