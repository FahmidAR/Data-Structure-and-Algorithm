#include<bits/stdc++.h>

#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define DEBUG 0
#define FILE 1

using namespace std;




class Graph
{
int nVertices, nEdges ;
bool directed ;
int ** matrix ; //adjacency matrix to store the graph
//define other variables required for bfs such as color, parent, and dist
//you must use pointers and dynamic allocation
    int *colorMarked;
    int *dist;
    int *parentVertex;


public:
Graph(bool dir = true);
~Graph();
void setnVertices(int n,int m);
void addEdge(int u, int v,int weight);
void removeEdge(int u, int v);
bool isEdge(int u, int v);
void dijkstra(int source,int destination);
void bellmanford(int source,int destination);

};



void Graph::dijkstra(int source,int destination)
{
    if(DEBUG)
    {
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j])
                printf(" %d", j);
        }
        printf("\n");
    }
    }





    for(int i=0;i<nVertices;i++)
    {
        colorMarked[i]=WHITE;

        parentVertex[i]=-1;

        dist[i]=INT_MAX;

    }

    dist[source]=0;

    if(DEBUG)
    {

    for(int i=0;i<nVertices;i++)
    {

        cout<<"DISTANCE = "<<i<<" "<<dist[i]<<endl;
        cout<<endl;
    }
    }

    for(int i=0;i<nVertices-1;i++)
    {

        int minHere=INT_MAX;
        int minIndex;

        for(int j=0;j<nVertices;j++)
        {
            if(dist[j]<=minHere&& colorMarked[j]==WHITE )
            {
                minHere=dist[j];
                minIndex=j;
            }
        }



       colorMarked[minIndex]=BLACK;
       int currentNode=minIndex;

       for(int k=0;k<nVertices;k++)
       {
           if(colorMarked[k]==WHITE&&abs(matrix[currentNode][k]))
           {
               if(dist[currentNode]+abs(matrix[currentNode][k])<dist[k])
               {
                   parentVertex[k]=currentNode;
                   dist[k]=dist[currentNode]+abs(matrix[currentNode][k]);
               }
           }
       }
    }

    if(DEBUG)
    {

    for(int i=0;i<nVertices;i++)
    {

        cout<<"PARENT = "<<i<<" "<<parentVertex[i]<<endl;
        cout<<endl;
    }

    for(int i=0;i<nVertices;i++)
    {

        cout<<"DISTANCE = "<<i<<" "<<dist[i]<<endl;
        cout<<endl;
    }
    }


    if(!FILE)
    {
    cout<<"Dijkstra Algorithm: "<<endl;
    cout<<dist[destination]<<endl;

    int countV=1 ,i=destination;

    int draw[nVertices]={0};

    //cout<<i<<" ";
    draw[0]=i;

    while(parentVertex[i]!=-1){

        i=parentVertex[i];

        draw[countV++]=i;

        //cout<<"-> "<<i<<" ";

    }



    cout<<draw[--countV]<<" ";

    while(countV--){

        cout<<"-> "<<draw[countV]<<" ";

    }

    cout<<endl;
    cout<<endl;

    }
    else
    {
    ofstream myFile;
    myFile.open ("output.txt",ios::app);

    myFile<<"Dijkstra Algorithm: "<<endl;
    myFile<<dist[destination]<<endl;

    int countV=1 ,i=destination;

    int draw[nVertices]={0};

    //cout<<i<<" ";
    draw[0]=i;

    while(parentVertex[i]!=-1){

        i=parentVertex[i];

        draw[countV++]=i;

        //cout<<"-> "<<i<<" ";

    }


    myFile<<draw[--countV]<<" ";

    while(countV--){

        myFile<<"-> "<<draw[countV]<<" ";

    }

    myFile<<endl;
    myFile<<endl;

    myFile.close();

    }




}

void Graph::bellmanford(int source,int destination)
{

    for(int i=0;i<nVertices;i++)
    {

        parentVertex[i]=-1;

        dist[i]=INT_MAX;

    }

    dist[source]=0;

    for(int run=0;run<nVertices-1;run++)
    {
        for(int i=0;i<nVertices ;i++)
        {
            for(int j=0;j<nVertices ;j++)
            {
                if(dist[i]!=INT_MAX&&matrix[i][j]!=0)
                {
                    if(dist[i]+matrix[i][j]<dist[j])
                {
                  //  cout<<i<<" "<<j<<endl;
                    parentVertex[j]=i;
                    dist[j]=dist[i]+matrix[i][j];
                  //  cout<<j<<":"<<dist[j]<<endl;
                }
                }
            }

        }
    }

   // cout<<dist[destination];

//for(int i=0;i<nVertices;i++)
  //  cout<<parentVertex[i]<<" ";



    if(!FILE)
    {
    cout<<"BellmanFord Algorithm: "<<endl;

    for(int run=0;run<nVertices-1;run++)
    {
        for(int i=0;i<nVertices ;i++)
        {
            for(int j=0;j<nVertices ;j++)
            {
                if(matrix[i][j])
                {
                    if(dist[i]+matrix[i][j]<dist[j])
                {
                    cout<<"Graph Contain Negetive Weight Cycle"<<endl;
                    cout<<endl;

                    return;
                }
                }
            }

        }
    }
    cout<<dist[destination]<<endl;

    int countV=1 ,i=destination;

    int draw[nVertices]={0};

    //cout<<i<<" ";
    draw[0]=i;

    while(parentVertex[i]!=-1){

        i=parentVertex[i];

        draw[countV++]=i;

        //cout<<"-> "<<i<<" ";

    }

    cout<<draw[--countV]<<" ";

    while(countV--){

        cout<<"-> "<<draw[countV]<<" ";

    }

    cout<<endl;
    cout<<endl;
    }
    else
    {

    ofstream myFile;
    myFile.open ("output.txt");

    myFile<<"BellmanFord Algorithm: "<<endl;

    for(int run=0;run<nVertices-1;run++)
    {
        for(int i=0;i<nVertices ;i++)
        {
            for(int j=0;j<nVertices ;j++)
            {
                if(matrix[i][j])
                {
                    if(dist[i]+matrix[i][j]<dist[j])
                {
                    myFile<<"Graph Contain Negetive Weight Cycle"<<endl;
                    myFile<<endl;

                    return;
                }
                }
            }

        }
    }
    myFile<<dist[destination]<<endl;

    int countV=1 ,i=destination;

    int draw[nVertices]={0};

    //cout<<i<<" ";
    draw[0]=i;

    while(parentVertex[i]!=-1){

        i=parentVertex[i];

        draw[countV++]=i;

        //cout<<"-> "<<i<<" ";

    }

    myFile<<draw[--countV]<<" ";

    while(countV--){

        myFile<<"-> "<<draw[countV]<<" ";

    }

    myFile<<endl;
    myFile<<endl;
    myFile.close();

    }



}



Graph::Graph(bool dir)
{
nVertices = 0 ;
nEdges = 0 ;
matrix = 0 ;
directed = dir ; //set direction of the graph
//define other variables to be initialized
colorMarked=new int [10];
parentVertex=new int [10];
dist=new int[10];
}

void Graph::setnVertices(int n,int m)
{
this->nVertices = n ;
this->nEdges = m ;

//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }


if(colorMarked!=0) delete[] colorMarked ;
colorMarked=new int [nVertices];

    if(parentVertex!=0) delete[] colorMarked ;
parentVertex=new int [nVertices];


if(dist!=0) delete[] dist ;
dist=new int [nVertices];

}

void Graph::addEdge(int u, int v,int weight)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = weight;
    if(!directed) matrix[v][u] = weight;

}

void Graph::removeEdge(int u, int v)
{
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
    //write this function
}

bool Graph::isEdge(int u, int v)
{
    return matrix[u][v]!=0;
    //returns true if (u,v) is an edge, otherwise should return false
}

Graph::~Graph()
{
    if(colorMarked) delete [] colorMarked;
    if(parentVertex) delete [] parentVertex;
    if(dist) delete [] dist;
    //write your destructor here
}




int main(void)
{
    int vertices , edges ;
    int u , v, w;

    Graph g;

    if(!FILE)
    {
    cin>>vertices>>edges;

    g.setnVertices(vertices,edges);

    for(int i=0;i<edges;i++)
    {
       // cout<<edges<<endl;

        cin>>u>>v>>w;

        g.addEdge(u,v,w);
    }

    cin>>u>>v;

    g.bellmanford(u,v);

    g.dijkstra(u,v);

    }
    else
    {

    /*
    input file name : input.txt
    output file name : output.txt

    */

    ifstream inFile;

    inFile.open("input3.txt");
    if (!inFile)
    {
        cout << "\nError occurs while opening file.\n";
        return 1;
    }

    inFile>>vertices>>edges;
    g.setnVertices(vertices,edges);


    for(int i=0;i<edges;i++)
    {


        inFile>>u>>v>>w;

        // cout<<i<<" "<<u<<" "<<v<<" "<<w<<endl;

        g.addEdge(u,v,w);
    }

    inFile>>u>>v;

    inFile.close();

    g.bellmanford(u,v);
    g.dijkstra(u,v);


    }

    return 0;
}
