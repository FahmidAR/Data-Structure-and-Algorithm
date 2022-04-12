#include<bits/stdc++.h>
using namespace std;

// Fahmid - 1705087_Four
//Binary Search Tree

#define dbg 0
#define dbgS 0
#define show 1
#define BLACK true
#define RED false

struct node
{
    int data ;
    bool color;
    node *left, *right, *parent ;
};

class BST{

     node *root;

    public:
        BST()
        {
            root=NULL;
        }
        ~BST()
        {
            destroyTree(root);
        }

        bool searchBoolBST(int key);
        void insertBST(int key);
        void deleteBst(int key);

        void rotateLeft(node *&);
        void rotateRight(node *&);
        void fixInsert(node *&);
        bool isBlack(node * temp)
        {
            return temp->color==BLACK||temp==NULL;
        }
        bool isRed(node * temp)
        {
            return temp->color==RED||temp!=NULL;
        }
        void fixDelete(int key,node * temp);
        void printBraketTree() {printBraketTree(root);}

        void inOrder() {inOrder(root);}
        void preOrder(){preOrder(root);}
        void postOrder(){postOrder(root);}

        void deleteBstRB(int key,node *&);
        node* deleteBstF(int key,node *&);

    private:

        void printBraketTree(node * temp);
        void inOrder(node * temp);
        void preOrder(node * temp);
        void postOrder(node * temp);
        void destroyTree(node * temp);
        void deleteBstR(int key,node * temp);
        node* minDataPoint(node* theNode);

};

void BST::destroyTree(node *theNode)
{
        if (theNode==NULL)
                return;

        node * curTreeNode = theNode;
        node * leftTreeNode = theNode->left;
        node * rightTreeNode = theNode->right;
        delete(curTreeNode);

        destroyTree(leftTreeNode);
        destroyTree(rightTreeNode);
}

node* BST::minDataPoint(node* theNode)
{
    node* temp=theNode;
   // cout<<"CX "<<temp->data<<endl;
    while(temp->left!=NULL)
    {
        temp=temp->left;
    }
    //cout<<"CX "<<temp->data<<endl;
    return temp;
}

void BST::printBraketTree(node * temp)
{
        if (temp==NULL)
                return;
        cout << temp->data << " : ";

        if(temp->color)
        {
            cout<<"b ";
        }
        else
        {
            cout<<"r ";
        }

        if(!temp->left&&!temp->right)
            return;

        cout<<"(";
        printBraketTree(temp->left);
        cout<<")";

        if(temp->right)
        {
        cout<<"(";
        printBraketTree(temp->right);
        cout<<")";
        }

}


void BST::preOrder(node * temp)
{
        if (temp==NULL)
                return;
        cout << temp->data << " ";
        preOrder(temp->left);
        preOrder(temp->right);
}


void BST::inOrder(node * temp)
{
        if (temp==NULL)
                return;
        inOrder(temp->left);
        cout << temp->data << " " ;
        inOrder(temp->right);
}

void BST::postOrder(node * temp)
{
        if (temp==NULL)
                return;
        postOrder(temp->left);
        postOrder(temp->right);
        cout << temp->data << " ";
}

void BST::deleteBst(int key)
{
    //printBraketTree();
    if(searchBoolBST(key))
    {
    //root=deleteBstF(key,root);
    node* temp=root;

    while(temp!=NULL)
    {
        if(temp->data==key)
        {
            deleteBstRB(key,temp);
            break;
        }
        else if(temp->data<key)
        {
            temp=temp->right;
        }
        else
        {
            temp=temp->left;
        }
    }
    }
}

void BST::deleteBstRB(int key,node *&temp)
{


    node *y;
    node *x;

    //if(temp->right!=NULL)cout<<temp->right->data<<endl;
    if(temp->left == NULL || temp->right == NULL) y = temp;
    else y = minDataPoint(temp->right);


    node *t;
    t->color=BLACK;

   // cout<<"sfs "<<y->data<<endl;
    if(y->left != NULL) x = y->left;
    else
    {
        x = y->right;
    }

    //cout<<"rfefe "<<temp->data<<endl;

    if(x!=NULL) x->parent = y->parent;
    else t=y->parent;

    //cout<<"rfefe5 "<<temp->data<<endl;

    if(y->parent == NULL) this->root = x;
    else if(y == y->parent->left) y->parent->left = x;
    else if(y == y->parent->right) y->parent->right = x;
//cout<<"sfs "<<y->data<<endl;
    if(y != temp)
    {
        temp->data = y->data;
        temp->color = y->color;
    }
   // cout<<"rfefe6 "<<temp->data<<endl;
    //cout<<"y "<<temp->data<<" x "<<x->data<<endl;

    if(y->color == BLACK && x!= NULL) fixDelete(x->data,x);
    else if (y->color == BLACK && x!= NULL) fixDelete(0,t);
//    return y;
}

node* BST::deleteBstF(int key,node *&temp)
{
    if(dbgS)
    {
        cout<<"welcome to delete normal = "<<key<<endl;
    }


    if(temp==NULL)
    {
        return temp;
    }
    if((temp->data)>key)
    {
        //cout<<"Miu"<<endl;
        temp->left=deleteBstF(key,temp->left);
    }
    else if((temp->data)<key)
    {
       // cout<<"Miu"<<endl;
        temp->right=deleteBstF(key,temp->right);
    }
    else
    {
        //cout<<"Miu"<<endl;
        if(temp->left==NULL&&temp->right==NULL)
        {

            node* temp2=temp->right;
            free(temp);
            return temp2;

        }
        if(temp->left==NULL)
        {
            node* temp2=temp->right;
            free(temp);
            return temp2;
        }
        else if(temp->right==NULL)
        {
            node* temp2=temp->left;
            free(temp);
            return temp2;
        }
        node* tempMin=minDataPoint(temp->right);
        temp->data=tempMin->data;
        temp->right=deleteBstF(tempMin->data,temp->right);
    }

    return temp;


}

void BST::fixDelete(int key,node* temp)
{
    if(dbgS)
    {
        cout<<"welcome to delete fix = "<<key<<endl;
    }

    node* sibling ;

    while(temp!=root&&isBlack(temp))
    {
        if(temp==temp->parent->left)
        {
            sibling=temp->parent->right;

            if(isRed(sibling))
            {
                //case 1
                sibling->color=BLACK;
                temp->parent->color=RED;
                rotateLeft(temp->parent);
                sibling=temp->parent->right;
            }
            if(isBlack(sibling->left)&&isBlack(sibling->right))
            {
                //case 2
                sibling->color=RED;
                temp=temp->parent;
            }
            else if(isBlack(sibling->right))
            {
                //case 3
                sibling->left->color=BLACK;
                sibling->color=RED;
                rotateRight(sibling);
                sibling=temp->parent->right;
                //case 4
                sibling->color=temp->parent->color;
                temp->parent->color=BLACK;
                sibling->right->color=BLACK;
                rotateLeft(temp->parent);
                temp=this->root;
            }
        }
        else
        {
            sibling=temp->parent->left;

            if(isRed(sibling))
            {
                //case 1
                sibling->color=BLACK;
                temp->parent->color=RED;
                rotateRight(temp->parent);
                sibling=temp->parent->left;
            }
             if(isBlack(sibling->left)&&isBlack(sibling->right))
            {
                //case 2
                sibling->color=RED;
                temp=temp->parent;
            }
            else if(isBlack(sibling->left))
            {
                //case 3
                sibling->right->color=BLACK;
                sibling->color=RED;
                rotateLeft(sibling);
                sibling=temp->parent->left;
                //case 4
                sibling->color=temp->parent->color;
                temp->parent->color=BLACK;
                sibling->left->color=BLACK;
                rotateRight(temp->parent);
                temp=this->root;
            }
        }
    }

    temp->color=BLACK;
}


bool BST::searchBoolBST(int key)
{
    node* temp=root;

    if(root==NULL){
        return false;
    }

    while(!((temp->data)==key))
    {
        if(temp->data< key)
        {
            if(temp->right==NULL)
            {
                if(dbg)
                    cout<<"### NOT Found in tree ="<<key<<endl;

                return false;
            }

            temp=temp->right;

            if(dbgS)
                cout<<"### NOW at ="<<temp->data<<endl;
        }

        if(temp->data > key)
        {
            if(temp->left==NULL)
            {
                if(dbg)
                    cout<<"### NOT Found in tree ="<<key<<endl;

                return false;
            }
            temp=temp->left;
            if(dbgS)
                cout<<"### NOW at ="<<temp->data<<endl;
        }

    }

    if(dbg)
        cout<<"### Found in tree ="<<key<<endl;

    return true;
}

void BST::rotateLeft(node *&wasUpper)
{
    node *waslowwer=wasUpper->right;

    wasUpper->right=waslowwer->left;

    if((wasUpper->right)!=NULL)
    {
        wasUpper->right->parent=wasUpper;
    }

    waslowwer->parent=wasUpper->parent;

    if( wasUpper->parent== NULL )
    {
        this->root=waslowwer;
    }
    else if(wasUpper->parent->right==wasUpper)
    {
        wasUpper->parent->right=waslowwer;
    }
    else
    {
        wasUpper->parent->left=waslowwer;
    }

    waslowwer->left=wasUpper;
    wasUpper->parent=waslowwer;

}
void BST::rotateRight(node *&wasUpper)
{
    node *waslowwer=wasUpper->left;

    wasUpper->left=waslowwer->right;

    if((wasUpper->left)!=NULL)
    {
        wasUpper->left->parent=wasUpper;
    }

    waslowwer->parent=wasUpper->parent;

    if( wasUpper->parent== NULL )
    {
        this->root=waslowwer;
    }
    else if(wasUpper->parent->left==wasUpper)
    {
        wasUpper->parent->left=waslowwer;
    }
    else
    {
        wasUpper->parent->right=waslowwer;
    }

    waslowwer->right=wasUpper;
    wasUpper->parent=waslowwer;
}

void BST::fixInsert(node *&now1)
{
    node *now=now1;

    if(dbgS)
    {
        cout<<"### welcome to isert fix => "<<now->data<<endl;
        cout<<"### welcome to isert color => "<<now->color<<endl;
    }



    while((now!=root)&&(now->color==RED)&&(now->parent->color==RED))
    {

       node *parent_now=now->parent;
       node *grand_p_now=now->parent->parent;

       if(parent_now==(grand_p_now->right))
       {
           //cout<<"meu"<<endl;

           node *uncle=grand_p_now->left;

           if((uncle!=NULL)&&(uncle->color==RED))
           {

                uncle->color=BLACK;
                parent_now->color=BLACK;
                grand_p_now->color=RED;
                now=grand_p_now;
                //if(now==root) cout<<"meu"<<endl;

           }
           else
           {


               if(now==parent_now->left)
               {
                   rotateRight(parent_now);
                   now=parent_now;
                   parent_now=now->parent;
               }

               bool c1=grand_p_now->color;
               bool c2=parent_now->color;

               grand_p_now->color=c2;
               parent_now->color=c1;

               rotateLeft(grand_p_now);

               now=parent_now;
           }

       }
       else
       {
           //cout<<"meu"<<endl;


           node *uncle=grand_p_now->right;

           if(uncle!=NULL&&uncle->color==RED)
           {
                uncle->color=BLACK;
                parent_now->color=BLACK;
                grand_p_now->color=RED;
                now=grand_p_now;

           }
           else
           {
               if(now==parent_now->right)
               {
                   rotateRight(parent_now);
                   now=parent_now;
                   parent_now=now->parent;
               }

               bool c1=grand_p_now->color;
               bool c2=parent_now->color;

               grand_p_now->color=c2;
               parent_now->color=c1;

               rotateLeft(grand_p_now);

               now=parent_now;
           }

       }
    }

    this->root->color=BLACK;
}

void BST::insertBST(int key)
{
    node* newNode=new node;
    newNode->data=key;
    newNode->left=NULL;
    newNode->right=NULL;
    newNode->parent=NULL;
    newNode->color=RED;

    if(root==NULL)
    {
     root=newNode;
     fixInsert(root);

     if(dbg)
            cout<<" ## Suceesflly inserted in root ="<<newNode->data<<endl;
    }
    else
    {
        if(!searchBoolBST(key))
        {
            node *temp=root;

            while(temp!=NULL)
            {
                if(temp->data< key){

                    if(temp->right==NULL)
                    {
                         newNode->parent=temp;
                         temp->right=newNode;
                         fixInsert(temp->right);

                         if(dbg)
                            cout<<" ## Suceesflly inserted in tree ="<<newNode->data<<endl;
                        break;
                    }
                    temp=temp->right;
                }

                if(temp->data > key)
                {
                    if(temp->left==NULL)
                    {
                        newNode->parent=temp;
                        temp->left=newNode;
                        fixInsert(temp->left);

                         if(dbg)
                            cout<<" ## Suceesflly inserted in tree ="<<newNode->data<<endl;
                        break;
                    }

                    temp=temp->left;
                }
            }

        }



    }
}



int main()
{



    int  m=0, input;

    int node;
    char command;

    BST b1;

    ifstream inFile;

    inFile.open("input.txt");

    if (!inFile)
    {
        cout << "\nError occurs while opening file.\n";
        return 1;
    }



    while(inFile>>command>>node)
    {
        cout<<command<<" "<<node<<endl;

        if(command=='I')
        {
            //cout<<"# Ilish #"<<endl;

            b1.insertBST(node);

            cout<<"Tree = ";
            b1.printBraketTree();
            //b1.preOrder();
            cout<<endl;
        }
        else if(command=='F')
        {
            //cout<<"# Fuska #"<<endl;

            if(b1.searchBoolBST(node))
            {
                cout<<"True"<<endl;
            }
            else
            {
                cout<<"False"<<endl;
            }
        }
        else if(command=='D')
        {
            //cout<<"# Doi #"<<endl
             b1.deleteBst(node);

            cout<<"Tree = ";
            b1.printBraketTree();
            cout<<endl;
        }
    }

    inFile.close();



return 0;

}
