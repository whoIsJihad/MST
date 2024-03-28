#include <bits/stdc++.h>

using namespace std;

bool customComparator(vector<int> &v1, vector<int> &v2)
{
    return v1[2] < v2[2];
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



int krushkalSecondBest(vector<vector<int>>&Edges,int v){
    sort(Edges.begin(),Edges.end(),customComparator);
    vector<int>selected;
    int ans=0;

    DS ds(v);
    int m=Edges.size();


    for(int i=0;i<m;i++){
        int nodeOne=Edges[i][0];
        int nodeTwo=Edges[i][1];
        int weight=Edges[i][2];

        if(ds.find(nodeOne)!=ds.find(nodeTwo)){
            selected.push_back(i);
            ds.Union(nodeOne,nodeTwo);
            ans=ans+weight;
        }
    }

    int secondBest=INT_MAX;

    vector<int>mstVals;

    for(int mstEdge:selected){
        DS ds(v);
        int mstVal=0;
        for(int i=0;i<m;i++){
            if(i==mstEdge){
                continue;
            }
            int nodeOne=Edges[i][0];
            int nodeTwo=Edges[i][1];
            int weight=Edges[i][2];

            if(ds.find(nodeOne)!=ds.find(nodeTwo)){
                ds.Union(nodeOne,nodeTwo);
                mstVal+=weight;
            }
        }
        mstVals.push_back(mstVal);
    }
    return *min_element(mstVals.begin(),mstVals.end());
}

// Driver code
//Find the second best mst

int main(){
    int n,m;
    cin>>n>>m;
    vector<vector<int>>Edges;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin>>u>>v>>w;
        Edges.push_back({u,v,w});
    }
    cout<<krushkalSecondBest(Edges,n);

}