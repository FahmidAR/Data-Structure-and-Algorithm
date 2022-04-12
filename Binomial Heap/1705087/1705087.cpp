#include<bits/stdc++.h>
using namespace std;

// Fahmid - 1705087_Four
//Binary Search Tree

#define dbgT 0


struct node
{
    int data ,degree ,level ;
    node *sibling, *child, *parent ;
};

node* mergeBH(node * first,node * second);
node* unionBH(node * first,node * second);

class BH{

     node *root;

    public:
        BH()
        {
            root=NULL;
        }
        ~BH()
        {
            //destroyTree(root);
        }

        node* findMin();
        node* ectractMin();
        void insertBH(int key);
        node*blinkBH(node * low,node * up);

        void printBH();
        node* headNode()
        {
            return root;
        }
        void setHeadNode(node* temp)
        {
            this->root=temp;
        }


};

void BH::printBH()
{
    cout<<"Printing Binomial Heap..."<<endl;
    node* travR=root;
    int level=0;
    int currect=0;

    while(travR!=NULL)
    {
       cout<<"Binomial Tree, B"<<travR->degree;

       level=0;
       int currect=0;
       queue<node*> q;
       queue<int> c;

       q.push(travR);
       c.push(level);

       while(!q.empty())
       {
            if(level==c.front())
            {
                currect=currect+1;
                cout<<"\nLevel "<<currect-1<<" : ";

            }
            node* tempL=q.front();
            q.pop();
            c.pop();
            cout<<tempL->data<<" ";

            if(tempL->child!=NULL)
            {
                node* tempD=tempL->child;
                level=level+1;
                while(tempD!=NULL)
                {
                    q.push(tempD);
                    c.push(level);
                    tempD=tempD->sibling;
                }
            }
       }


       travR=travR->sibling;
       cout<<endl;
    }
}

node* BH::ectractMin()
{

    node* prev=NULL ;
    node* current=NULL;

    node* preTra=NULL;
    node* traverse=root;


    int minData=INT_MAX;

    while(traverse!=NULL)
    {
        if(traverse->data<minData)
        {
            minData=traverse->data;
            prev=preTra;
            current=traverse;
        }
        preTra=traverse;
        traverse=traverse->sibling;
    }

    if(prev!=NULL)
    {
        prev->sibling=current->sibling;
    }
    else
    {
        if(current->sibling==NULL)
        {
            this->root=NULL;
        }
    }

    node* childMin=current->child;
    stack<node*> s;

    while(childMin!=NULL)
    {
        childMin->parent=NULL;
        s.push(childMin);
        cout<<" Baccha "<<childMin->data<<endl;
        childMin=childMin->sibling;
    }

    //current->child=NULL;

    traverse=s.top();

    node* temp=traverse;
    //cout<<" Baccha "<<traverse->data<<endl;

    s.pop();

    while(!s.empty())
    {
        traverse->sibling=s.top();
        s.pop();
        traverse=traverse->sibling;
    }

    traverse->sibling=NULL;
    //cout<<" Baccha jar hobe she root "<<root->data<<endl;

    cout<<"Extract-Min returned "<<current->data<<endl;

    if(temp!=NULL)
    {
        if(this->root==NULL)
        {
            this->root=temp;
        }
        else
        {
            this->root=unionBH(this->root,temp);
        }
    }

    return current;


}

void BH::insertBH(int key)
{
	node* newNode=new node;
	newNode->data = key;
	newNode->degree =newNode->level= 0;
	newNode->child=newNode->parent=newNode->sibling=NULL;

	if(dbgT)
    {
        cout<<" inserted <<"<<key<<endl;
        if(this->root)
        {
            cout<<" root <<"<<this->root->data<<endl;
        }
    }

    if(this->root==NULL) this->root=newNode;
    else this->root=unionBH(this->root,newNode);

    if(dbgT)
    {
        cout<<" root <<"<<this->root->data<<endl;
    }
}

node* BH::findMin()
{
    node* current=NULL;
    node* traverse=root;

    int minData=INT_MAX;

    while(traverse!=NULL)
    {
        if(traverse->data<minData)
        {
            minData=traverse->data;
            current=traverse;
        }
        traverse=traverse->sibling;
    }
    cout<<"Find-Min returned  "<<current->data<<endl;

    return current;
}

node* blinkBH(node * low,node * up)
{
    if(low->data>up->data)
    {
        low->parent=up;
        low->sibling=up->child;
        up->child=low;
        up->degree=up->degree+1;
        return up;

    }
    else
    {
        up->parent=low;
        up->sibling=low->child;
        low->child=up;
        low->degree=low->degree+1;
        return low;
    }

}

node* mergeBH(node * first,node * second)
{
    node* tempA=first;
    node* tempB=second;
    node* head;

    if(dbgT)
    {
        cout<<" mereged 1 <<"<<first->data<<endl;
        cout<<" mereged 2 <<"<<second->data<<endl;
    }


    if(first==NULL) return second;
    if(second==NULL) return first;

    if(first->degree<second->degree)
    {
        head=tempA;
        tempA=tempA->sibling;
    }
    else
    {
        head=tempB;
        tempB=tempB->sibling;
    }

    while(tempA!=NULL&&tempB!=NULL)
    {
        if(first->degree<second->degree)
        {
            head->sibling=tempA;
            tempA=tempA->sibling;
        }
        else
        {
            head->sibling=tempB;
            tempB=tempB->sibling;
        }
        head=head->sibling;
    }

    if(tempA==NULL)
    {
        head->sibling=tempB;
    }
    else
    {
        head->sibling=tempA;
    }

    return head;

}

node* unionBH(node * first,node * second)
{
    if(dbgT)
    {
        cout<<" union 1 <<"<<first->data<<endl;
        cout<<" union 2 <<"<<second->data<<endl;
    }

    node* headN=mergeBH(first,second);


    if(dbgT)
    {
        node* temp=headN;

        while(temp!=NULL)
        {
            cout<<" HUII "<<temp->data<<endl;
            temp=temp->sibling;
        }
    }
    first=second=NULL;

    if(headN==NULL) return NULL;

    node* prev=NULL;
    node* now=headN;
    node* next=headN->sibling;

    while(next!=NULL)
    {
        //CASE 1 2 3 4
        if(now->degree!=next->degree)
        {
            prev=now;
            now=next;
        }
        else if(next->sibling!=NULL&&now->degree==next->sibling->degree)
        {
            prev=now;
            now=next;
        }
        else
        {
            if(now->data<next->data)
            {
                now->sibling=next->sibling;
                next->parent=now;
                next->sibling=now->child;
                now->child=next;
                now->degree=now->degree+1;
            }
            else
            {
                if(prev)
                {
                    prev->sibling=next;
                }
                else
                {
                    headN=next;
                }

                now->parent=next;
                now->sibling=next->child;
                next->child=now;
                next->degree=next->degree+1;
                now=next;
            }
        }

        next=next->sibling;

    }

    return headN;
}



int main()
{



    int  m=0, input;

    int node;
    char command;

    BH b1;

    ifstream inFile;

    inFile.open("input.txt");

    if (!inFile)
    {
        cout << "\nError occurs while opening file.\n";
        return 1;
    }



    while(inFile>>command)
    {
        //cout<<command<<endl;

        if(command=='I')
        {
            //cout<<"# Ilish #"<<endl;
            inFile>>node;
            b1.insertBH(node);
            //cout<<node<<endl;

        }
        else if(command=='F')
        {
            //cout<<"# Fuska #"<<endl;
            b1.findMin();

            //cout<<"True"<<endl;
        }
        else if(command=='E')
        {
            //cout<<"# eDoi #"<<endl;
            b1.ectractMin();
        }
        else if(command=='P')
        {
            //cout<<"# Polashi #"<<endl;
            b1.printBH();
        }
        else if(command=='U')
        {
           //cout<<"# UNO #"<<endl;
           BH b2;

           while(inFile>>node)
           {
                //cout<<node<<" "<<endl;
                b2.insertBH(node);
                if (inFile.peek() == '\n') break;
           }
           //b2.printBH();
           b1.setHeadNode(unionBH(b1.headNode(),b2.headNode()));
        }
    }

    inFile.close();



return 0;

}


