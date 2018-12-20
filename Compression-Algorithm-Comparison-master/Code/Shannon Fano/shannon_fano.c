#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
typedef struct symFreq{
	char sym;
	float freq;
}symFreq;

void swapStruct(symFreq A,symFreq B){
	char cTemp = A.sym;
	float fTemp = A.freq;
	A.sym = B.sym;
	A.freq = B.freq;
	B.sym = cTemp;
	B.freq = fTemp;
}
float absolute(float a){
	return a>0?a:-a;
}
int addBit(int orig,int addBit){
	int res = 2*orig;
	return addBit?orig+1:orig;
}



char* makeBinaryString(char* text,char** codes){     //main function. Pass the text and the set of codes that you have found(array of strings) Returns the desired binary string after padding
	char* bitString = (char*)malloc(sizeof(char)*10000000);
	int len = strlen(text);
	int i,j,k;
	for(i=0;i<len;i++){
		int k = 0 ;
		// printf("symbol: %c code: %s\n",text[i],codes[text[i]]);
		 while(k<strlen(codes[text[i]]))
		 {
		 	bitString[j]=codes[text[i]][k];
		 	j++;
		 	k++;
		 }
	}
	int bitStringLength = strlen(bitString);
	int padLength = 8-bitStringLength%8;
	for(i = 0;i<padLength;i++){
		bitString[bitStringLength + i] = '0';
	}
	bitString[bitStringLength + i] = '\0';
	return bitString;
}
int cOffset;
void insertionSort(symFreq* arr,int n){
  symFreq temp;
  int maxInd;
  for(int i=0;i<n;i++){
    maxInd = i;
    for(int j=i;j<n;j++){
      if(arr[j].freq>arr[maxInd].freq){
        maxInd = j;
      }
    }
    temp = arr[i];
    arr[i] = arr[maxInd];
    arr[maxInd] = temp;
    swapStruct(arr[maxInd],arr[i]);
  }
}

// typedef struct symFreq{
// 	char sym;
// 	float freq;
// }symFreq;

// void swapStruct(symFreq A,symFreq B){
// 	char cTemp = A.sym;
// 	float fTemp = A.freq;
// 	A.sym = B.sym;
// 	A.freq = B.freq;
// 	B.sym = cTemp;
// 	B.freq = fTemp;
// }
// float absolute(float a){
// 	return a>0?a:-a;
// }
// int addBit(int orig,int addBit){
// 	int res = 2*orig;
// 	return addBit?orig+1:orig;
// }


// char* fileReader(FILE* fp){
// 	char buffer[10000];
// 	char* text = (char*)malloc(sizeof(char)*100000);
// 	text[0] = '\0';
// 	while(fgets(buffer,10000,fp)){
// 		// printf()
// 		strcat(text,buffer);
// 	}
// 	return text;
// }
typedef struct node{
	int chr;
	int sLeaf;
	struct node* children[2];
}node;



symFreq* initFreqTable(){
	symFreq* table = (symFreq*)malloc(sizeof(symFreq)*256);
	for(int i=0;i<256;i++){
		table[i].sym = i;
		table[i].freq = 0;
	}
	return table;
}


// void insertionSort(symFreq* arr,int n){
//   symFreq temp;
//   int maxInd;
//   for(int i=0;i<n;i++){
//     maxInd = i;
//     for(int j=i;j<n;j++){
//       if(arr[j].freq>arr[maxInd].freq){
//         maxInd = j;
//       }
//     }
//     temp = arr[i];
//     arr[i] = arr[maxInd];
//     arr[maxInd] = temp;
//     swapStruct(arr[maxInd],arr[i]);
//   }
// }

int calcFreq(symFreq* table,char* text,int textLength){
	int uniqueCount = 0;
	for(int i=0;i<textLength;i++){
		// if(text[i]>30){
			if(table[text[i]].freq == 0.0)uniqueCount += 1;
			table[text[i]].freq += 1.0;
		// }
	}
	for(int i =0;i<256;i++)
		table[i].freq = table[i].freq/(textLength-1);
	return uniqueCount;
}


int divideTable(symFreq* table,int tableLen){ 		//splits table at i, into a[0...i], a[i+1...n-1]
	float totalSum = 0;
	float cumulative = 0;
	float delta =1;

	for(int i=0;i<tableLen;i++)totalSum+=table[i].freq; //calculating total
	float halfPoint = totalSum/2;
	for(int i=0;i<tableLen;i++){
		cumulative+=table[i].freq;
		if (absolute(halfPoint - cumulative)>delta)return i-1;
		delta = absolute(halfPoint - cumulative);
		// printf("delta: %f\n", delta);
	}
}


void split(symFreq* table,int len,int output,char** codes,int depth){
	// printf("split: output is %d",output);
	if(len<=1){
		// printf("code for %c done,code is:%d\n",table[0].sym,output);
		codes[table[0].sym] = intToBin(output,depth);
		return;
	}
	

	int splitIndex = divideTable(table,len);
	// printf("\nsplit Index:%d",splitIndex);
	// printf("\nlength:%d\n\n",len);
	// printf("OUUTPUT:%d\n",output);
	// split(table,splitIndex+1,addBit(output,0),codes);
	// split(&table[splitIndex+1],len - (splitIndex+1),addBit(output,1),codes);
	split(table,splitIndex+1,2*output,codes,depth+1);
	split(&table[splitIndex+1],len - (splitIndex+1),2*output+1,codes,depth+1);
	return;
}

void shannon_fano(char *text,char *outputFile){
	
	char* codes[256];
	for(int i=0;i<256;i++){
		codes[i] = NULL;
	}
	struct timespec start;
	struct timespec end;
	clock_gettime(CLOCK_REALTIME,&start);
	// fclose(fp);
	symFreq* freqTable = initFreqTable();
	int tableLen = calcFreq(freqTable,text,strlen(text));
	insertionSort(freqTable,256);
	split(freqTable,tableLen,0,codes,0);
	free(freqTable);
	// free(text);
	//printCodes(codes);



	FILE* fp = fopen(outputFile,"wb");
	char* binString = (char*)malloc(sizeof(char)*10000000); 
	binString = makeBinaryString(text,codes);
	// printf("%ld\n",strlen(binString));
	char* output = (char*)malloc(sizeof(char)*10000000); 
	output = BStoCS(binString);
	// printf("%d\n",cOffset);
	for(int i = 0 ; i < cOffset ; i++)
	{
		fprintf(fp, "%c",output[i]);
	}
	fclose(fp);
	clock_gettime(CLOCK_REALTIME,&end);
	printf("compression factor%f\n",(float)cOffset/strlen(text));
	printf("Time taken:%lf\n", time_elapsed(&start, &end));
	char *binaryString = (char*)malloc(sizeof(char)*100000000);
	char * temp = (char*)malloc(sizeof(char)*8);
	int j = 0 ; 
	for(int i = 0 ; i < cOffset ; i++)
	{
		temp = intToBin(output[i]-'0',8);
		for(int k = 0 ; k < 8 ; k++)
		{
			binaryString[j]=temp[k];
			j++;
		}
	}
	free(output);
	free(binString);

}