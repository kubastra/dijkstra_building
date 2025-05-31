#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <limits>
#include <string>


using namespace std;
const int INF = numeric_limits<int>::max();

vector<int> dijkstra(int startRoom, const vector<vector<pair<int, int>>>& graph) {
    int numRooms = graph.size();

    vector<int> shortestTime(numRooms, INF);
    shortestTime[startRoom] = 0;

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    pq.push({0, startRoom});

    while (!pq.empty()) {

        int currentTime = pq.top().first;
        int currentRoom = pq.top().second;
        pq.pop();

        if (currentTime > shortestTime[currentRoom])
            continue;

        for (auto [neighbor, timeToNeighbor] : graph[currentRoom]) {
            int newTime = currentTime + timeToNeighbor;

            if (newTime < shortestTime[neighbor]) {
                shortestTime[neighbor] = newTime;
                pq.push({newTime, neighbor});
            }
        }
    }
    return shortestTime;
}


int main() {
    vector<string> names = {"A","B","C","D","E","F","G","H","I","J"};
    unordered_map<string,int> id;
    for (int i = 0; i < (int)names.size(); ++i)
        id[names[i]] = i;

    int n = names.size();
    vector<vector<pair<int,int>>> adj(n);

    auto addEdge = [&](const string& u, const string& v, int w){
        int ui = id[u], vi = id[v];
        adj[ui].push_back({vi,w});
        adj[vi].push_back({ui,w});
    };

    addEdge("A","B",3);
    addEdge("B","C",2);
    addEdge("C","H",2);
    addEdge("H","I",2);
    addEdge("H","J",1);
    addEdge("H","G",1);
    addEdge("H","F",2);
    addEdge("F","G",1);
    addEdge("F","E",1);
    addEdge("E","D",1);
    addEdge("D","B",1);

    vector<int> distA = dijkstra(id["A"], adj);
    vector<int> distJ = dijkstra(id["J"], adj);

    cout << "Pomieszczenie\tCzas do A\tCzas do J\n";
    for (int i = 0; i < n; ++i) {
        cout << names[i] << "\t\t";
        if (distA[i] == INF) cout << "∞"; else cout << distA[i];
        cout << "\t\t";
        if (distJ[i] == INF) cout << "∞"; else cout << distJ[i];
        cout << "\n";
    }
    return 0;
}
