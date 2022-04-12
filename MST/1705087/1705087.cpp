#include<bits/stdc++.h>

#define queueMaxSize 100000
#define INF 999999
#define NULL_VALUE -999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define DEBUG 0
#define INDEX 1
#define FILE 1

using namespace std;

typedef pair<int,int> p;

class Edge {

  private:

    int u;
    int v;
    double w;

  public:

    Edge(int i,int j,double k)
    {
        u = i;
        v = j;
        w = k;
    }

    void setU(int i) {
      u = i;
    }

    void setV(int i) {
      v = i;
    }

    void setW(double i) {
      w = i;
    }

    int getU() {
      return u;
    }

    int getV() {
      return v;
    }

    double getW() {
      return w;
    }


};

bool compareEdge(Edge a, Edge b)
{
    return a.getW()<=b.getW();
}

class SET{

    int *parent;
    int *rankH;

    public:

    SET()
    {
        parent = new int[queueMaxSize];
        rankH = new int[queueMaxSize];
    }

    SET(int x)
    {
        parent = new int[x];
        rankH = new int[x];
    }



    void makeSet(int x);
    int findSet(int x);
    void unionSet(int x,int y);

    ~SET();

};

void SET::makeSet(int x)
{
    rankH[x]=0;
    parent[x]=x;
}

int SET::findSet(int x)
{
    if (parent[x]!=x)
    {
        parent[x]=findSet(parent[x]);
    }
    return parent[x];
}

void SET::unionSet(int x,int y)
{
     x=findSet(x);
     y=findSet(y);

    if(x!=y)
    {
        if(rankH[x]>rankH[y]) parent[y]=x;
        else parent[x]=y;
        if(rankH[x]==rankH[y]) rankH[y]++;
    }
}

SET::~SET()
{
    if(parent) delete[] parent;
    if(rankH) delete[] rankH;
    parent = 0;
    rankH = 0;
}

class Graph
{
	int nVertices, nEdges ;
	bool udirected ;
	int totalWeight;
	vector<Edge> edgeAll;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
    int *colorMarked;
    int *level;
    int *distD;
    int *parD;
    int parentVertex;
    double ** disMatrix ;
    int ** parMatrix ;


public:
	Graph(bool dir = true);
	~Graph();
	void setnVertices(int n);
	void printGraph();
	void addEdge(int u, int v,double w);
	void rwEdge(int u, int v,double w);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int weighVal(int u,int v);
    Edge* searchEdge(int u, int v);
    void Prim(int s);
    void Krus();
    void printTW();

};

void Graph::Krus()
{
    ofstream myFile;
    myFile.open ("output.txt",ios::app);

    cout<<" Kruskal's Algorithm :" <<endl;
    myFile<<" Kruskal's Algorithm :" <<endl;

    SET s(nVertices);
    totalWeight=0;

    for(int i=0;i<nVertices;i++)
    {
        s.makeSet(i);
    }

   sort(edgeAll.begin(), edgeAll.end(),compareEdge);

    if(DEBUG)
    {

    for(int j=0; j<edgeAll.size(); j++)
    {
            Edge eg=edgeAll[j];


            cout<<" Edge "<<j<<" "<<eg.getU()<<" "<<eg.getV()<<" "<<eg.getW()<<endl;

    }

    }

    for(int j=0; j<edgeAll.size(); j++)
    {
            Edge eg=edgeAll[j];

            if(DEBUG)
            cout<<" Edge "<<j<<" "<<eg.getU()<<" "<<eg.getV()<<endl;

            if(s.findSet(eg.getU())!=s.findSet(eg.getV()))
            {
                cout<<" "<<eg.getU()<<" "<<eg.getV()<<endl;
                myFile<<" "<<eg.getU()<<" "<<eg.getV()<<endl;
                s.unionSet(eg.getU(),eg.getV());

                totalWeight+=eg.getW();
            }

    }

   // cout<<" "<<totalWeight<<endl;

   myFile.close();

}

void Graph::Prim(int s)
{

    ofstream myFile;
    myFile.open ("output.txt",ios::app);


    priority_queue< p, vector <p>, greater<p> > pqd;

    totalWeight=0;

    for(int i=0;i<nVertices;i++)
    {
        distD[i]=INF;
        parD[i]=-1;
        colorMarked[i]=WHITE;
    }

    distD[s]=0;



    pqd.push(make_pair(0,s));

    int now, child;
    double weight;

    while(!pqd.empty())
    {
        now=pqd.top().second;
        pqd.pop();

        colorMarked[now]=BLACK;

       // cout<<" Pop "<<now<<endl;


        for(int k=0;k<edgeAll.size();k++)
        {
            Edge eg =edgeAll[k];

            if(eg.getU()==now)
            {
                child=eg.getV();
                weight=eg.getW();

                if(DEBUG)

                cout<<" 1111 "<<" "<<now<<" "<<child<<" "<<distD[child]<<" "<<weight<<endl;


            if(colorMarked[child]==WHITE&&distD[child]> weight)
            {
                distD[child]=weight;

                if(DEBUG)

                cout<<" Weight " <<edgeAll.size()<<" "<<now<<" "<<child<<" "<<distD[child]<<" "<<weight<<endl;


                parD[child]=now;

                pqd.push(make_pair(distD[child],child));
            }

            }
        }


    }

    for(int k=0;k<edgeAll.size();k++)
    {
        if((parD[edgeAll[k].getU()]==edgeAll[k].getV()))
        {
            totalWeight+=edgeAll[k].getW();
        }
    }

   // cout<<" "<<totalWeight<<endl;

    cout<<" Prim's Algorithm :" <<endl;
    myFile<<" Prim's Algorithm :" <<endl;

    cout<<" Root Node = "<<s<<endl;
    myFile<<" Root Node = "<<s<<endl;


    for(int i=1 ; i<nVertices ; i++)
    {
        cout<<" "<<parD[i]<<" "<<i<<endl;
        myFile<<" "<<parD[i]<<" "<<i<<endl;
    }

    myFile.close();
}



void Graph::printTW()
{
    ofstream myFile;
    myFile.open ("output.txt");

    SET s(nVertices);
    totalWeight=0;

    for(int i=0;i<nVertices;i++)
    {
        s.makeSet(i);
    }

   sort(edgeAll.begin(), edgeAll.end(),compareEdge);

    for(int j=0; j<edgeAll.size(); j++)
    {
            Edge eg=edgeAll[j];

            if(DEBUG)
            cout<<" Edge "<<j<<" "<<eg.getU()<<" "<<eg.getV()<<endl;

            if(s.findSet(eg.getU())!=s.findSet(eg.getV()))
            {

                s.unionSet(eg.getU(),eg.getV());

                totalWeight+=eg.getW();
            }

    }

   cout<<" "<<totalWeight<<endl;
   myFile<<" "<<totalWeight<<endl;

   myFile.close();
}


Edge* Graph::searchEdge(int u, int v)
{
    vector<Edge>::iterator it;

    for( it =edgeAll.begin(); it <= edgeAll.end(); ++it)
    {


        if((*it).getU()==u&&(*it).getV()==v)
        {
            return &(*it);
        }
    }
}


void Graph::printGraph()
{
    if(DEBUG)
    {
        for(int j=0; j<edgeAll.size(); j++)
        {
            Edge eg=edgeAll[j];

            cout<<"### DEBUG EDGE u v w "<<eg.getU()<<" "<<eg.getV()<<" "<<weighVal(eg.getU(),eg.getV())<<endl;
        }
    }


    printf("\nNumber of vertices: %d , Number of edges: %d \n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf(" %d :", i+INDEX);

        int flag = 0 ;

        for(int j=0; j<edgeAll.size(); j++)
        {
            Edge eg=edgeAll[j];

            if(eg.getU()==i&&flag)
            {
                cout<<"-->";
            }

            if(eg.getU()==i)
            {
                flag=1;
                cout<<" "<<eg.getV()+INDEX<<" ("<<eg.getW()<<") ";
            }
        }
        cout<<endl;
    }
}

int Graph::weighVal(int u,int v)
{
    for(int i=0; i<edgeAll.size(); i++)
    {
        Edge eg=edgeAll[i];

        if(eg.getU()==u&&eg.getV()==v)
        {
            return eg.getW();
        }
    }
}




Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	parentVertex=0 ;
	udirected = dir ; //set direction of the graph
	//define other variables to be initialized
	colorMarked=new int [10];
	distD=new int[10];
	level=new int[10];
	parD=new int[10];
}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	if(colorMarked!=0) delete[] colorMarked ;
	colorMarked=new int [nVertices];

	if(level!=0) delete[] level ;
	level=new int [nVertices];

    if(distD!=0) delete[] distD ;
    distD=new int [nVertices+1];

    if(parD!=0) delete[] parD ;
    parD=new int [nVertices+1];


}

void Graph::rwEdge(int u, int v,double w)
{
    vector<Edge>::iterator it;edgeAll.size();

    for( it =edgeAll.begin(); it != edgeAll.end(); ++it)
    {


        if((*it).getU()==u&&(*it).getV()==v)
        {
           (*it).setW(w);
        }

        if(udirected)
        {
        if((*it).getV()==u&&(*it).getU()==v)
        {
           (*it).setW(w);
        }
        }
    }
}

void Graph::addEdge(int u, int v,double w)
{
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return; //vertex out of range

    this->nEdges++ ;

	Edge eg(u,v,w);

	edgeAll.push_back(eg);

	if(udirected)
    {
	Edge eg(v,u,w);

	edgeAll.push_back(eg);

    }

	if(DEBUG) cout<<"### DEBUG EDGE  "<<nEdges<<endl;

}

void Graph::removeEdge(int u, int v)
{

    if(isEdge(u,v))
    {
        this->nEdges--;

        vector<Edge>::iterator it;

    for( it =edgeAll.begin(); it <= edgeAll.end(); ++it)
    {


        if((*it).getU()==u&&(*it).getV()==v)
        {
            edgeAll.erase(it);
        }

        if(udirected)
        {
        if((*it).getV()==u&&(*it).getU()==v)
        {
           edgeAll.erase(it);
        }
        }
    }

    }

    //write this function
}

bool Graph::isEdge(int u, int v)
{
    for(int i=0; i<edgeAll.size(); i++)
    {
        Edge eg=edgeAll[i];

        if(eg.getU()==u&&eg.getV()==v)
        {
            return true;
        }
    }
    return false;
}



Graph::~Graph()
{

    if(colorMarked) delete [] colorMarked;
    if(level) delete [] level;
    if(distD) delete [] distD;
    if(parD) delete [] parD;
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

    g.setnVertices(vertices);

    for(int i=0;i<edges;i++)
    {
       // cout<<edges<<endl;

        cin>>u>>v>>w;

        g.addEdge(u,v,w);
    }


    g.Prim(0);
    g.Krus();

    }
    else
    {

    /*
    input file name : input.txt
    output file name : output.txt

    */

    ifstream inFile;

    inFile.open("input.txt");

    if (!inFile)
    {
        cout << "\nError occurs while opening file.\n";
        return 1;
    }

    inFile>>vertices>>edges;

    g.setnVertices(vertices);


    for(int i=0;i<edges;i++)
    {


        inFile>>u>>v>>w;

         //cout<<i<<u<<v<<w<<endl;

        g.addEdge(u,v,w);
    }

    inFile.close();

    g.printTW();
    g.Krus();
    g.Prim(0);



    }
    return 0;
}
