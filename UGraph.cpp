#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int V, E;
int input[1000][2];

/*BEGIN Graph class */

class UGraph {
	int V;
	int E;
public:
	vector<int> adj[1000];
	UGraph(int Vx);
	void addEdge(int v, int w);
	void printUG();
	int getV() {
		return V;
	}
};

UGraph::UGraph(int Vx) {
	V = Vx;
	E=0;
	for (int i=0; i<V; i++) {
		vector<int> tmp;
		adj[i] = tmp;
	}
}

void UGraph::addEdge(int v, int w) {
	E++;
	adj[v].push_back(w);
	adj[w].push_back(v);
}

void UGraph::printUG() {
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
	void dfs(UGraph G, int v);
public:
	DFSPaths(UGraph G, int v);
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

DFSPaths::DFSPaths(UGraph G, int v) {
	s = v;
	memset(marked, false, sizeof(marked));
	memset(edgeTo, -1, sizeof(edgeTo));
	dfs(G, s);
}

void DFSPaths::dfs(UGraph G, int v) {
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
	void bfs(UGraph G, int v);
public:
	BFSPaths(UGraph G, int v);
	bool hasPathTo(int v);
	vector<int> pathTo(int v);
};

BFSPaths::BFSPaths(UGraph G, int v) {
	s = v;
	memset(marked, false, sizeof(marked));
	memset(edgeTo, -1, sizeof(edgeTo));
	bfs(G, s);
}

void BFSPaths::bfs(UGraph G, int v) {
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

/*bool isBipartite(vector<int> adj[], int v, 
                 vector<bool>& visited, vector<int>& color) 
{ 
  
    for (int u : adj[v]) { 
  
        // if vertex u is not explored before 
        if (visited[u] == false) { 
  
            // mark present vertic as visited 
            visited[u] = true; 
  
            // mark its color opposite to its parent 
            color[u] = !color[v]; 
  
            // if the subtree rooted at vertex v is not bipartite 
            if (!isBipartite(adj, u, visited, color)) 
                return false; 
        } 
  
        // if two adjacent are colored with same color then 
        // the graph is not bipartite 
        else if (color[u] == color[v]) 
            return false; 
    } 
    return true; 
} */

class CC {
	bool marked[1000];
	int id[1000];
	int count;
public:
	CC(UGraph G) {
		memset(marked, false, sizeof(marked));
		memset(id, 0, sizeof(id));
		count =0;
		for (int v=0; v<G.getV(); v++) {
			if (!marked[v]) {
				dfs(G, v);
				count ++;
			}
		}
	};
	void dfs(UGraph G, int v) {
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

int main() {
	scanf_s("%d %d", &V, &E);
	for (int i=0; i<E; i++) {
		scanf_s("%d %d", &input[i][0], &input[i][1]);
	}

	UGraph G(V);

	for (int i=0; i<E; i++) {
		G.addEdge(input[i][0], input[i][1]);
	}

	// G.printUG();

	/*DFSPaths DFS(G, 0);

	BFSPaths BFS(G,0);

	vector<int> tmp = DFS.pathTo(6);
	vector<int> tmp1 = BFS.pathTo(6);

	cout << "DFS:" ;
	for (vector<int>::iterator it = tmp.begin(); it!=tmp.end(); it++) {
		cout << *it << " ";
	}

	cout << endl;

	cout << "BFS:" ;
	for (vector<int>::iterator it = tmp1.begin(); it!=tmp1.end(); it++) {
		cout << *it << " ";
	}*/

	CC c(G);
	cout << c.isConnected(0,11);

	cout << endl;
	//G.printUG();

	return 0;
}