
#include<bits/stdc++.h>

#define queueMaxSize 100000
#define INF 999999
#define NULL_VALUE -999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#define MID 0
#define LEFT 1
#define RIGHT 2
#define DEBUG 0
#define INDEX 0
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



class Graph
{
	int nVertices, nEdges ;
	bool udirected ;
	int maxFlow;
	int totalWeight;
	bool bpGraph;
	vector<Edge> edgeAll;
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation
    int *colorMarked;
    int *posMarked;
    int *level;
    int *distD;
    int *parD;
    int parentVertex;

    int ** flowMatrix ;
    int ** resMatrix ;


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


    int fordFul(int source,int sink);
    bool bfs(int source,int sink);

    void printFlowMatrix();
    void printResMatrix();

    void printFlowEdge();
    void pmbmEdge();

    bool isBip();
    int mBM();

};

int Graph::mBM()
{
    bpGraph=isBip();
    if(bpGraph)
    {
        cout<<"# The graph is bipartite #"<<endl;

        maxFlow=0;
        int pathFlow=INT_MAX;
        int tra,before,extra,cap;
        //this->udirected=false;

        if(DEBUG)
        {
            printFlowMatrix();
            cout<<endl;
            printResMatrix();
            cout<<endl;
            cout<<"# Check Point 1 #\n  BEST of LUCK"<<endl;
        }

        for(int j=0; j<edgeAll.size(); j++)
        {
              int u=edgeAll[j].getU();
              int v=edgeAll[j].getV();

              if(DEBUG)
              {
                cout<<endl;
               cout<<u<<"# ENJOY 2#"<<v<<endl;
               cout<<posMarked[u]<<"# ENJOY 22#"<<posMarked[v]<<endl;
              }

              if(posMarked[u]==RIGHT&&posMarked[v]==LEFT)

                {
                    //removeEdge(u,v);
                    edgeAll[j].setW(0);
                }
        }

        this->udirected=false;

        if(DEBUG)
        {

        for(int j=0; j<edgeAll.size(); j++)
        {
              int u=edgeAll[j].getU();
              int v=edgeAll[j].getV();
              int w=edgeAll[j].getW();

               cout<<endl;
               if(w!=0)
                {
                    removeEdge(u,v);
                    cout<<u<<"# ENJOY 9#"<<v<<endl;
                    cout<<posMarked[u]<<"# ENJOY 99#"<<posMarked[v]<<endl;

                }
        }



            printFlowMatrix();
            cout<<endl;
            printResMatrix();
            cout<<endl;
            cout<<"# Check Point 1 #\n  BEST of LUCK"<<endl;
        }

        int new1,new2;

        new1=nVertices-1;
        new2=new1-1;

        posMarked[new1]=MID;
        posMarked[new2]=MID;



        for(int j=0; j<edgeAll.size(); j++)
        {
              int u=edgeAll[j].getU();
              int v=edgeAll[j].getV();
              int w=edgeAll[j].getW();

              if(posMarked[u]==LEFT&&posMarked[v]==RIGHT&&w!=0)
              {
                  addEdge(new1,u,1);
                  addEdge(v,new2,1);
              }
              else if((posMarked[u]==RIGHT&&posMarked[v]==LEFT)&&w!=0)
              {
                  addEdge(new1,v,1);
                  addEdge(u,new2,1);
              }
        }

        //as can not remove weight zero

        fordFul(new1,new2);

    }
    else
    {
        cout<<"# The graph is not bipartite #"<<endl;
    }


}

bool Graph::isBip()
{

    for(int i=0;i<nVertices;i++)
    {
        posMarked[i]=MID;
        parD[i]=-1;
        // distance matrix null as unweighted bfs
    }

    posMarked[0]=LEFT;


    if(DEBUG)
    {

        for(int k=0;k<edgeAll.size();k++)
        {
            Edge eg =edgeAll[k];
            cout<<k<<endl;
            cout<<eg.getU()<<"# ENJOY 2#"<<eg.getV()<<endl;
        }
    }

    queue <int> q ;
    q.push(0);

    int now,next;

    while(!q.empty())
    {
        now=q.front();
        q.pop();


        for(int k=0;k<edgeAll.size();k++)
        {
            Edge eg=edgeAll[k];

            if(now==next) return false ;

            if(eg.getU()==now)
            {
                next=eg.getV();

                //cout<<eg.getU()<<"# ENJOY 2#"<<eg.getV()<<endl;



            if(posMarked[next]==MID)
            {
                q.push(next);
                parD[next]=now;

                if(posMarked[now]==LEFT)
                {
                    posMarked[next]=RIGHT;
                }
                else
                {
                    posMarked[next]=LEFT;
                }

            }
            else if(posMarked[now]==posMarked[next])
            {
                return false ;
            }

            }
        }
    }

    return true;
}

void Graph::pmbmEdge()
{
    if(bpGraph)
    {


    ofstream myFile;
    myFile.open ("output.txt");

    cout<<maxFlow<<endl;
    myFile<<maxFlow<<endl;

    for(int j=0; j<edgeAll.size(); j++)
    {
         int u=edgeAll[j].getU();
         int v=edgeAll[j].getV();
         int w=edgeAll[j].getW();


         if(posMarked[u]==LEFT&&posMarked[v]==RIGHT&&flowMatrix[u][v]==1)
         {
            cout<<u<<" "<<v<<endl;
            myFile<<u<<" "<<v<<endl;
         }


    }
    myFile.close();

    }
}

void Graph::printFlowEdge()
{
    ofstream myFile;
    myFile.open ("output.txt");

    cout<<maxFlow<<endl;
    myFile<<maxFlow<<endl;

    for(int j=0; j<edgeAll.size(); j++)
    {
         int u=edgeAll[j].getU();
         int v=edgeAll[j].getV();
         int w=edgeAll[j].getW();

         cout<<u<<" "<<v<<" "<<flowMatrix[u][v]<<"/"<<w<<endl;
         myFile<<u<<" "<<v<<" "<<flowMatrix[u][v]<<"/"<<w<<endl;
    }
    myFile.close();
}

void Graph::printFlowMatrix()
{
    for(int i=0;i<nVertices ;i++)
    {
        for(int j=0;j<nVertices ;j++)
        {
            if(flowMatrix[i][j]==-1)
                cout<<"NIL ";
            else
                cout<<flowMatrix[i][j]+INDEX<<" ";
        }
        cout<<endl;
    }
}

void Graph::printResMatrix()
{
    for(int i=0;i<nVertices ;i++)
    {
        for(int j=0;j<nVertices ;j++)
        {
            if(resMatrix[i][j]==-1)
                cout<<"NIL ";
            else
                cout<<resMatrix[i][j]+INDEX<<" ";
        }
        cout<<endl;
    }
}

bool Graph::bfs(int source,int sink)
{
    if(DEBUG)
    {
         cout<<"# Check P0int 2 #\n  BEST of LUCK"<<endl;
    }


    for(int i=0;i<nVertices;i++)
    {
        colorMarked[i]=WHITE;
        parD[i]=-1;
        // distance matrix null as unweighted bfs
    }

    colorMarked[source]=WHITE;

    queue <int> q ;
    q.push(source);

    int now,next,capacity;

    while(!q.empty())
    {
        now=q.front();
        q.pop();

        for(int k=0;k<edgeAll.size();k++)
        {
            Edge eg =edgeAll[k];

            if(eg.getU()==now)
            {
                next=eg.getV();
                capacity=eg.getW();


            if(resMatrix[now][next]>0&&colorMarked[next]==WHITE)
            {
                q.push(next);
                parD[next]=now;
                colorMarked[next]=BLACK;
            }
            }


        }
    }


    return colorMarked[sink]==BLACK;
}

int Graph::fordFul(int source,int sink)
{
    maxFlow=0;
    int pathFlow=INT_MAX;
    int tra,before,extra,cap;

    if(DEBUG)
    {
        printFlowMatrix();
        cout<<endl;
        printResMatrix();
        cout<<endl;
        cout<<"# Check Point 1 #\n  BEST of LUCK"<<endl;
    }

    //Remember 2D increase Space complexity
    //Remember 2D does not  increase time complexity as we are
    //traversing through adjacency list =)

    for(int j=0; j<edgeAll.size(); j++)
    {
         int u=edgeAll[j].getU();
         int v=edgeAll[j].getV();
         int cap=edgeAll[j].getW();

         if(cap!=0)
         {

         flowMatrix[u][v]=0;
         resMatrix[u][v]=1;
         resMatrix[v][u]=flowMatrix[u][v];
         }
    }

    if(DEBUG)
    {
        printFlowMatrix();
        cout<<endl;
        printResMatrix();
        cout<<endl;
        cout<<"# Check Point 1 #\n  BEST of LUCK"<<endl;
    }

    while(bfs(source,sink))
    {
        for( tra=sink; tra!=source; tra=before)
        {
            before=parD[tra];

            if(resMatrix[before][tra]<pathFlow)
            {
                pathFlow=resMatrix[before][tra];
            }

        }
        for( tra=sink; tra!=source; tra=before)
        {
            before=parD[tra];
            cap=weighVal(before,tra);
            extra=cap-flowMatrix[before][tra];


            if(pathFlow<=extra)
            {
                flowMatrix[before][tra]=flowMatrix[before][tra]+pathFlow;
            }
            else
            {
                flowMatrix[before][tra]=cap;
                flowMatrix[tra][before]=flowMatrix[tra][before]-(pathFlow-extra);

            }

            resMatrix[before][tra]=resMatrix[before][tra]-pathFlow;
            resMatrix[tra][before]=resMatrix[tra][before]+pathFlow;

        }

        if(DEBUG)
        {
            cout<<"Path flow = "<<pathFlow<<endl;
        }

        maxFlow=maxFlow+pathFlow;

    }

    return maxFlow;
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
	flowMatrix=0;
	resMatrix=0;
	udirected = dir ; //set direction of the graph
	//define other variables to be initialized
	colorMarked=new int [10];
	posMarked=new int [10];
	distD=new int[10];
	level=new int[10];
	parD=new int[10];
}

void Graph::setnVertices(int n)
{
	this->nVertices = n+2 ;

	if(colorMarked!=0) delete[] colorMarked ;
	colorMarked=new int [nVertices];

    if(posMarked!=0) delete[] posMarked ;
	posMarked=new int [nVertices];

	if(level!=0) delete[] level ;
	level=new int [nVertices];

    if(distD!=0) delete[] distD ;
    distD=new int [nVertices+1];

    if(parD!=0) delete[] parD ;
    parD=new int [nVertices+1];

    flowMatrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        flowMatrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            flowMatrix[i][j] = -1; //initialize the matrix cells to 0
    }

    resMatrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        resMatrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            resMatrix[i][j] = -1; //initialize the matrix cells to 0
    }


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
    if(u<0 || v<0 ) return; //vertex out of range

    this->nEdges++ ;

    //cout<<u<<" "<<v<<" "<<w<<endl;

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
            //cout<<"Hi"<<endl;
            edgeAll.erase(it);
        }

        if(udirected)
        {
        if((*it).getV()==u&&(*it).getU()==v)
        {
           //cout<<"BYE"<<endl;
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
    if(posMarked) delete [] posMarked;
    if(level) delete [] level;
    if(distD) delete [] distD;
    if(parD) delete [] parD;
    if(flowMatrix) delete [] flowMatrix;
    if(resMatrix) delete [] resMatrix;
    //write your destructor here
}

int main(void)
{
    int vertices , edges ;
    int u , v , w=1;

    Graph g(true);

    if(!FILE)
    {
    cin>>vertices>>edges;

    g.setnVertices(vertices);

    for(int i=0;i<edges;i++)
    {
       // cout<<edges<<endl;

        cin>>u>>v;

        g.addEdge(u,v,w);
    }

    g.mBM();
    g.pmbmEdge();

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


        inFile>>u>>v;

        // cout<<i<<" "<<u<<" "<<v<<" "<<w<<endl;

        g.addEdge(u,v,w);
    }


    inFile.close();


    g.mBM();
    g.pmbmEdge();



    }
    return 0;
}

