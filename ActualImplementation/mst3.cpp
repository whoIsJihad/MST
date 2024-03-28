#include <bits/stdc++.h>
#define exp 1000000000
using namespace std;

//modified to sort desc
bool customComparator(vector<int> &v1, vector<int> &v2)
{
    return v1[2] > v2[2];
}

class DS
{
    vector<int> parent;
    vector<int> rank;

public:
    DS(int v)
    {
        parent.resize(v);
        rank.resize(v);
        for (int i = 0; i < v; i++)
        {
            parent[i] = i;
            rank[i] = 0;
        }
    }
    // finding the representative element
    int find(int i)
    {
        if (parent[i] == i)
            return i;
        return parent[i] = find(parent[i]);
    }
    // union by path compression

    void Union(int a, int b)
    {
        int sa = find(a);
        int sb = find(b);

        if (sa != sb)
        {
            if (rank[sa] > rank[sb])
            {
                parent[sb] = sa;
            }
            else if (rank[sa] < rank[sb])
            {
                parent[sa] = sb;
            }

            else
            {
                parent[sa] = sb;
                rank[sb]++;
            }
        }
    }
};

int KOICOST(vector<vector<int>>&Edges,int n,int a ,int b){
    sort(Edges.begin(),Edges.end(),customComparator);
    int ans=0;

    DS ds(n);

    for(auto edge:Edges){
        int nodeOne=edge[0];
        int nodeTwo=edge[1];
        int weight=edge[2];

        if(ds.find(nodeOne)!=ds.find(nodeTwo)){
            ds.Union(nodeOne,nodeTwo);
            ans+=weight;
        }
        else{
            ans+=weight;
        }
        if(ds.find(a)==ds.find(b)){
            ans=ans-weight;
            break;
        }
    }
    //summing all edge weight
    int edgeSum=0;
    for(auto edge:Edges){
        edgeSum+=edge[2];
    }

    return edgeSum-ans;
}

int main(){
    int n,m,a,b;
    cin>>n>>m;
    vector<vector<int>> Edges;
    for(int i=0;i<m;i++){
        int x,y,z;
        cin>>x>>y>>z;
        x--;
        y--;
        Edges.push_back({x,y,z});
    }

    int koicost=0;

    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            if(i<j){
                a=i;
                b=j;
                koicost = (koicost%exp + KOICOST(Edges, n, a, b)%exp)%exp;
   
            }
        }
    }
    cout<<koicost<<endl;
    return 0;
}

/*
test case

6 7
1 2 10
2 3 2
2 6 6
3 6 15
3 4 5
4 5 3
3 5 4
*/
