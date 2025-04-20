#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter number of students: ";
    cin >> n;
    
    vector<int> marks(n);
    cout << "Enter marks of the students:\n";
    for (int i = 0; i < n; i++) {
        cin >> marks[i];
    }

    priority_queue<int, vector<int>, greater<int>> minHeap;
    priority_queue<int> maxHeap;
    
    for (int i = 0; i < n; i++) {
        minHeap.push(marks[i]);
        maxHeap.push(marks[i]);
    }

    int minMark = minHeap.top();
    int maxMark = maxHeap.top();

    cout << "Minimum marks obtained: " << minMark << endl;
    cout << "Maximum marks obtained: " << maxMark << endl;

    return 0;
}
