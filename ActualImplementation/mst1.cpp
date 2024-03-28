#include<bits/stdc++.h>
using namespace std;

//function to find the minimum spanning tree using prims algorithm
float primsAlgo(vector<vector<pair<int, float>>> &graph, int src = 0)
{
    int n = graph.size();
    float mstval = 0;

    vector<int> parent(n, -1);
    vector<float> key(n, INT_MAX);
    vector<bool> mst(n, false);

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> pq;

    key[src] = 0;
    pq.push({0.00, src});

    while (!pq.empty())
    {
        auto mini = pq.top();
        pq.pop();
        int miniNode = mini.second;
        if (mst[miniNode])
            continue;
        mst[miniNode] = true;
        mstval += mini.first;

        for (auto x : graph[miniNode])
        {
            if (key[x.first] > x.second && mst[x.first] == false)
            {
                key[x.first] = x.second;
                pq.push({key[x.first], x.first});
                parent[x.first] = miniNode;
            }
        }
    }
    return mstval;
}



int main()
{
    //taking the points as input
    cout << "Enter the number of points: ";
    int numberOfPoints;
    cin >> numberOfPoints;
    vector<pair<int, int>> points;
    for (int i = 0; i < numberOfPoints; i++)
    {

        int x, y;
        cout << "Enter the x and y coordinates of point " << i + 1 << " : ";
        cin >> x >> y;
        points.push_back({x, y});
    }

    //constructing the graph

    vector<vector<pair<int,float>>> graph(numberOfPoints);
    
    for(int i=0;i<numberOfPoints;i++)
    {
        vector<pair<int,float>> temp;
        for(int j=0;j<numberOfPoints;j++)
        {
            if(i!=j)
            {
                float distance = sqrt(pow(points[i].first - points[j].first, 2) + pow(points[i].second - points[j].second, 2));
                temp.push_back({j,distance});
            }
        }
        graph[i] = temp; //graph[i] = [ (j1,d1) , (j2,d2) , ... ]

    }

    cout << primsAlgo(graph) << endl;
}