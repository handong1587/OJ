#include <stdio.h>
#include <iostream>
using namespace std;

#define _abs_(a) ((a)<0?-(a):(a))
#define _min_(a,b) ((a)<(b)?(a):(b))
#define _max_(a,b) ((a)>(b)?(a):(b))

int T;
#define MAXV 10005
int res_d, res_size;

struct Node
{
    Node *parent;
    Node *left;
    Node *right;
    int d;
};

struct VerticePairs
{
    int left;
    int right;
};

VerticePairs v_pairs[MAXV];

void init()
{
    for (int i = 0; i < MAXV; i++){
        v_pairs[i].left = 0;
        v_pairs[i].right = 0;
    }
}

int size(Node *root)
{
    if(root==NULL){
        return 0;
    }
    if(root->left==NULL && root->right==NULL){
        return 1;
    }
    int left_size=size(root->left);
    int right_size=size(root->right);
    return left_size + right_size+1;
}

Node *find(Node* root, int d)
{
    if(root==NULL){
         return NULL;
    }
    if(root->d == d){
        return root;
    }
    Node *left=NULL;
    Node *right=NULL;
    if(root->left != NULL){
        left=find(root->left,d);
    }
    if(root->right!= NULL){
        right=find(root->right,d);
    }
    if(left!=NULL){
         return left;
    }
    if(right!=NULL){
        return right;
    }
    return NULL;
}

void insert(Node* root, int par, int chd)
{
    Node* node = find(root, par);
    Node* new_node = new Node;
    new_node->parent = node;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->d = chd;

    if (node->left == NULL){
        node->left = new_node;
    }
    else{
        node->right = new_node;
    }
}

void insertNode(Node *root, int par)
{
    if (v_pairs[par].left > 0){
        insert(root, par, v_pairs[par].left);
        insertNode(root, v_pairs[par].left);
    }
    if (v_pairs[par].right > 0){
        insert(root, par, v_pairs[par].right);
        insertNode(root, v_pairs[par].right);
    }
}

void freeNode(Node *root)
{
    if(root==NULL){
        return;
    }
    if (root->left != NULL){
        freeNode(root->left);
    }
    if (root->right != NULL){
        freeNode(root->right);
    }
    delete root;
}

int distToRoot(Node* root, int v)
{
    int dist=0;
    Node *vnode=find(root, v);
    while(vnode->parent != root){
        vnode = vnode->parent;
        dist++;
    }
    return dist;
}

void solve(Node* root, int v1, int v2)
{
    int dist1=distToRoot(root,v1);
    int dist2=distToRoot(root,v2);
    int diff = _abs_(dist1-dist2);

    Node* node1=find(root,v1);
    Node* node2=find(root,v2);
    if(dist1 > dist2){
        while(diff > 0){
            node1=node1->parent;
            diff--;
        }
    }else {
        while(diff > 0){
            node2=node2->parent;
            diff--;
        }
    }
    Node* common_ancestor = NULL;
    if(node1->parent == node2->parent){
         common_ancestor = node1->parent;
    }else{
        while(node1->parent != node2->parent){
            node1=node1->parent;
            node2=node2->parent;
        }
        if (node1->parent == node2->parent){
            common_ancestor = node1->parent;
        }
    }
    res_d = common_ancestor->d;
    res_size = size(common_ancestor);
}

int main()
{
    freopen("Common_Ancestor_in_Tree.txt","r",stdin);
    scanf("%d", &T);
    for(int t=1;t<=T;t++){
        init();

        int V,E,v1,v2;
        scanf("%d %d %d %d",&V,&E,&v1,&v2);

        Node *root = new Node;
        root->parent = NULL;
        root->left = NULL;
        root->right = NULL;
        root->d = 1;

        for(int e=0;e<E;e++){
            int e1,e2;
            scanf("%d %d",&e1,&e2);

            if (v_pairs[e1].left == 0){
                v_pairs[e1].left = e2;
            }
            else{
                v_pairs[e1].right = e2;
            }
        }

        insertNode(root, 1);

        res_d = 0;
        res_size = 0;
        solve(root, v1, v2);

        printf("#%d %d %d\n",t, res_d, res_size);

        freeNode(root);
    }
    return 0;
}
