#include "hbt.h"
#include "pa4.h"
#include "build.h"

//evaluation of trees
int evaluate(char* filename, Tnode* root)
{
    int bstScore = 1;
    int avlEval = 1;

    FILE* fh = fopen(filename, "rb");

    if(fh == NULL)
    {
        fprintf(stderr, "file to eval failed to open\n");
        return -1;
    }

    int formatScore = 1;

    root = buildFromFile(fh, &formatScore);
    getBalance(root, &avlEval);
    bstEval(root, &bstScore);
    fprintf(stdout, "%d,%d,%d\n", formatScore, bstScore, avlEval);
    destroyTree(root);
    fclose(fh);
    
    return EXIT_SUCCESS;
}

//gets the balance of each node in the tree
void getBalance(Tnode* root, int* balanceScore)
{
    
    if(root == NULL)
        return;

    int leftHeight = getHeight(root -> left);
    int rightHeight = getHeight(root -> right);

    int balance = leftHeight - rightHeight;
    fprintf(stderr, "balance\n");
    root -> balance = balance;
    if(balance > 1 || balance < -1)
    {
        *balanceScore = 0;
    }
    return;
}

//get Balance without score
void getBalanceNS(Tnode* root)
{
    if(root == NULL)
        return;

    int leftHeight = getHeight(root -> left);
    int rightHeight = getHeight(root -> right);

    int balance = leftHeight - rightHeight;
    fprintf(stderr, "balance\n");
    root -> balance = balance;
    return;
}


//gets the height of the passed node
int getHeight(Tnode* root)
{
    if(root == NULL)
        return 0;

    int heightLeft = getHeight(root -> left);
    int heightRight = getHeight(root -> right);

    int prevHeight = heightLeft > heightRight ? heightLeft : heightRight; 
    return 1 + prevHeight;
}

void bstEval(Tnode* root, int* bstScore)
{   
    if(root == NULL)
    {
        return;
    }
    // fprintf(stderr, "root -> key: %d\n", root -> key);
    if(root -> left != NULL)
    {
        *bstScore = (root -> left) -> key <= root -> key ? (*bstScore) : 0; 
    }
    if(root -> right != NULL)
    {
        *bstScore = (root -> right) -> key > root -> key ? (*bstScore) : 0;
    }
    bstEval(root -> left, bstScore);
    bstEval(root -> right, bstScore);
    return;
}