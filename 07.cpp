#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <set>
using namespace std;

class FlightGraph {
private:
    unordered_map<string, vector<pair<string, int>>> adjList;

public:
    void addFlight(string src, string dest, int cost) {
        adjList[src].push_back({dest, cost});
        adjList[dest].push_back({src, cost});
    }

    void displayGraph() {
        for (auto& pair : adjList) {
            cout << pair.first << " --> ";
            for (auto& neighbor : pair.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    bool isConnected() {
        if (adjList.empty()) return true;
        set<string> visited;
        queue<string> q;
        auto start = adjList.begin()->first;
        q.push(start);
        while (!q.empty()) {
            string city = q.front();
            q.pop();
            if (visited.find(city) == visited.end()) {
                visited.insert(city);
                for (auto& neighbor : adjList[city]) {
                    if (visited.find(neighbor.first) == visited.end()) {
                        q.push(neighbor.first);
                    }
                }
            }
        }
        return visited.size() == adjList.size();
    }
};

int main() {
    FlightGraph fg;
    fg.addFlight("A", "B", 3);
    fg.addFlight("A", "C", 1);
    fg.addFlight("B", "D", 2);
    fg.addFlight("C", "D", 4);
    fg.addFlight("D", "E", 2);
    cout << "Flight Path Graph (Adjacency List):" << endl;
    fg.displayGraph();
    if (fg.isConnected()) {
        cout << "\nThe flight network graph is connected." << endl;
    } else {
        cout << "\nThe flight network graph is NOT connected." << endl;
    }
    return 0;
}
