#define WS 100000
#define LAB 50000
#define SB WS-LAB

typedef struct node
{
    char ch;
    struct node *next;
}NODE;

typedef struct
{
    NODE *root;
}LIST;

void lz78_encoding(char* text);
void lz78_decoding();

LIST* create_LIST();
NODE* append_LIST(NODE *root, NODE *root2, char ch);

NODE* create_NODE(char ch);
void destroy_NODE_from(NODE *n);

NODE* insert_NODE(NODE *root, char ch);
