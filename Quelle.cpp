//	https://www.arndt-bruenner.de/mathe/10/parabeltangente.htm#:~:text=Somit%20ergibt%20sich%20f%C3%BCr%20die%20Tangente%20an%20die,jeden%20Punkt%20x%20durch%202ax%20%2B%20b%20gegeben.

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <initializer_list>

class Point
{
private:
	float mX, mY;
public:
	Point() :
		mX{ 0 },
		mY{ 0 }
	{}
	Point(float x, float y) :
		mX{ x },
		mY{ y }
	{}
	Point(Point const& p) :
		mX{ p.mX },
		mY{ p.mY }
	{}
	Point& operator=(Point const& rhs) {
		mX = rhs.mX;
		mY = rhs.mY;
		return *this;
	}
	float x() const
	{
		return mX;
	}
	float y() const
	{
		return mY;
	}
	void set_x(float xx)
	{
		mX = xx;
	}
	void set_y(float yy)
	{
		mY = yy;
	}
	friend std::ostream&
		operator<<(std::ostream& os, Point const& p) {
		return os << "x = " << p.mX << " y = " << p.mY;
	}
};
class Kurve : public Point {
public:
	std::vector<Point> kur;


public:
	Kurve(std::initializer_list<Point> liste) : kur{ liste } {}
	Kurve(Point p) {
		kur.push_back(p);
	}

	std::vector<Point>& get_kur() {
		return kur;
	}
};


class Segment
{
private:
	Point mA, mB;
public:
	Segment(Point A, Point B) :
		mA{ A }, mB{ B }
	{}
	float A() const		// Coefficient A: y = Ax + B
	{
		return (mA.y() - mB.y()) / (mA.x() - mB.x());
		// source: https://calculis.net/droite
					// A completer
	}
	float B() const		// Coefficient B: y = Ax + B
	{
		return mA.y() - A() * mA.x();
		// source: https://calculis.net/droite
					// A completer
	}
	Point intersection(Segment const& other)
	{
		float x = (other.B() - B()) / (A() - other.A());
		// source: https://calculis.net/intersection
		// A completer

		// A completer
		return Point{ x , A() * x + B() };
	}
	std::string equation() const
	{
		return "y = " + std::to_string(A()) + "x + " + std::to_string(B());
	}
};
int main() {
	Point poiA(0, 0);
	Point poiB(2, pow(2, 2));


	Kurve parabole({ 0,0 });
	for (float i = 0; i < 100; i++)
		parabole.kur.push_back({ i * 0.1f,pow(i * 0.1f,2.0f) });

	float xQ, yQ;
	std::cout << "Veuillez calculer le point à partir duquel la tangente est calculée sur la parabole:   " << std::endl;
	std::cout << "S’il vous plaît x: ";
	std::cin >> xQ;

	std::cout << std::endl;
	std::cout << "S’il vous plaît y: ";
	std::cin >> yQ;
	float aa, bb, cc;
	std::cout << std::endl;
	std::cout << "a * x^2 + b * x + c: S'il vous plait a: " << std::endl;
	std::cin >> aa;
	std::cout << std::endl;
	std::cout << "a * x^2 + b * x + c: S'il vous plait b: " << std::endl;
	std::cin >> bb;
	std::cout << std::endl;
	std::cout << "a * x^2 + b * x + c: S'il vous plait c: " << std::endl;
	std::cin >> cc;
	Kurve parabole_Bsp_1({ 0.0f,0.0f });
	for (float i = -30.0f; i < 100; i++) {
		parabole_Bsp_1.kur.push_back({ i * 0.1f, aa * pow(i * 0.1f,2.0f) + bb * i * 0.1f + cc });
	}

	// Calculer la tangente , Point Q connu Q(-1,-1), La tangente a une forme y = Ax + B , Parabole f(x) = ax^2 + bx +c
	// Point de contact T(xT,yT) , yT = A*xT + B, A est tangente de l’angle de la tangente A = f'(x) = 2ax + b



	// Parabel yT = aaxT^2 + bbxT +cc  ; Tangente yT = (2aaxT +bb) xT + B




	//  https://www.youtube.com/watch?v=ql_w5paclOs

	// f(x)Tangente = f(x)Parabel
	// aax^2 +bx + c = AxO + B = (2 * aa * x + bb) * x + B
	// aa * x^2  + bb * x * xQ + cc = 2 * aa * x^2 + bb * x + B 
	// -aa *  x^2 + (bb * xQ - bb ) * x + 2 * xQ - yQ + 1 = 0



	float a = -aa;

	float b = bb * xQ - bb;

	float c = 2 * xQ - yQ + 1;

	float xT1 = ((-1) * b + std::sqrt(pow(b, 2.0f) - 4 * a * c)) / (2 * a);

	float xT2 = ((-1) * b - std::sqrt(pow(b, 2.0f) - 4 * a * c)) / (2 * a);

	float A1 = -6.0f * xT1 + 2;
	float A2 = -6.0f * xT2 + 2;
	float B1 = yQ - A1 * xQ;
	float B2 = yQ - A2 * xQ;

	float yT1 = A1 * xT1 + B1;
	float yT2 = A2 * xT2 + B2;

	Point Q(xQ, yQ);
	Point T1(xT1, yT1);
	Point T2(xT2, yT2);
	Segment tangente1(Q, T1);
	std::cout << tangente1.equation() << std::endl;
	Segment tangente2(Q, T2);
	std::cout << tangente2.equation() << std::endl;



	std::cout << "Le point de contact de la tangente1 et de la parabole est "
		<< "T1(" << xT1 << ", " << yT1 << ")" << std::endl;
	std::cout << "Le point de contact de la tangente1 et de la parabole est "
		<< "T2(" << xT2 << ", " << yT2 << ")" << std::endl;


	auto it = parabole_Bsp_1.kur.begin();
	while (it != parabole_Bsp_1.kur.end()) {
		std::cout << "parabole(x, y) " << *it++ << std::endl;

	}
	std::cout << "Hiperbole " << std::endl;
	Kurve hiperbole({ 0,0 });
	for (float i = 0; i < 100; i++)
		hiperbole.kur.push_back({ i * 0.1f,pow(i * 0.1f,.5f) });





	auto it_h = hiperbole.kur.begin();
	while (it_h != hiperbole.kur.end()) {
		std::cout << *it_h++ << std::endl;

	}


	Point pA(3.5f, 4.0f);
	Point pB(-4.0f, 2.0f);
	Point pC(2.0f, -2.0f);
	Point pD(-2.0f, 5.0f);
	std::cout << "Point d'intersection des deux lignes droites: " << std::endl;
	Segment Line1(pA, pB);
	std::cout << Line1.equation() << std::endl;
	Segment Line2(pC, pD);
	std::cout << Line2.equation() << std::endl;

	std::cout << Line1.intersection(Line2);	// Point d'intersection des deux lignes droites	
}