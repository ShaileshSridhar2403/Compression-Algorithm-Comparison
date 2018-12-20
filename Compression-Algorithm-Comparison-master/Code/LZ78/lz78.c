#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct l8node
{
    char ch;
    struct l8node *next;
}L8NODE;

typedef struct
{
    L8NODE *root;
}LIST;

LIST* create_LIST();
L8NODE* append_LIST(L8NODE *root, L8NODE *root2, char ch);

L8NODE* create_LNODE(char ch);
void destroy_LNODE_from(L8NODE *n);

L8NODE* insert_LNODE(L8NODE *root, char ch);

void lz78_encoding(char* text,char *outputFile)
{
    FILE *fp = fopen(outputFile, "w");
    
    int t, t1;
    int len_of_text = strlen(text);
    
    LIST **list;
    list = (LIST**)malloc(len_of_text * sizeof(LIST));
    for(t=0; t<len_of_text; ++t)
        list[t] = create_LIST();
    
    L8NODE *r;
    
    int flag;
    int l, L=0;                        /* number of lists made */
    
    t=0;
    while(t < len_of_text)
    {
        flag=0;
        
        for(l=L-1; l>=0; --l)
        {
            r = list[l]->root;
            t1 = t;
            while(r!=NULL && t < len_of_text && text[t]==r->ch)
            {
                ++t;
                r = r->next;
            }
            
            if(r==NULL)
            {
                fprintf(fp, "%d,%c\n", l+1, text[t]);
                
                /* append in list of lists */
                if(t < len_of_text)
                    list[L]->root = append_LIST(list[L]->root, list[l]->root, text[t]);
                else
                    list[L]->root = append_LIST(list[L]->root, list[l]->root, '\0');
                
                ++L;
                ++t;
                
                flag=1;
                break;
            }
            else
                t = t1;
        }
        
        if(flag==0)
        {
            fprintf(fp, "%d,%c\n", 0, text[t]);
            
            /* append in list of lists */
            list[L]->root = append_LIST(list[L]->root, NULL, text[t]);
            
            ++L;
            ++t;
        }
    }
    
    fclose(fp);
    
    for(t=0; t<len_of_text; ++t)
    {
        destroy_LNODE_from(list[t]->root);
        free(list[t]);
    }
    free(list);
}

void lz78_decoding()
{
    FILE *fp_orig = fopen("output/original.txt", "w");
    FILE *fp_comp = fopen("output/compressed.txt", "r");
    
    int length;                                 /* length of compressed file */
    int num;
    char ch;
    
    fseek (fp_comp, 0, SEEK_END);
    length = ftell (fp_comp);
    fseek (fp_comp, 0, SEEK_SET);
    
    int i;
    
    LIST **list;
    list = (LIST**)malloc(length * sizeof(LIST));
    for(i=0; i<length; ++i)
        list[i] = create_LIST();
    
    L8NODE *r;
    
    int L=0;                        /* number of lists made */
    
    while(!feof(fp_comp))
    {
        fscanf(fp_comp, "%d,%c\n", &num, &ch);
        
        if(num==0)
        {
            fprintf(fp_orig, "%c", ch);
            list[L]->root = append_LIST(list[L]->root, NULL, ch);
            ++L;
        }
        else
        {
            list[L]->root = append_LIST(list[L]->root, list[num-1]->root, ch);
            
            r = list[L]->root;
            
            fprintf(fp_orig, "%c", r->ch);
            while(r->next != NULL)
            {
                fprintf(fp_orig, "%c", r->next->ch);
                r = r->next;
            }
            
            ++L;
        }
    }
    
    fclose(fp_orig);
    fclose(fp_comp);
    
    for(i=0; i<length; ++i)
    {
        destroy_LNODE_from(list[i]->root);
        free(list[i]);
    }
    free(list);
}

LIST* create_LIST()
{
    LIST *list;
    list = (LIST*)malloc(sizeof(LIST));
    list->root = NULL;
    return list;
}

L8NODE* create_LNODE(char ch)
{
    L8NODE *n;
    n = (L8NODE*)malloc(sizeof(L8NODE));
    n->ch = ch;
    n->next = NULL;
    return n;
}

L8NODE* append_LIST(L8NODE *root, L8NODE *root2, char ch)
{
    if(root2==NULL)
        return create_LNODE(ch);
    
    root = create_LNODE(root2->ch);
    
    L8NODE *r1 = root;
    L8NODE *r2 = root2;
    while(r2->next != NULL)
    {
        r1->next = create_LNODE(r2->next->ch);
        r1 = r1->next;
        r2 = r2->next;
    }
    if(ch != '\0')
        r1->next = create_LNODE(ch);
    
    return root;
}

void destroy_LNODE_from(L8NODE *n)
{
    if(n==NULL)
        return;

    L8NODE *n1;
    n1 = n->next;
    free(n);
    destroy_LNODE_from(n1);
}

L8NODE* insert_LNODE(L8NODE *root, char ch)
{
    if(root==NULL)
        return create_LNODE(ch);
    
    L8NODE *r = root;
    
    while(root->next!=NULL)
        root = root->next;
    
    root->next = create_LNODE(ch);
    
    return r;
}
