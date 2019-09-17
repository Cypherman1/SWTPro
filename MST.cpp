#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <stack>
using namespace std;

int V, E;
int input[1000][2];
double dinput[1000];

/*Begin Edge class */

class Edge {
	int v, w;
	
public:
	double weight;
	Edge(int iv, int iw, double iweight) {
		v = iv;
		w = iw;
		weight = iweight;
	};
	int either() {
		return v;
	};
	int other(int vertex) {
		if (vertex == v) return w;
		else return v;
	};
	static int cmp(Edge me, Edge that) {
		if (me.weight < that.weight) return -1;
		else if (me.weight > that.weight) return 1;
		else return 0;
	};
	bool operator<(const Edge &that) const {
		return weight > that.weight;
	};
	/*bool operator()(const Edge &e1, const Edge &e2) const{
		return e1.weight > e2.weight;
	};*/

	bool operator()(const Edge &lhs, const Edge &rhs) const
	{
		return lhs.weight > rhs.weight;
	}
	void printE() {
		cout << v << " " << w << " " << weight << endl;
	};
};

/*End Edge class*/

/*Begin EWGraph class*/

class EWGraph {
	int V;
public:
	vector<Edge> adj[1000];
	vector<Edge> edges;
	EWGraph(int iV) {
		V = iV;
		edges.clear();
		for (int i=0; i<V; i++) {
			vector<Edge> tmp;
			adj[i] = tmp;
		}
	};
	void addEdge(Edge e) {
		int v = e.either();
		int w = e.other(v);
		adj[v].push_back(e);
		adj[w].push_back(e);
		edges.push_back(e);
	};
	int getV() {
		return V;
	};
};

/*End EWGraph*/

/*Union Find class*/

class UF {
	int id[100001];
	int N;
	int uF_root(int p);
	int sz[100001];
public:
	UF(int n);
	void uF_union(int p, int q);
	bool uF_find(int p, int q);
};

UF::UF(int n) {
	memset(id,0, sizeof(id));
	memset(sz,0, sizeof(id));
	N = n;
	for (int i=0; i<N; i++) {
		id[i] = i;
	}
};

int UF::uF_root(int x) {
	while (x != id[x]) {
		id[x] = id[id[x]];
		x = id[x];
	}
	return x;
};


bool UF::uF_find(int p, int q) {
	return uF_root(p) == uF_root(q) ;
};

void UF::uF_union(int p, int q) {
	int qr = uF_root(q);
	int pr = uF_root(p);
	if (qr==pr) return;
	if(sz[qr] < sz[pr]) {
		id[qr] = pr;
		sz[pr]+=sz[qr];
	} else {
		id[pr] = qr;
		sz[qr]+=sz[pr];
	}
	//id[pr] = qr;
}

/*End Union Find*/

struct Node {
	int v, w,  weight;
};

struct comp
{
	bool operator()(const Node &lhs, const Node &rhs) const
	{
		return lhs.weight > rhs.weight;
	}
};

/*Begin Kruskal*/
class KruskalMST {
	
public:
	queue<Edge> mst;
	KruskalMST(EWGraph G) {
		while(!mst.empty()) {
			mst.pop();
		}
		priority_queue<Edge> pq;
		for (vector<Edge>::iterator it = G.edges.begin(); it!=G.edges.end(); it++) {
			pq.push(*it);
		}
		UF uf(G.getV());
		while (!pq.empty() && mst.size() < G.getV()-1) {
			Edge e = pq.top();
			pq.pop();
			int v = e.either();
			int w = e.other(v);
			if (!uf.uF_find(v,w)) {
				uf.uF_union(v,w);
				mst.push(e);
			}
		}
	}
	
};
/*End Kruskal*/

/*Begin Lazy Prim*/

class LazyPrimMST {
	bool marked[1000];
	priority_queue<Edge> pq;
	void visit(EWGraph G, int v) {
		marked[v] = true;
		for (int i=0; i< G.adj[v].size(); i++) {
			if (!marked[G.adj[v][i].other(v)]) {
				pq.push(G.adj[v][i]);
			}
		}
	};
public:
	queue<Edge> mst;
	LazyPrimMST(EWGraph G) {
		while(!pq.empty()) pq.pop();
		while(!mst.empty()) mst.pop();
		memset(marked, false, sizeof(marked));
		visit(G,0);
		while (!pq.empty()) {
			Edge e = pq.top();
			pq.pop();
			int v = e.either();
			int w = e.other(v);
			if (!marked[v] && !marked[w]) continue;
			mst.push(e);
			if (!marked[v]) visit(G, v);
			if (!marked[w]) visit(G, w);
		}
	}
};

/*End Lazy Prim*/




int main() {
	scanf_s("%d %d", &V, &E);
	for (int i=0; i<E; i++) {
		scanf_s("%d %d", &input[i][0], &input[i][1]);
		scanf_s("%lf", &dinput[i]);
	}

	EWGraph G(V);
	for (int i=0; i< E; i++) {
		Edge e(input[i][0], input[i][1], dinput[i]);
		G.addEdge(e);
	}

	cout << "Kruskal MST:" << endl;

	KruskalMST KMST(G);

	while (!KMST.mst.empty()) {
		Edge tmp = KMST.mst.front();
		KMST.mst.pop();
		tmp.printE();
	};

	cout << "Prim lazy MST:" << endl;

	LazyPrimMST LPMST(G);
	while (!LPMST.mst.empty()) {
		Edge tmp = LPMST.mst.front();
		LPMST.mst.pop();
		tmp.printE();
	}

	return 0;
}