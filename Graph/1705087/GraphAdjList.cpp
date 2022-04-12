#include<bits/stdc++.h>

#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3

using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;   // circular queue implementation
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************

//****************Dynamic ArrayList class based************************
class ArrayList
{
	int * list;
	int length ;
	int listMaxSize ;
	int listInitSize ;
public:
	ArrayList() ;
	~ArrayList() ;
	int searchItem(int item) ;
    void insertItem(int item) ;
	void removeItem(int item) ;
	void removeItemAt(int item);
	int getItem(int position) ;
	int getLength();
	bool empty();
	void printList();
} ;


ArrayList::ArrayList()
{
	listInitSize = 2 ;
	listMaxSize = listInitSize ;
	list = new int[listMaxSize] ;
	length = 0 ;
}

void ArrayList::insertItem(int newitem)
{
	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;  // doubling memory when array is full
		tempList = new int[listMaxSize] ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        delete[] list ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
}

int ArrayList::searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

void ArrayList::removeItemAt(int position) //do not preserve order of items
{
	if ( position < 0 || position >= length ) return ; //nothing to remove
	list[position] = list[length-1] ;
	length-- ;
}


void ArrayList::removeItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return ; //nothing to remove
	removeItemAt(position) ;
}


int ArrayList::getItem(int position)
{
	if(position < 0 || position >= length) return NULL_VALUE ;
	return list[position] ;
}

int ArrayList::getLength()
{
	return length ;
}

bool ArrayList::empty()
{
    if(length==0)return true;
    else return false;
}

void ArrayList::printList()
{
    int i;
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("Current size: %d, current length: %d\n", listMaxSize, length);
}

ArrayList::~ArrayList()
{
    if(list) delete [] list;
    list = 0 ;
}

//******************ArrayList class ends here*************************

//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	ArrayList  * adjList ;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
    int *colorMarked;
    int *parentNode;
    int *level;
    int parentVertex;


public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	bool addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getInDegree(int u);
    int getOutDegree(int u);
    int getDegree(int u,bool out=true);
    void printAdjVertices(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source,bool draw=true); //will run bfs in the graph
	void bfs_run(int source,bool draw);
    void dfs(int source,bool draw=true);
    void dfs_run(int u,bool draw);

};

int Graph::getInDegree(int u)
{
    return getDegree(u, false);
}

int Graph::getOutDegree(int u)
{
    return getDegree(u, true);
}


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	adjList = 0 ;
	parentVertex=0 ;
	directed = dir ; //set direction of the graph
	//define other variables to be initialized
	colorMarked=new int [10];
	parentNode=new int [10];
	level=new int[10];
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	if(adjList!=0) delete[] adjList ; //delete previous list
	adjList = new ArrayList[nVertices] ;

	if(colorMarked!=0) delete[] colorMarked ;
	colorMarked=new int [nVertices];

    if(parentNode!=0) delete[] parentNode ;
	parentNode=new int [nVertices];


	if(level!=0) delete[] level ;
	level=new int [nVertices];

}

bool Graph::addEdge(int u, int v)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false; //vertex out of range
    this->nEdges++ ;

	adjList[u].insertItem(v) ;

	if(!directed) adjList[v].insertItem(u) ;

	return true;
}

void Graph::removeEdge(int u, int v)
{
    if(isEdge(u,v))
    {
        adjList[u].removeItem(v);
        if(!directed) adjList[v].removeItem(u) ;
    }

    //write this function
}

bool Graph::isEdge(int u, int v)
{
    for(int i=0; i<adjList[u].getLength();i++)
        {
            if(adjList[u].getItem(i)==v)
                return true ;
        }

    for(int i=0; i<adjList[v].getLength();i++)
        {
            if(adjList[v].getItem(i)==u)
                return true ;
        }

    return false;
    //returns true if (u,v) is an edge, otherwise should return false
}

int Graph::getDegree(int u,bool out)
{
     if(!directed)
     return adjList[u].getLength();
    //returns the degree of vertex u
    if(out)
    {
        return adjList[u].getLength();
    }
    else
    {
        int countIn=0;
        for(int i=0;i<nVertices;i++)
            {
                printf("%d:", i);
                for(int j=0; j<adjList[i].getLength();j++)
                {
                    if(i!=u&&adjList[i].getItem(j)==u)
                    countIn++;
                }
            }

        return countIn;
    }
}

void Graph::printAdjVertices(int u)
{
    printf("%d:", u);
        for(int i=0; i<adjList[u].getLength();i++)
        {
            printf(" %d", adjList[u].getItem(i));
        }
    //prints all adjacent vertices of a vertex u
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    for(int i=0; i<adjList[u].getLength();i++)
        {
            for(int j=0; j<adjList[v].getLength();j++)
            {
                if(adjList[u].getItem(i)==adjList[v].getItem(j))
                    return true;
            }

        }
    return false;

    //returns true if vertices u and v have common adjacent vertices

}

void Graph::bfs(int source,bool draw)
{
        for(int i=0;i<nVertices;i++)
            colorMarked[i]=WHITE;

        bfs_run(source,draw);

        for(int i=0;i<nVertices;i++)
        {
            if(colorMarked[i]==WHITE)
            {
                bfs_run(i,draw);
            }
        }


}

void Graph::bfs_run(int source,bool draw)
{
    Queue q1;

    parentNode[source]=-1;
    colorMarked[source]=GREY;
    q1.enqueue(source);
    level[source]=0;

    while(!q1.empty())
    {
        parentVertex=q1.dequeue();

        if(draw)
            cout<<parentVertex<<" ";

        colorMarked[parentVertex]=BLACK;
        //colorMarked[parentVertex]=true;

     for(int i=0;i<adjList[parentVertex].getLength();i++)
        {
            int childVertex=adjList[parentVertex].getItem(i);

            parentNode[childVertex]=parentVertex;

            if(colorMarked[childVertex]==WHITE)
            {
                level[childVertex]=level[parentVertex]+1;
                colorMarked[childVertex]=GREY;
                q1.enqueue(childVertex);
            }
        }
    }

    //complete this function
    //initialize BFS variables for all n vertices first

}

void Graph::dfs_run(int u,bool draw)
{
    colorMarked[u]=GREY;

    if(draw)
        cout<<u<<" ";

    for(int i=0;i<adjList[u].getLength();i++)
    {
        int childVertex=adjList[u].getItem(i);

        parentNode[childVertex]=u;

        if(colorMarked[childVertex]==WHITE)
        {
                dfs_run(childVertex,draw);
        }


    }

    colorMarked[u]=BLACK;
}

void Graph::dfs(int source,bool draw)
{

    for(int i=0;i<nVertices;i++)

    {
        colorMarked[i]=WHITE;
    }

    parentNode[source]=-1;
    dfs_run(source,draw);

    for(int i=0;i<nVertices;i++)

    {
        if(colorMarked[i]==WHITE)
        {

            parentNode[i]=-1;
            dfs_run(i,draw);

        }
    }






}


int Graph::getDist(int u, int v)
{

    bfs(u,false);
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    return level[v] ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<adjList[i].getLength();j++)
        {
            printf(" %d", adjList[i].getItem(j));
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    if(adjList) delete [] adjList;
    if(colorMarked) delete [] colorMarked;
    if(parentNode) delete [] parentNode;
    if(level) delete [] level;
    adjList = 0 ;
    //write your destructor here
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    printf("Enter your choice:\n");
    printf("1. Graph operation   2. Staistics : Run time of BFS\n");

     int choice , opt;
    scanf("%d",&choice);

    if(choice == 1) opt = true;
    else if(choice == 2) opt = false;

    if(opt)
    {



    int n;
    int choice;
    bool dir;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice);
    if(choice == 1)dir = true;
    else if(choice == 2)dir = false;

    Graph g(dir);

    printf("Enter number of vertices: ");
    scanf("%d", &n);
    g.setnVertices(n);

    while(1)
    {
        printf("1. Add edge. \n");
        printf("2. Remove edge. \n");
        printf("3. Edge between. \n");
        printf("4. Get degree . \n");
        printf("5. Print adjacent vertices of. \n");
        printf("6. Is there common between . \n");
        printf("7. Run bfs. \n");
        printf("8. Get distance between. \n");
        printf("9. Run dfs. \n");
        printf("10. Print Graph \n11. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            g.addEdge(u, v);
            cout<<"### Edge added "<<endl;
        }
        else if(ch==2)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            g.removeEdge(u, v);
            cout<<"### Edge removed if exist"<<endl;
        }
        else if(ch==3)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.isEdge(u, v))
                cout<<"### There is edge between u and v "<<endl;
            else
                cout<<"### There is no edge between u and v "<<endl;

        }
        else if(ch==4)
        {
            cout<<"### Give the input vertice =";
            int u;
            scanf("%d", &u);
            if(!dir)
            {

            cout<<"### The degree of "<<u<<"is :"<<g.getDegree(u)<<endl;
            }
            else
            {
                cout<<"### The degree In of "<<u<<"is :"<<g.getInDegree(u)<<endl;
                cout<<"### The degree Out of "<<u<<"is :"<<g.getOutDegree(u)<<endl;
            }


        }
        else if(ch==5)
        {
            cout<<"### Give the input vertice =";
            int u;
            scanf("%d", &u);
            cout<<"### The adjacent of "<<u<<" is :";
            g.printAdjVertices(u);
            cout<<endl;
        }
        else if(ch==6)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            if(g.hasCommonAdjacent(u, v))
                cout<<"### There is common between u and v "<<endl;
            else
                cout<<"### There is no common between u and v "<<endl;

        }
        else if(ch==7)
        {
            cout<<"### Give the input vertice =";
            int u;
            scanf("%d", &u);
            cout<<"### BFS =";
            g.bfs(u);
            cout<<endl;

        }
        else if(ch==8)
        {
            cout<<"### Give the input of vertices =";
            int u, v;
            scanf("%d%d", &u, &v);
            cout<<"### Distance ="<<g.getDist(u,v)<<endl;
        }
        else if(ch==9)
        {
            cout<<"### Give the input vertice =";
            int u;
            scanf("%d", &u);
            cout<<"### DFS =";
            g.dfs(u);
            cout<<endl;
        }
        else if(ch==10)
        {
            cout<<"### The graph is now ="<<endl;
            g.printGraph();
        }
        else if(ch==11)
        {
            cout<<"### The graph is deleted"<<endl;
            break;
        }
    }

    }

    else
    {

    int choice2,choice3;
    bool dir,select;
    printf("Enter your choice:\n");
    printf("1. directed graph   2. undirected graph\n");
    scanf("%d",&choice2);
    if(choice2 == 1) dir = true;
    else if(choice2 == 2) dir = false;

   srand(time(0));

    printf("1. Manual   2. Auto\n");
    scanf("%d",&choice3);
    if(choice3 == 1) select = true;
    else if(choice3 == 2) select = false;

    if(select)
    {
        int a,b;
        printf("Enter Verteces and Edges =");
        scanf("%d %d",&a,&b);



       int vertices=a;
        {
            cout<<"### The number of Vertices = "<<vertices<<endl;


            Graph g(dir);
            g.setnVertices(vertices);

            int endLimit=(vertices*vertices-vertices)/8;

            double totalTime;

            int edges=b;
            {
                cout<<"  --- When number of edges ="<<edges<<" ";





                for(int i=1; i<=edges; i++)
                {
                    //cout<<"  created edges ="<<i<<" ";
                    int u=(rand()%vertices);
                    int v=(rand()% vertices);

                    if(g.isEdge(u,v))
                    {
                        i=i-1;
                    }
                    else
                    {
                        g.addEdge(u,v);
                    }

                }

                cout<<"debug"<<endl;



                 totalTime=0;



                for(int runI=0;runI<10;runI++)
                {
                    int randSource=(rand()% vertices);



                    clock_t startTime, endTime;
                    double cpu_time_used;


                    startTime = clock();
                    g.bfs(randSource,false);
                    endTime = clock();

                    cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

                    //cout<<" BFS part time  "<<cpu_time_used<<endl;

                    totalTime=totalTime+cpu_time_used;
                }

                cout<<"      The avg time ( milli seceond ) needed is =  "<<totalTime/10<<endl;

                for(int i=0; i<vertices; i++)
                {
                    for(int j=0; j<vertices; j++)
                    {
                        if(g.isEdge(i,j))

                            g.removeEdge(i,j);

                    }
                }



            }

        //g.~Graph();

        cout<<endl;

        }
    }

    else
    {



        for(int vertices=1000;vertices<=16000;vertices=vertices*2)
        {
            cout<<"### The number of Vertices = "<<vertices<<endl;


            Graph g(dir);
            g.setnVertices(vertices);

            int endLimit=((vertices*vertices)-vertices)/8;

            double totalTime;

            for(int edges=vertices;edges<=endLimit;edges=edges*2)
            {
                cout<<"  --- When number of edges ="<<edges<<" ";





                for(int i=1; i<=edges; i++)
                {
                    //cout<<"  created edges ="<<i<<" ";
                    int u=(rand()%vertices);
                    int v=(rand()% vertices);

                    if(g.isEdge(u,v))
                    {
                        i=i-1;
                    }
                    else
                    {
                        g.addEdge(u,v);
                    }

                }

                cout<<"debug"<<endl;



                 totalTime=0;



                for(int runI=0;runI<10;runI++)
                {
                    int randSource=(rand()% vertices);



                    clock_t startTime, endTime;
                    double cpu_time_used;


                    startTime = clock();
                    g.bfs(randSource,false);
                    endTime = clock();

                    cpu_time_used = ((double) (endTime - startTime)) / CLOCKS_PER_SEC;

                    //cout<<" BFS part time  "<<cpu_time_used<<endl;

                    totalTime=totalTime+cpu_time_used;
                }

                cout<<"      The avg time ( milli seceond ) needed is =  "<<totalTime/10<<endl;

                for(int i=0; i<vertices; i++)
                {
                    for(int j=0; j<vertices; j++)
                    {
                        if(g.isEdge(i,j))

                            g.removeEdge(i,j);

                    }
                }



            }

        //g.~Graph();

        cout<<endl;

        }
    }




    }
    return 0;
}
