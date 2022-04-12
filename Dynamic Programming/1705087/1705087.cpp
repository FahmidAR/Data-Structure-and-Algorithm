#include <bits/stdc++.h>
using namespace std;

#define DBG 0


char* LCS(string a,string b)
{
    int row = a.length();
    int col = b.length();

    int c[row+1][col+1];
    char d[row+1][col+1];

    for(int i=0;i<=row;i++)
    {
        c[i][0]=0;
        d[i][0]='O';
    }


    for(int j=0;j<=col;j++)
    {
        c[0][j]=0;
        d[0][j]='O';
    }


    for(int i=1;i<=row;i++)
    {
        for(int j=1;j<=col;j++)
        {
            if(a[i-1]==b[j-1])
            {
                c[i][j]=c[i-1][j-1]+1;
                d[i][j]='D';
            }

            else if(c[i-1][j]>=c[i][j-1])
            {
                c[i][j]=c[i-1][j];
                d[i][j]='U';
            }
            else
            {
                c[i][j]=c[i][j-1];
                d[i][j]='L';
            }
        }


    }

    if(DBG)
    {

    for(int i=0;i<=row;i++)
    {
        for(int j=0;j<=col;j++)
        {
            cout<<c[i][j]<<" ";
        }
        cout<<endl;
    }

    cout<<endl;

     for(int i=0;i<=row;i++)
    {
        for(int j=0;j<=col;j++)
        {
            cout<<d[i][j]<<" ";
        }
        cout<<endl;
    }

    }

    int rr=row;
    int cc=col;
    int lcsL=c[row][col];
    char *lcsS=new char[lcsL+1];
    lcsS[lcsL]='\n';

    while(rr>0&&cc>0)
    {
        if(a[rr-1]==b[cc-1])
        {
            lcsS[lcsL-1]=a[rr-1];
            rr=rr-1;
            cc=cc-1;
            lcsL=lcsL-1;
        }
        else if(c[rr-1][cc]>c[rr][cc-1])
            rr=rr-1;
        else
            cc=cc-1;
    }

    return lcsS;

}

int main()
{
    //string a="ABCBDAE",b="BDCABA",c;
    string a,b,c;
    cin>>a>>b;
    cout<<"First Input = "<<a<<"\nSecond Input = "<<b<<endl;
    //cout<<a.length()<<" "<<b.length()<<endl;


    cout<<"Longest Common Subsequence = "<<LCS(a,b)<<endl;


    return 0;
}
