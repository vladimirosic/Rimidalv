//: C10:MessengerDemo.cpp
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <math.h>
using namespace std;

class Point { // Un mesenger
public:
	float x, y, z; // Puisque c’est juste un transporteur
	Point() { x = 0.0; y = 0.0; z = 0.0; }
	Point(float xi, float yi, float zi) : x(xi), y(yi), z(zi) {}
	Point(const Point& p) : x(p.x), y(p.y), z(p.z) {}
	Point& operator=(const Point rhs) {
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return *this;
	}
	friend ostream&
		operator<<(ostream& os, const Point& p) {
		return os << " x=" << p.x << " y=" << p.y << " z=" << p.z;
	}
};

class Vector { // Mathematical vector
public:
	float magnitude, angleAlfa, angleBeta, angleGama;
	Vector(float m, float angleAlf, float angleBet, float angleGam) : magnitude(m), angleAlfa(angleAlf), angleBeta(angleBet)
	,angleGama (angleGam) {}
};
class Line  {	//?!?
	Point po1, po2;
public:
	Line(Point poi1, Point poi2) : po1{ poi1 }, po2{ poi2 }{}
	float coin() { return atan((po2.y - po1.y) / (po2.x - po1.x)); }

	float x2_x1() const {
		return (po2.x - po1.x);
	}
	float y2_y1() const {
		return (po2.y - po1.y);
	}
	float x3y4_y3x4( Line li2) const {
		return (li2.po1.x * li2.po2.y - li2.po1.y * li2.po2.x);
	}
	float x1y2_y1x2() const{
		return (po1.x * po2.y - po1.y * po2.x);
	}
	float dénominateur(Line li2) const{ return (x2_x1() * y4_y3(li2) - y2_y1() * x4_x3(li2)); }
	
	float x4_x3(Line lin2) const { return (lin2.po2.x - lin2.po1.x); }
	float y4_y3(Line lin2) const{ return (lin2.po2.y - lin2.po1.y); }
	Point& intersection(Line li2);
};
Point po;
Point& Line::intersection(Line li2) {
	
	po.x = (x2_x1() * x3y4_y3x4(li2) - x4_x3(li2) * x1y2_y1x2())
		/ dénominateur(li2);
	po.y = (y2_y1() * x3y4_y3x4(li2) - y4_y3(li2) * x1y2_y1x2())
		/ dénominateur(li2);
	return po;
}

class Space {
public:
	static Point translate(Point p, Vector v) {
		// Copy-constructeur empêche la modification de l’original,
		// A dummy calculation:
		p.x += v.magnitude * cos(v.angleAlfa);
		p.y += v.magnitude * cos(v.angleBeta);
		p.z += v.magnitude * cos(v.angleGama);
		return p;
	}
};

int main() {
	Point A(1, 2, 3);
	Point B = Space::translate(A, Vector(11.1e0, 47.2e0,33.5e0, 23.4e0));
	Point C = Space::translate(B, Vector(5.5e0, 8.8e0 ,55.7e0, 6.7e0));
	Point D(B);
	cout << "A: " << A << " B: " << B << " C: " << C << " D: " << D << endl;
	A = B;
	cout << "A après A = B: " << A << endl;
	vector<Point> wer;
	wer.push_back(A);
	wer.push_back(B);
	wer.push_back(C);
	wer.push_back(D);
	vector<Point>::iterator it = wer.begin();
	while (it != wer.end()) {
		cout << it->x << endl;
		++it;
	}
	
	Point pA(3.5, 4, 0);
	Point pB(-4, 2, 0);
	Point pC(2, -2, 0);
	Point pD(-2.0, 5, 0);
	cout << "test pA : " << pA << endl;

	Line gérades1(pA, pB);
	Line gérades2(pC, pD);
	
	cout <<  gérades1.intersection( gérades2) << endl;	//	intersection_d_deux_lignes_droites
	Point pP(7.5,-3, 0);
	Point pQ(-5.5, 4, 0);
	Point pR(5, 3, 0);
	Point pS(-1, -6, 0);

	Line gérades3(pP, pQ);
	Line gérades4(pR, pS);

	cout << gérades3.intersection(gérades4);	//	intersection_d_deux_lignes_droites

} ///~

