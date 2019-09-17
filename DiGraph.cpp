#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

int V, E;
int input[1000][2];

/*BEGIN Graph class */

class DGraph {
	int V;
	int E;
public:
	vector<int> adj[1000];
	DGraph(int Vx);
	void addEdge(int v, int w);
	void printDG();
	DGraph reverse();
	bool isCycle();
	int getV(){
		return V;
	}
};

DGraph DGraph::reverse() {
	DGraph G(V);
	for (int i=0; i < V; i++) {
		for (vector<int>::iterator it= adj[i].begin(); it != adj[i].end(); it++) {
			G.addEdge(*it,i);
		}
	}
	return G;
}


bool DGraph::isCycle(){
	// Create a vector to store indegrees of all 
    // vertices. Initialize all indegrees as 0. 
    vector<int> in_degree(V, 0); 
	vector<int>::iterator it;
  
    // Traverse adjacency lists to fill indegrees of 
    // vertices. This step takes O(V+E) time 
    for (int u = 0; u < V; u++) { 
		for (it  = adj[u].begin(); it!=adj[u].end(); it++) 
            in_degree[*it]++; 
    } 
  
    // Create an queue and enqueue all vertices with 
    // indegree 0 
    queue<int> q; 
    for (int i = 0; i < V; i++) 
        if (in_degree[i] == 0) 
            q.push(i); 
  
    // Initialize count of visited vertices 
    int cnt = 0; 
  
    // Create a vector to store result (A topological 
    // ordering of the vertices) 
    vector<int> top_order; 
  
    // One by one dequeue vertices from queue and enqueue 
    // adjacents if indegree of adjacent becomes 0 
    while (!q.empty()) { 
  
        // Extract front of queue (or perform dequeue) 
        // and add it to topological order 
        int u = q.front(); 
        q.pop(); 
        top_order.push_back(u); 
  
        // Iterate through all its neighbouring nodes 
        // of dequeued node u and decrease their in-degree 
        // by 1 
        vector<int>::iterator itr; 
        for (itr = adj[u].begin(); itr != adj[u].end(); itr++) 
  
            // If in-degree becomes zero, add it to queue 
            if (--in_degree[*itr] == 0) 
                q.push(*itr); 
  
        cnt++; 
    } 
  
    // Check if there was a cycle 
    if (cnt != V)  
        return true; 
    else
        return false;
}

DGraph::DGraph(int Vx) {
	V = Vx;
	E=0;
	for (int i=0; i<V; i++) {
		vector<int> tmp;
		adj[i] = tmp;
	}
}

void DGraph::addEdge(int v, int w) {
	E++;
	adj[v].push_back(w);
}

void DGraph::printDG() {
	for (int i=0; i< V; i++) {
		for (vector<int>::iterator it = adj[i].begin(); it != adj[i].end(); it++) {
			cout << i << " " << *it << endl;
		}
	}
}

/*END Graph class */

/*BEGIN DFS */

class DFSPaths {
	int s;
	bool marked[1000];
	int edgeTo[1000];
	void dfs(DGraph G, int v);
public:
	DFSPaths(DGraph G, int v);
	bool hasPathTo(int v);
	vector<int> pathTo(int v);
};

bool DFSPaths::hasPathTo(int v) {
	return marked[v];
}

vector<int> DFSPaths::pathTo(int v) {
	vector<int> path;
	if (!hasPathTo(v)) return path;
	for (int x = v; x!=s; x = edgeTo[x]) {
		path.push_back(x);
	}
	path.push_back(s);
	reverse(path.begin(), path.end());
	return path;
}

DFSPaths::DFSPaths(DGraph G, int v) {
	s = v;
	memset(marked, false, sizeof(marked));
	memset(edgeTo, -1, sizeof(edgeTo));
	dfs(G, s);
}

void DFSPaths::dfs(DGraph G, int v) {
	marked[v] = true;
	for (vector<int>::iterator it=G.adj[v].begin(); it != G.adj[v].end(); it++) {
		if (!marked[*it]) {		
			dfs(G, *it);
			edgeTo[*it] = v;
		}
	}
}

/*END DFS*/

/*BEGIN BFS*/
class BFSPaths{
	int s;
	bool marked[1000];
	int edgeTo[1000];
	void bfs(DGraph G, int v);
public:
	BFSPaths(DGraph G, int v);
	bool hasPathTo(int v);
	vector<int> pathTo(int v);
};

BFSPaths::BFSPaths(DGraph G, int v) {
	s = v;
	memset(marked, false, sizeof(marked));
	memset(edgeTo, -1, sizeof(edgeTo));
	bfs(G, s);
}

void BFSPaths::bfs(DGraph G, int v) {
	queue<int> bfsq;
	marked[v] = true;
	bfsq.push(v);
	while (!bfsq.empty()) {
		int tmp = bfsq.front();
		bfsq.pop();
		for (vector<int>::iterator it=G.adj[tmp].begin(); it!=G.adj[tmp].end(); it++) {
			if(!marked[*it]) {
				bfsq.push(*it);
				edgeTo[*it] = tmp;
				marked[*it] = true;
			}
		}
	}
}

bool BFSPaths::hasPathTo(int v) {
	return marked[v];
}

vector<int> BFSPaths::pathTo(int v) {
	vector<int> path;
	if (!hasPathTo(v)) return path;
	for (int i= v; i != s; i = edgeTo[i]) {
		path.push_back(i);
	}
	path.push_back(s);
	reverse(path.begin(), path.end());
	return path;
}

/*END BFS */

/*BEGIN Topo sort*/ 

class DFOrder {
	bool marked[1000];
public:
	stack<int> reversePost;
	DFOrder(DGraph G) {
		while(!reversePost.empty()) {
			reversePost.pop();
		}
		memset(marked, false, sizeof(marked));
		for (int v = 0; v< G.getV(); v++) 
			if (!marked[v])
				dfs(G,v);
			
	};
	void dfs(DGraph G, int v) {
		marked[v] = true;
		for (vector<int>::iterator it=G.adj[v].begin(); it != G.adj[v].end(); it++)
			if (!marked[*it])		
				dfs(G, *it);
		reversePost.push(v);
	}
	void printTO() {
		while (!reversePost.empty()) {
			int tmp = reversePost.top();
			reversePost.pop();
			cout << tmp << " ";
		}
		cout << endl;
	}
};

/* END topo sort*/

/* BEGIN Connected component */
class CC {
	bool marked[1000];
	int id[1000];
	int count;
public:
	CC(DGraph G) {
		memset(marked, false, sizeof(marked));
		memset(id, 0, sizeof(id));
		count =0;

		DFOrder DFO(G.reverse());

		while (!DFO.reversePost.empty()) {
			int tmp = DFO.reversePost.top();
			DFO.reversePost.pop();
			if (!marked[tmp]) {
				dfs(G,tmp);
				count++;
			}
		}
	};
	void dfs(DGraph G, int v) {
		marked[v] = true;
		id[v]= count;
		for (vector<int>::iterator it = G.adj[v].begin(); it != G.adj[v].end(); it++) {
			if (!marked[*it]) {
				dfs(G, *it);
			}
		}
	};
	bool isConnected(int v, int w) {
		return id[v]==id[w];
	};
};

/* END Connected component*/
int main() {
	scanf_s("%d %d", &V, &E);
	for (int i=0; i<E; i++) {
		scanf_s("%d %d", &input[i][0], &input[i][1]);
	}

	DGraph G(V);

	for (int i=0; i<E; i++) {
		G.addEdge(input[i][0], input[i][1]);
	}

	G.printDG();

	DFSPaths DFS(G, 0);

	BFSPaths BFS(G,0);

	vector<int> tmp = DFS.pathTo(2);
	vector<int> tmp1 = BFS.pathTo(2);

	cout << "DFS:" ;
	for (vector<int>::iterator it = tmp.begin(); it!=tmp.end(); it++) {
		cout << *it << " ";
	}

	cout << endl;

	cout << "BFS:" ;
	for (vector<int>::iterator it = tmp1.begin(); it!=tmp1.end(); it++) {
		cout << *it << " ";
	}

	cout << endl;
	
	cout << G.isCycle();
	cout << endl;

	//DFOrder DFO(G);
	//DFO.printTO();

	CC c(G);

	cout << c.isConnected(0,1);

	cout << endl;
	//G.printUG();

	return 0;
}