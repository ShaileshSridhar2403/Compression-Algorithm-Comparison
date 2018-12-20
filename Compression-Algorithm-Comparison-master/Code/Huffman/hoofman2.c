
#include <stdio.h> 
#include <stdlib.h> 
#include<time.h>
#include<string.h>
#define MAX_TREE_HT 1000000 
struct character
{
	int code[100];
	int top;
};
struct MinHeapNode { 
	char data; 
	unsigned freq;  
	struct MinHeapNode *left, *right; 
}; 
struct MinHeap { 
	unsigned size; 
	unsigned capacity; 
	struct MinHeapNode** array; 
}; 
int x = 0;

struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
	struct MinHeapNode* temp 
		= (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 

	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 

	return temp; 
} 

struct MinHeap* createMinHeap(unsigned capacity) 

{ 

	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 

	minHeap->size = 0; 

	minHeap->capacity = capacity; 

	minHeap->array = (struct MinHeapNode**)malloc(minHeap-> capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 

{ 

	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

void minHeapify(struct MinHeap* minHeap, int idx) 

{ 

	int smallest = idx; 
	int left = 2 * idx + 1; 
	int right = 2 * idx + 2; 

	if (left < minHeap->size && minHeap->array[left]-> freq < minHeap->array[smallest]->freq) 
		smallest = left; 

	if (right < minHeap->size && minHeap->array[right]-> freq < minHeap->array[smallest]->freq) 
		smallest = right; 

	if (smallest != idx) { 
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
		minHeapify(minHeap, smallest); 
	} 
} 

int isSizeOne(struct MinHeap* minHeap) 
{ 

	return (minHeap->size == 1); 
} 

struct MinHeapNode* extractMin(struct MinHeap* minHeap) 

{ 

	struct MinHeapNode* temp = minHeap->array[0]; 
	minHeap->array[0] = minHeap->array[minHeap->size - 1]; 

	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return temp; 
} 


void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) 

{ 

	++minHeap->size; 
	int i = minHeap->size - 1; 

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 

		minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 

	minHeap->array[i] = minHeapNode; 
} 


void buildMinHeap(struct MinHeap* minHeap) 

{ 

	int n = minHeap->size - 1; 
	int i; 

	for (i = (n - 1) / 2; i >= 0; --i) 
		minHeapify(minHeap, i); 
} 
void printArr(int arr[], int n) 
{ 
	int i;

	// printf("\n"); 
} 
 
int isLeaf(struct MinHeapNode* root) 

{ 

	return !(root->left) && !(root->right); 
} 

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 

{ 

	struct MinHeap* minHeap = createMinHeap(size); 

	for (int i = 0; i < size; ++i) 
		minHeap->array[i] = newNode(data[i], freq[data[i]]); 

	minHeap->size = size; 
	buildMinHeap(minHeap); 

	return minHeap; 
} 

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 

{ 
	struct MinHeapNode *left, *right, *top; 
 
	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 
	while (!isSizeOne(minHeap)) { 

		left = extractMin(minHeap); 
		right = extractMin(minHeap); 
		top = newNode('$', left->freq + right->freq); 

		top->left = left; 
		top->right = right; 

		insertMinHeap(minHeap, top); 
	} 

 
	return extractMin(minHeap); 
} 

void printCodes(struct MinHeapNode* root, int arr[], int top,struct character coded[]) 
{ 
 
	if (root->left) { 

		arr[top] = 0; 
		printCodes(root->left, arr, top + 1,coded); 
	} 
	if (root->right) { 

		arr[top] = 1; 
		printCodes(root->right, arr, top + 1,coded); 
	} 

	if (isLeaf(root)) { 
		 //printf("%c:",root->data);
		 x++;
		for (int i = 0; i < top; ++i) 
		{
			coded[root->data].code[i]=arr[i];
			coded[root->data].top++;	
			// printf("%d", arr[i]);

		}  
		x+=top;
		 //printf("\n");
	} 
} 

struct MinHeapNode* HuffmanCodes(char data[], int freq[], int size,struct character coded[]) 

{ 
	struct MinHeapNode* root = buildHuffmanTree(data, freq, size); 

	
	int arr[MAX_TREE_HT], top = 0; 

	printCodes(root, arr, top,coded);
	return root; 
} 

int* computeFrequency(char text[])
{
	int l = strlen(text);
	int *frequency = (int*)malloc(sizeof(int)*l);
	for(int i = 0 ; i<l ;i++)
	{
		if(text[i]=='\n')
			continue;
		frequency[text[i]]++;	
	}
	return frequency;
}
int computeAlphabet(int *frequency,char text[],char *letters)
{
	int l = strlen(text);
	int *duplicate = (int*)malloc(sizeof(int)*l);
	int j = 0;
	for(int i = 0 ; i <l ;i++)
	{
		if(text[i]=='\n')
			continue;
		if(frequency[text[i]]>=1 && duplicate[text[i]]==0)
		{
			letters[j] = text[i];
			++j;
			duplicate[text[i]] = 1;
		}
	}
	free(duplicate);
	return j;
}
int padOffset;
char * WriteOnText(struct character coded[], char text[] )
{
	int l = strlen(text);
	char *encoded = (char*)malloc(sizeof(int)*100000000);
	int k = 0;
	for(int i = 0 ; i<l; i++)
	{
		//printf("%c",text[i]);
		for(int j = 0 ; j<coded[text[i]].top;j++)
		{
			
			encoded[k] = coded[text[i]].code[j]+'0';
			k++;
			//printf("%d",coded[text[i]].code[j]);
		}
	}
	if(k%8!=0)
	{
		padOffset = 8 - (k % 8) ;
		int i = 0 ;
		while(i<padOffset)
		{
			encoded[k+i]='0';
			i++;
		}
	}
	
	
	return encoded;
}

/*static void decode(struct MinHeapNode *root,char *encoded,char *text)
{
	 FILE *fp2 = fopen("compressed","w");
	 struct MinHeapNode* curr = root;  
	 int l = strlen(encoded)-padOffset;
	 int k = 0 ; 
	 int no_of_lines=0;
    for (int i=0;i<l;i++) 
    {
        if (encoded[i] == '0') 
           curr = curr->left; 
        else
           curr = curr->right; 
 
        if (curr->left==NULL && curr->right==NULL) 
        { 
        	fputc(curr->data,fp2);
            curr = root;
            k++;
            if(text[k+no_of_lines]=='\n')
            {
            	// printf("\n"); 
            	no_of_lines++;
            }
        } 
    } 
} */
int cOffset;

int binToInt(const char *s) {
  return (int) strtol(s, NULL, 2);
}
char* BStoCS(char* binaryString){                               //converts the provided binary string to a character string, which can be written to the file.
	char* characterString = (char*)malloc(sizeof(char)*10000000);
	cOffset = 0;
	char tempBuffer[9];
	int lim = strlen(binaryString);
	tempBuffer[8] = '\0';
	for(int bOffset = 0;bOffset<lim;bOffset+=8){
		strncpy(tempBuffer,&binaryString[bOffset],8);
		characterString[cOffset++] = binToInt(tempBuffer)+'0';
	}
	characterString[cOffset] = '\0';
	int i = 0 ; 
	while(characterString[i]!='\0')
	{
		i++;
	}
	return characterString;

} 
char * intToBin(int i,int n)
{
	
    size_t bits = n;//sizeof(int) * CHAR_BIT;

    char * str = malloc(bits + 1);
    if(!str) return NULL;
    str[bits] = 0;
    if(i==0){
    	for(int i=0;i<n;i++)str[i] = '0';
    }
    // type punning because signed shift is implementation-defined
    unsigned u = *(unsigned *)&i;
    for(; bits--; u >>= 1)
        str[bits] = u & 1 ? '1' : '0';

    return str;
}


void huffman(char *text,char *outputFile)
{
	struct timespec start;
	struct timespec end;
	char *dest = (char*)malloc(sizeof(char)*100000000);
	int l = strlen(text);
	int *frequency = (int*)malloc(sizeof(int)*l);
	clock_gettime(CLOCK_REALTIME,&start);
	frequency = computeFrequency(text);
	char *letters = (char*)malloc(sizeof(char)*l);
	int x = computeAlphabet(frequency,text,letters);
	struct character* coded = (struct character*)malloc(sizeof(struct character)*10000);
	char *encoded;
	struct MinHeapNode *minHeap = HuffmanCodes(letters,frequency,x,coded);
	encoded = WriteOnText(coded,text);
	char *final;
	final=BStoCS(encoded);
	clock_gettime(CLOCK_REALTIME,&end);
	FILE *fp = fopen(outputFile,"wb");
	for(int i = 0 ; i < cOffset ;i++)
	{
		fprintf(fp,"%c",final[i]);
	}
	fclose(fp);
	printf("Compression factor %f\n",(float)cOffset/strlen(text));
	printf("Time taken: %lf\n", time_elapsed(&start, &end));
	char *binaryString = (char*)malloc(sizeof(char)*10000000);
	char * temp = (char*)malloc(sizeof(char)*8);
	int j = 0 ; 
	for(int i = 0 ; i < cOffset ; i++)
	{
		temp = intToBin(final[i]-'0',8);
		for(int k = 0 ; k < 8 ; k++)
		{
			binaryString[j]=temp[k];
			j++;
		}
	}

}
