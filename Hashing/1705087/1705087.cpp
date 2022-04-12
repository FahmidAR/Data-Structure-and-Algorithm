#include<bits/stdc++.h>

using namespace std;

#define DEBUG 0
#define WSHOW 0

#define TSIZE 10007
#define WSIZE 7

#define RWSIZE 5
#define RSWSIZE 3

#define PRIME 13
#define PRIME2 11

#define HF 1
#define C1 3
#define C2 7
#define K 13

string rWord()
{
    char alphabet[26] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g',
                          'h', 'i', 'j', 'k', 'l', 'm', 'n',
                          'o', 'p', 'q', 'r', 's', 't', 'u',
                          'v', 'w', 'x', 'y', 'z' };
    //srand (time(NULL));

    string temp = "";

    for (int i = 0; i < WSIZE; i++)
    {
        temp = temp + alphabet[rand() % 26];
    }

    return temp;
}

int stringToKey(string s)
{
    int key=PRIME;
    for(int i=0; s[i] ;i++)
    {
        //cout<<s[i]<<endl;
        key = (key)*K+s[i];
    }

    //cout<<key<<endl;
    return key;
}

class HashNode
{

    public:

    string key;
    int ind;

	HashNode* next;

    HashNode(int ind, string key)
    {

        this->key = key;
        this->ind = ind;
        this->next = NULL;
    }

};

class HashTableChain
{
    HashNode** hashTableL;
    int curentSizeL;
    int collisionL=0;
    int probL=1;

    public:



    HashTableChain()
    {

        hashTableL = new HashNode*[TSIZE];
        this->curentSizeL=0;

        for (int i = 0; i < TSIZE; i++)
        {
            hashTableL[i] = NULL;
        }
    }

    void insertHash(string key);
    bool searchHash(string key);
    void deleteHash(string key);
    void printHash();

    ~HashTableChain()
    {

    for (int i = 0; i < TSIZE; i++)

    {

        HashNode* entryN = hashTableL[i];

        while (entryN != NULL)

        {

            HashNode* prev = entryN;

            entryN = entryN->next;

            delete prev;

        }

        delete[] hashTableL;

    }
    }
    int hashOne(string key)
    {
        int keyI=stringToKey(key);
        if(HF==1)
        {
            return (keyI % TSIZE);
        }
        else
        {
            return (keyI % TSIZE);
        }

    }
    int colN()
    {
        return collisionL;
    }

    int probN()
    {
        return probL;
    }
};


void HashTableChain::deleteHash(string key)
{
    HashNode* prev = NULL;
    HashNode* entry = hashTableL[hashOne(key)];
    bool flag = false;

    if (entry == NULL )
    {
        return;
    }
    if(entry->key==key)
    {
       hashTableL[hashOne(key)]=NULL;
       return;
    }

    while (entry->next != NULL)
    {
        prev = entry;
        entry = entry->next;

        if(entry->key==key)
        {
            flag=true;
            break;
        }

    }
    if (prev != NULL)
    {
        prev->next = entry->next;
    }

    delete entry;


}

void HashTableChain::printHash()
{
    for (int i = 0; i < TSIZE; i++) {
        if (hashTableL[i] != NULL)
        {

             cout <<i;
             HashNode* entry = hashTableL[i];

            while (entry != NULL)
            {
                cout <<" --> "<< entry->key ;
                entry = entry->next;
            }

            cout << endl;

        }
        else
        {
             cout << i << endl;
        }
    }
}

void HashTableChain::insertHash(string key)
{
        int ind=hashOne(key);
        HashNode* prev = NULL;
        HashNode* entry = hashTableL[ind];

        while (entry != NULL)
        {
            prev = entry;
            entry = entry->next;
        }

        if (entry == NULL)
        {
            entry = new HashNode(ind,key);

            if (prev == NULL)
            {
                hashTableL[ind] = entry;

            }
            else
            {
                this->collisionL++;
                prev->next = entry;
            }
        }
        else
        {
            entry->key = key;
        }
    this->curentSizeL++;
}
bool HashTableChain::searchHash(string key)
{

    HashNode* entryN = hashTableL[hashOne(key)];

    while (entryN != NULL)
    {
        this->probL++;
        if (entryN->key == key)
        {
            cout<<"## FOUND"<<endl;
            return true;
        }
        entryN = entryN->next;
    }
    cout<<"## NOT FOUND"<<endl;
    return false;
}


class HashTableCustom
{
    string* hashTableC;
    int curentSizeC;
    int collisionC=0;
    int probC=1;

    public:

    HashTableCustom()
    {
        hashTableC=new string[TSIZE];
        curentSizeC=0;

        for (int i = 0; i < TSIZE; i++)
        {
            hashTableC[i] = "-1";
            //cout<<hashTable[i]<<endl;
        }
    }

    int hashOne(string key)
    {
        int keyI=stringToKey(key);

        if(HF==1)
        {
            return (keyI % TSIZE);
        }
        else
        {
            return (keyI % TSIZE);
        }

    }
    int hashTwo(string key)
    {
        int keyI=stringToKey(key);

        if(HF==1)
        {
            return (PRIME - (keyI % PRIME));
        }
        else
        {
            return (PRIME2 - (keyI % PRIME2));
        }


    }

    int colN()
    {
        return collisionC;
    }

    int probN()
    {
        return probC;
    }

    void insertHash(string key);
    bool searchHash(string key);
    void deleteHash(string key);
    void printHash();

};



void HashTableCustom::deleteHash(string key)
{
    int ind1 = hashOne(key);
    int ind2 = hashTwo(key);

    int i=0;

    while(hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]!=key)
    {
        if(hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]=="-1")
        {
            return ;
        }
        else
        {
            i=i+1;
        }
    }
    hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]="-1";

}

void HashTableCustom::printHash()
{
    for (int i = 0; i < TSIZE; i++) {
        if (hashTableC[i] != "-1")
            cout << i << " --> "
                 << hashTableC[i] << endl;
        else
            cout << i << endl;
    }
}

void HashTableCustom::insertHash(string key)
{
    int ind1 = hashOne(key);
    int ind2 = hashTwo(key);

    int i=0;

    //cout << "HI "<< endl;

    if(hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]!="-1")
    {
        i=1;

        while(true)
        {
            this->collisionC++;
            if(hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]=="-1")
            {
                hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]=key;
                //cout <<hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]<< endl;

                break;
            }
            else
            {
                i=i+1;
            }
        }
    }
    else
    {
        hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]=key;
        //cout<<hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]<<endl;
    }
    this->curentSizeC++;
}
bool HashTableCustom::searchHash(string key)
{
    int ind1 = hashOne(key);
    int ind2 = hashTwo(key);

    int i=0;

    while(hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]!=key)
    {
        this->probC++;
        if(hashTableC[(ind1 + C1*i * ind2 +C2*i*i)% TSIZE]=="-1")
        {
            if(1)
            {
                cout<<"## Not Found"<<endl;
            }
            return false;
        }
        i=i+1;
    }
    if(1)
    {
        cout<<"## Found"<<endl;
    }

    return true;
}

class HashTableDOuble
{
    string* hashTable;
    int curentSize;
    int collision=0;
    int prob=1;

    public:

    HashTableDOuble()
    {
        hashTable=new string[TSIZE];
        curentSize=0;

        for (int i = 0; i < TSIZE; i++)
        {
            hashTable[i] = "-1";
            //cout<<hashTable[i]<<endl;
        }
    }

    int hashOne(string key)
    {
        int keyI=stringToKey(key);

        if(HF==1)
        {
            return (keyI % TSIZE);
        }
        else
        {
            return (keyI % TSIZE);
        }

    }
    int hashTwo(string key)
    {
        int keyI=stringToKey(key);

        if(HF==1)
        {
            return (PRIME - (keyI % PRIME));
        }
        else
        {
            return (PRIME2 - (keyI % PRIME2));
        }


    }

    int colN()
    {
        return collision;
    }

    int probN()
    {
        return prob;
    }

    void insertHash(string key);
    bool searchHash(string key);
    bool searchPURE(string key);
    void deleteHash(string key);
    void printHash();

};

void HashTableDOuble::deleteHash(string key)
{
    int ind1 = hashOne(key);
    int ind2 = hashTwo(key);

    int i=0;

    while(hashTable[(ind1 + i * ind2 )% TSIZE]!=key)
    {
        if(hashTable[(ind1 + i * ind2 )% TSIZE]=="-1")
        {
            return ;
        }
        else
        {
            i=i+1;
        }
    }
    hashTable[(ind1 + i * ind2 )% TSIZE]="-1";

}

void HashTableDOuble::printHash()
{
    for (int i = 0; i < TSIZE; i++) {
        if (hashTable[i] != "-1")
            cout << i << " --> "
                 << hashTable[i] << endl;
        else
            cout << i << endl;
    }
}

void HashTableDOuble::insertHash(string key)
{
    int ind1 = hashOne(key);
    int ind2 = hashTwo(key);

    int i=0;

    //cout << "HI "<< endl;

    if(hashTable[(ind1 + i * ind2 )% TSIZE]!="-1")
    {
        i=1;

        while(true)
        {
            this->collision++;
            if(hashTable[(ind1 + i * ind2 )% TSIZE]=="-1")
            {
                hashTable[(ind1 + i * ind2 )% TSIZE]=key;
                //cout <<hashTable[(ind1 + i * ind2 )% TSIZE]<< endl;

                break;
            }
            else
            {
                i=i+1;
            }
        }
    }
    else
    {
        hashTable[(ind1 + i * ind2 )% TSIZE]=key;
    }
    this->curentSize++;
}
bool HashTableDOuble::searchHash(string key)
{
    int ind1 = hashOne(key);
    int ind2 = hashTwo(key);

    //cout<<"## Hukkaaa"<<endl;

    int i=0;

    while(hashTable[(ind1 + i * ind2 )% TSIZE]!=key)
    {
        this->prob++;
        if(hashTable[(ind1 + i * ind2 )% TSIZE]=="-1")
        {

            if(1)
            {
                cout<<"## Not Found"<<endl;
            }
            return false;
        }

        //cout<<"## Huaaaaa"<<endl;
        i=i+1;

    }
    if(1)
    {
        cout<<"## Found"<<endl;
    }

    return true;
}

bool HashTableDOuble::searchPURE(string key)
{
    int ind1 = hashOne(key);
    int ind2 = hashTwo(key);

    int i=0;

    while(hashTable[(ind1 + i * ind2 )% TSIZE]!=key)
    {
        if(hashTable[(ind1 + i * ind2 )% TSIZE]=="-1")
        {

            return false;
        }
        i=i+1;
    }

    return true;
}

int main(void)
{

    cout<<"### HASH ###"<<endl;
    cout<<"### FAHMID AL RIFAT ###"<<endl;
    cout<<"### 1705087  ###"<<endl;
    cout<<endl;

    HashTableDOuble hd ;
    HashTableCustom hc ;
    HashTableChain hl ;

    while(1)
    {
        printf("1. Insert \n");
        printf("2. Search \n");
        printf("3. Delete \n");
        printf("4. Print ALL \n");
        printf("5. REPORT with GENARATED \n");
        printf("6. Exit \n");

        int ch;
        scanf("%d",&ch);

        if(ch==1)
        {
            cout<<"### Give the key to INSERT =";
            //int key;
            string key;
            cin>>key;
            hd.insertHash(key);
            hc.insertHash(key);
            hl.insertHash(key);
            cout<<"### Key added "<<endl;
        }
        else if(ch==2)
        {
            cout<<"### Give the key to SEARCH=";
            //int key;
            string key;
            cin>>key;

            cout<<"### FOR Double HASH VIEW"<<endl;
            hd.searchHash(key);
            cout<<"### FOR Custom HASH VIEW"<<endl;
            hc.searchHash(key);
            cout<<"### FOR Chain HASH VIEW"<<endl;
            hl.searchHash(key);

            /* if(1)
            {
                cout<<"### Key FOUND "<<endl;
            }
            else
            {
                cout<<"### Key not FOUND "<<endl;
            } */
        }
        else if(ch==3)
        {
            cout<<"### Give the key to DELETE=";
            //int key;
            string key;
            cin>>key;
            cout<<"### FOR Double HASH VIEW"<<endl;
            hd.deleteHash(key);
            cout<<"### FOR Custom HASH VIEW"<<endl;
            hc.deleteHash(key);
            cout<<"### FOR Chain HASH VIEW"<<endl;
            hl.deleteHash(key);
            cout<<"### Key deleted "<<endl;
        }
        else if(ch==4)
        {
            cout<<"### FOR Double HASH VIEW"<<endl;
            hd.printHash();
            cout<<"### FOR Custom HASH VIEW"<<endl;
            hc.printHash();
            cout<<"### FOR Chain HASH VIEW"<<endl;
            hl.printHash();
            //pq.print();
            cout<<endl;

        }
        else if(ch==5)
        {

            cout<<"### GENERATED"<<endl;



            int input=1;
            int input2=1;
            int input3=1;

            cout<<"### Press One for Default"<<endl;
            cout<<"### Press Two for Rand Report"<<endl;
            cin>>input;


            if(input==1)
            {
                int c=RWSIZE;
                int d=RSWSIZE;

                cout<<"\nTotal Probes in L HASH = "<<hl.probN()<<endl;
                cout<<"Avg Probes in L HASH = "<<hl.probN()/(double)RSWSIZE<<endl;
                cout<<"\nTotal Probes in D HASH = "<<hd.probN()<<endl;
                cout<<"Avg Probes in D HASH = "<<hd.probN()/(double)RSWSIZE<<endl;
                cout<<"\nTotal Probes in C HASH = "<<hc.probN()<<endl;
                cout<<"Avg Probes in C HASH = "<<hc.probN()/(double)RSWSIZE<<endl;

                cout<<"\nCollision no in L HASH = "<<( hl.colN() )<<endl;
                cout<<"Collision Percent in L HASH = "<<( hl.colN()*100 )/TSIZE<<endl;
                cout<<"Unique Percent in L HASH = "<<100-( hl.colN()*100 )/TSIZE<<endl;
                cout<<"\nCollision no in D HASH = "<<( hd.colN() )<<endl;
                cout<<"Collision Percent in D HASH = "<<( hd.colN()*100 )/TSIZE<<endl;
                cout<<"Unique Percent in D HASH = "<<100-( hd.colN()*100 )/TSIZE<<endl;
                cout<<"\nCollision no in C HASH = "<<( hc.colN() )<<endl;
                cout<<"Collision Percent in C HASH = "<<( hc.colN()*100 )/TSIZE<<endl;
                cout<<"Unique Percent in C HASH = "<<100-( hc.colN()*100 )/TSIZE<<endl;
            }
            else
            {

            cout<<"### Total Word"<<endl;
            cin>>input2;
            cout<<"### Selected Word"<<endl;
            cin>>input3;

            int c=input2;
            int d=input3;
            int cc=input2;
            int dd=input3;

            string word[cc];

            while(c--)
            {
                    if(WSHOW) cout<<c<<endl;
                    word[c]=rWord();
                    if(WSHOW) cout<<word[c]<<endl;
                    //stringToKey(word[c]);

                    //if(1)
                    if(!hd.searchPURE(word[c]))
                    {
                      hd.insertHash(word[c]);
                      hc.insertHash(word[c]);
                      hl.insertHash(word[c]);
                    }
                    else
                    {
                        c=c+1;
                    }
                    if(WSHOW) cout<<"###INSERTED"<<endl;

            }


            int tempR=0;

            cout<<"\nSelected word ="<<endl;

            while(d--)
            {
                tempR=(rand()% cc)-1;

                if(WSHOW) cout<<tempR<<" "<<word[tempR]<<endl;
                hd.searchHash(word[tempR]);
                hc.searchHash(word[tempR]);
                hl.searchHash(word[tempR]);
            }


                //cout<<"\nTotal Probes in L HASH = "<<hl.probN()<<endl;
                cout<<"\nAvg Probes in L HASH = "<<hl.probN()/(double)dd<<endl;
                //cout<<"\nTotal Probes in D HASH = "<<hd.probN()<<endl;
                cout<<"\nAvg Probes in D HASH = "<<hd.probN()/(double)dd<<endl;
                //cout<<"\nTotal Probes in C HASH = "<<hc.probN()<<endl;
                cout<<"\nAvg Probes in C HASH = "<<hc.probN()/(double)dd<<endl;

                cout<<"\nCollision no in L HASH = "<<( hl.colN() )<<endl;
                //cout<<"Collision Percent in L HASH = "<<( hl.colN()*100 )/TSIZE<<endl;
                //cout<<"Unique Percent in L HASH = "<<100-( hl.colN()*100 )/TSIZE<<endl;
                cout<<"\nCollision no in D HASH = "<<( hd.colN() )<<endl;
                //cout<<"Collision Percent in D HASH = "<<( hd.colN()*100 )/TSIZE<<endl;
                //cout<<"Unique Percent in D HASH = "<<100-( hd.colN()*100 )/TSIZE<<endl;
                cout<<"\nCollision no in C HASH = "<<( hc.colN() )<<endl;
                //cout<<"Collision Percent in C HASH = "<<( hc.colN()*100 )/TSIZE<<endl;
                //cout<<"Unique Percent in C HASH = "<<100-( hc.colN()*100 )/TSIZE<<endl;


            }



        }
        else if(ch==6)
        {
            cout<<"### Praogram ENDED"<<endl;
            break;
        }

    }

    return 0;
}
