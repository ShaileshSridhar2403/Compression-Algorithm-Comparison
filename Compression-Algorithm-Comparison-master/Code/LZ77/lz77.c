#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define WS 100000
#define LAB 50000
#define SB WS-LAB

typedef struct lnode
{
    char ch;
    struct lnode *left;
    struct lnode *right;
}LNODE;

typedef struct
{
    LNODE *root;
}DLL;


DLL* create_DLL(DLL *dll);
LNODE* create_NODE(char ch);
void destroy_NODE_from(LNODE *n);

LNODE* insert_NODE_right(LNODE *root, char ch);
LNODE* insert_NODE_left(LNODE *root, char ch);

void lz77_encoding(char* text,char *outputFile)
{
    FILE *fp = fopen(outputFile, "w");
    
    int i;
    int sb, sb2;                    /* search buffer index */
    int p=0;                        /* index of input text */
    int len_longest_match, len;
    int len_of_text = strlen(text);
    
    char ch, ch2;                   /* char which did not match */
    
    LNODE *n;
    
    DLL *start = NULL;
    DLL *search = NULL;
    DLL *lookahead = NULL;
    DLL *end = NULL;
    
    start = create_DLL(start);
    search = create_DLL(search);
    lookahead = create_DLL(lookahead);
    end = create_DLL(end);
    
    for(i=1; i<=SB; ++i)
        start->root = insert_NODE_right(start->root, '\0');
    
    for(i=1; i<=LAB; ++i)
    {
        if(p<len_of_text)
            lookahead->root = insert_NODE_right(lookahead->root, text[p++]);
        else
            lookahead->root = insert_NODE_right(lookahead->root, '\0');
    }
    
    n = start->root;
    while(n->right!=NULL)
        n = n->right;
    search->root = n;
    
    search->root->right = lookahead->root;
    lookahead->root->left = search->root;
    
    n = lookahead->root;
    while(n->right!=NULL)
        n = n->right;
    end->root = n;
    
    LNODE *look, *l;
    LNODE *see, *s;
    
    while(lookahead->root->ch != '\0')
    {
        look = lookahead->root;
        see = search->root;
        len_longest_match = 0;
        sb = sb2 = 0;
        ch = ch2 = look->ch;
        
        while(see!=NULL && see->ch!='\0' && look!=NULL && look->ch!='\0' && sb2<SB)
        {
            l = look;
            s = see;
            len = 0;
            
            while(len<LAB && look->ch==see->ch)
            {
                ++len;
                if(look->right!=NULL)
                    ch2 = look->right->ch;
                else if(p<len_of_text)
                    ch2 = text[p];
                else
                    ch2 = '\0';
                look = look->right;
                see = see->right;
            }

            if(len > len_longest_match)
            {
                len_longest_match = len;
                ch = ch2;
                sb = sb2+1;
            }
            
            ++sb2;
            look = l;
            see = s;
            see = see->left;
        }
        
        fprintf(fp, "%d,%d,%c\n", sb, len_longest_match, ch);
        
        for(i=0; i<=len_longest_match; ++i)
        {
            start->root = start->root->right;
            free(start->root->left);
            search->root = search->root->right;
            lookahead->root = lookahead->root->right;
            if(p<len_of_text)
                end->root->right = create_NODE(text[p++]);
            else
                end->root->right = create_NODE('\0');
            end->root->right->left = end->root;
            end->root = end->root->right;
        }
    }
    
    fclose(fp);
    
    destroy_NODE_from(start->root);
    free(start);
    free(search);
    free(lookahead);
    free(end);
}

void lz77_decoding()
{
    FILE *fp_orig = fopen("output/original.txt", "w");
    FILE *fp_comp = fopen("output/compressed.txt", "r");
    
    int i;
    int length;
    int num1, num2;
    char ch;
    
    fseek (fp_comp, 0, SEEK_END);
    length = ftell (fp_comp);
    fseek (fp_comp, 0, SEEK_SET);
    
    LNODE *n;
    
    DLL *start = NULL;
    DLL *search = NULL;
    
    start = create_DLL(start);
    search = create_DLL(search);
    
    for(i=1; i<=SB; ++i)
        start->root = insert_NODE_right(start->root, '\0');
    
    n = start->root;
    while(n->right!=NULL)
        n = n->right;
    search->root = n;
    
    while(!feof(fp_comp))
    {
        fscanf(fp_comp, "%d,%d,%c\n", &num1, &num2, &ch);
        
        if(num1==0)
        {
            fprintf(fp_orig, "%c", ch);
            
            search->root->right = create_NODE(ch);
            search->root->right->left = search->root;
            search->root = search->root->right;
            
            start->root = start->root->right;
            free(start->root->left);
            start->root->left = NULL;
        }
        else
        {
            n = search->root;
            for(i=1; i<num1; ++i)
                n = n->left;
            
            for(i=0; i<num2; ++i)
            {
                fprintf(fp_orig, "%c", n->ch);

                search->root->right = create_NODE(n->ch);
                search->root->right->left = search->root;
                search->root = search->root->right;
                
                start->root = start->root->right;
                free(start->root->left);
                start->root->left = NULL;
                
                n = n->right;
            }
            
            fprintf(fp_orig, "%c", ch);
            search->root->right = create_NODE(ch);
            search->root->right->left = search->root;
            search->root = search->root->right;
            
            start->root = start->root->right;
            free(start->root->left);
            start->root->left = NULL;
        }
    }
}

DLL* create_DLL(DLL *dll)
{
    dll = (DLL*)malloc(sizeof(DLL));
    dll->root = NULL;
    return dll;
}

LNODE* create_NODE(char ch)
{
    LNODE *n;
    n = (LNODE*)malloc(sizeof(LNODE));
    n->ch = ch;
    n->right = n->left = NULL;
    return n;
}

void destroy_NODE_from(LNODE *n)
{
    if(n==NULL)
        return;

    LNODE *n1;
    n1 = n->right;
    free(n);
    destroy_NODE_from(n1);
}

LNODE* insert_NODE_right(LNODE *root, char ch)
{
    if(root==NULL)
        return create_NODE(ch);
    
    LNODE *r = root;
    
    while(root->right!=NULL)
        root = root->right;
    
    root->right = create_NODE(ch);
    root->right->left = root;
    
    return r;
}
