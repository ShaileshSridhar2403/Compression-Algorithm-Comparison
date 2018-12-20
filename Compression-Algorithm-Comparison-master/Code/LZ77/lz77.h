#define WS 100000
#define LAB 50000
#define SB WS-LAB

typedef struct node
{
    char ch;
    struct node *left;
    struct node *right;
}NODE;

typedef struct
{
    NODE *root;
}DLL;

void lz77_encoding(char* text);
void lz77_decoding();

DLL* create_DLL(DLL *dll);
NODE* create_NODE(char ch);
void destroy_NODE_from(NODE *n);

NODE* insert_NODE_right(NODE *root, char ch);
NODE* insert_NODE_left(NODE *root, char ch);
