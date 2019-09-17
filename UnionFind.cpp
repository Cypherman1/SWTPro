#include <iostream>
#include <time.h>
#include <set>
#include <stack>

using namespace std;

int N, M, Q, T, test_case, Answer, tf, tps, tp, tq, tmp;
int ufA[100001][2], PQ[100001][3];
set<int> s;
stack<int> res;

/*Union Find class*/

class UF {
	int id[100001];
	int N;
	int uF_root(int p);
	int sz[100001];
public:
	UF(int n);
	void uF_union(int p, int q);
	int uF_find(int p, int q);
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


int UF::uF_find(int p, int q) {
	return uF_root(p) == uF_root(q) ? 1 : 0 ;
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

int main(){
	scanf("%d", &T);
	clock_t tStart = clock();
	for (test_case = 1; test_case<= T; test_case++) {
		scanf("%d %d", &N, &M);
		memset(ufA,0,sizeof(ufA));
	    memset(PQ, 0, sizeof(PQ));
		for (int i=0; i<M; i++) {
			scanf("%d %d", &ufA[i][0], &ufA[i][1]);
			ufA[i][0]--;
			ufA[i][1]--;
		}
		scanf("%d", &Q);
		for (int i=0; i<Q; i++) {
			scanf("%d", &tf);
			if (tf==1) {
				scanf("%d", &tps);
				PQ[i][0] = tf;
				PQ[i][1] = --tps;
				s.insert(PQ[i][1]);
			} else if (tf==2) {
				scanf("%d %d", &tp, &tq);
				PQ[i][0] = tf;
				PQ[i][1] = --tp;
				PQ[i][2] = --tq;
			}
		}

		UF uf(N);

		for (int i=0; i< M; i++) {
			if(s.find(i) == s.end()){
				uf.uF_union(ufA[i][0], ufA[i][1]);
			}
		}

		cout << "#" << test_case << " ";

		for (int i=Q-1; i>=0; i--) {
			if (PQ[i][0] == 2) {
				res.push(uf.uF_find(PQ[i][1], PQ[i][2]));
			} else if (PQ[i][0] == 1) {
				uf.uF_union(ufA[PQ[i][1]][0], ufA[PQ[i][1]][1]);
			}
		}

		/*for (int i = 0; i< Q; i++) {
			if (PQ[i][0] == 2) {
				uf.uF_find(PQ[i][1], PQ[i][2]);
			}
		}*/

		while (!res.empty()) {
			tmp = res.top();
			cout << tmp;
			res.pop();
		}

		cout << endl;
	}
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	return 0;
}