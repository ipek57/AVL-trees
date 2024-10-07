#include <stdio.h>
#include <stdlib.h>

struct AVLtreeNode{
    struct AVLtreeNode *left;
    int data;
    struct AVLtreeNode *right;
    int height;
};

struct AVLtreeNode *root = NULL;

int heightcalculation(struct AVLtreeNode *ptr){
    if(ptr == NULL){
        return 0;
    }
    return ptr->height;
}

struct AVLtreeNode *createAVLtree(int data){
    struct AVLtreeNode *newnode = (struct AVLtreeNode *)malloc(sizeof(struct AVLtreeNode));
    newnode->data = data;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->height = 1;
    return newnode;
}

int maxmin(int x, int y){
    return (x > y) ? x : y;
}

int balance_factor(struct AVLtreeNode *ptr){
    if(ptr == NULL){
        return 0;
    }
    return heightcalculation(ptr->left) - heightcalculation(ptr->right);
}

struct AVLtreeNode *Rrotation(struct AVLtreeNode *b){
    struct AVLtreeNode *a = b->left;
    struct AVLtreeNode *c = a->right;
    
    a->right = b;
    b->left = c;
    
    b->height = maxmin(heightcalculation(b->left), heightcalculation(b->right)) + 1;
    a->height = maxmin(heightcalculation(a->left), heightcalculation(a->right)) + 1;
    
    return a;
}

struct AVLtreeNode *Lrotation(struct AVLtreeNode *a){
    struct AVLtreeNode *b = a->right;
    struct AVLtreeNode *c = b->left;
    
    b->left = a;
    a->right = c;
    
    a->height = maxmin(heightcalculation(a->left), heightcalculation(a->right)) + 1;
    b->height = maxmin(heightcalculation(b->left), heightcalculation(b->right)) + 1;
    
    return b;
}

struct AVLtreeNode *insertNode(struct AVLtreeNode *ptr, int data){
    if(ptr == NULL){
        return createAVLtree(data);
    }
    if(data < ptr->data){
        ptr->left = insertNode(ptr->left, data);
    }else if(data > ptr->data){
        ptr->right = insertNode(ptr->right, data);
    }else{
        return ptr;  
    }

    ptr->height = 1 + maxmin(heightcalculation(ptr->left), heightcalculation(ptr->right));

    int balancef = balance_factor(ptr);

    // LL durumu
    if(balancef > 1 && data < ptr->left->data){
        return Rrotation(ptr);
    }

    // RR durumu
    if(balancef < -1 && data > ptr->right->data){
        return Lrotation(ptr);
    }

    // LR durumu
    if(balancef > 1 && data > ptr->left->data){
        ptr->left = Lrotation(ptr->left);
        return Rrotation(ptr);
    }

    // RL durumu
    if(balancef < -1 && data < ptr->right->data){
        ptr->right = Rrotation(ptr->right);
        return Lrotation(ptr);
    }
    return ptr;
}

void inOrderTraversal(struct AVLtreeNode *root){
    if(root != NULL){
        inOrderTraversal(root->left);
        printf("%d\n", root->data);
        inOrderTraversal(root->right);
    }
}

void displayNodeDetails(struct AVLtreeNode *node, struct AVLtreeNode *parent, char side) {
    int balancef = balance_factor(node);
    if (parent == NULL) {
        printf("%d (%d B) ", node->data, balancef);
    } else {
        printf("%d (%d %c) (%d B) ", node->data, parent->data, side, balancef);
    }
}

void displayCurrentLevel(struct AVLtreeNode *root, int level, struct AVLtreeNode *parent, char side) {
    if (root == NULL)
        return;
    if (level == 1)
        displayNodeDetails(root, parent, side);
    else if (level > 1) {
        displayCurrentLevel(root->left, level-1, root, 'L');
        displayCurrentLevel(root->right, level-1, root, 'R');
    }
}

int treeHeight(struct AVLtreeNode *node) {
    if (node == NULL)
        return 0;
    return 1 + maxmin(treeHeight(node->left), treeHeight(node->right));
}

void displayLevelOrder(struct AVLtreeNode *root) {
    int h = treeHeight(root);
    int i;
    for (i = 1; i <= h; i++) {
        displayCurrentLevel(root, i, NULL, ' ');
        printf("\n");
    }
}

int main(){
    int n;
    while(1){
        scanf("%d", &n);
        if(n == -1){
            break;
        }
        root = insertNode(root, n);
    }
    inOrderTraversal(root);
    printf("\n");

    displayLevelOrder(root);

    return 0;
}
