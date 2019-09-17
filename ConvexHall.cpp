#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>
#include <time.h>
using namespace std;

int T, test_case, N, Q, P, Answer, tmp;
long long int Input[1001][2], Qs[101][2];

class Point2D {
public:
	long long int x;
	long long int y;
	Point2D(long long int a, long long int b);
	void setP(long long int a, long long int b);
	static bool ccv(Point2D a, Point2D b, Point2D c); 
	static bool cp_Yc(Point2D a, Point2D b);
	static bool cp_Polar(Point2D a, Point2D b);
	void print() {
		cout << x << " " << y << endl;
	}
};

Point2D p(0,0);
vector <Point2D> vPoints;
stack <Point2D> CH;
vector <Point2D> tmp1;

bool Point2D::cp_Polar(Point2D a, Point2D b) {
	long long int dy1 = a.y - p.y;
	long long int dy2 = b.y - p.y;
	if (dy1==0 && dy2==0) return false;
	else if (dy1>=0 && dy2<0) return false;
	else if (dy2>=0 && dy1<0) return true;
	

	return ccv(p,a,b);
}

bool Point2D::cp_Yc(Point2D a, Point2D b) {
	return  (a.y < b.y);
	
}

bool Point2D::ccv(Point2D a, Point2D b, Point2D c) {
	long long int area2 = (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x);
	if (area2 <= 0) return false; //clockwise 
	return true; //counter-clockwise
	//else return 0; //collinear
}

Point2D::Point2D(long long int a, long long int b) {
	x = a;
	y = b;
};

void Point2D::setP(long long int a, long long int b) {
	x = a;
	y = b;
}


int main(){
	Point2D pTmp(0,0);
	scanf_s("%d", &T);
	clock_t tStart = clock();
	for (test_case = 1; test_case <= T; test_case++) {
		scanf_s("%d", &N);
		memset(Input,0, sizeof(Input));
		memset(Qs,0, sizeof(Qs));
		vPoints.clear();
		for (int i=0; i< N; i++) {
			scanf_s("%lld %lld", &Input[i][0], &Input[i][1]);
			pTmp.setP(Input[i][0], Input[i][1]);
			//cout << Input[i][0] << " " << Input[i][1] << endl;
			//cout << pTmp.x << " " << pTmp.y << endl;

			vPoints.push_back(pTmp);
		}
		scanf_s("%d", &Q);
		for (int i=0; i<Q; i++) {
			scanf_s("%lld %lld", &Qs[i][0], &Qs[i][1]);
		}

		sort(vPoints.begin(), vPoints.end(), Point2D::cp_Yc);
		p.setP(vPoints[0].x, vPoints[0].y);
		sort(vPoints.begin(), vPoints.end(), Point2D::cp_Polar);
		CH.push(vPoints[0]);
		CH.push(vPoints[1]);

		for (int i=2; i<N; i++) {
			Point2D top = CH.top();
			CH.pop();
			while (!CH.empty() && !Point2D::ccv(CH.top(),top, vPoints[i]) ){
				top = CH.top();
				CH.pop();
			}
			CH.push(top);
			CH.push(vPoints[i]);
		}

		tmp1.empty();

		while (!CH.empty()) {
			tmp1.push_back(CH.top());
			CH.pop();
		}
		Answer = 0;
		for (int i=0; i< Q; i++) {
			Point2D qNode(Qs[i][0], Qs[i][1]);
			if (qNode.y>=p.y) {
				vector <Point2D> tmp2(tmp1);
				reverse(tmp2.begin(), tmp2.end());
				tmp2.push_back(qNode);
				//sort(tmp2.begin(),tmp2.end(), Point2D::cp_Yc);
				sort(tmp2.begin(), tmp2.end(), Point2D::cp_Polar);
				if (tmp2.rbegin()->x != qNode.x || tmp2.rbegin()->x != qNode.x) {
					for (int j=0; j<tmp2.size()-1; j++) {
						if (tmp2[j].x == qNode.x && tmp2[j].y == qNode.y) {
							if (Point2D::ccv(tmp2[j-1],tmp2[j], tmp2[j+1])) Answer++;
						}
					}
				} else {
					Answer++;
				}
			} else {
				Answer++;
			}
		}

		cout << "#" << test_case << " " << Answer << endl;
		

		//for (vector <Point2D>::iterator it = vPoints.begin(); it!=vPoints.end(); it++) {
		//	//cout << it->x  << " " << it->y << endl;
		//	it->print();
		//}
	}
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);

	return 0;
}