//	https://www.arndt-bruenner.de/mathe/10/parabeltangente.htm#:~:text=Somit%20ergibt%20sich%20f%C3%BCr%20die%20Tangente%20an%20die,jeden%20Punkt%20x%20durch%202ax%20%2B%20b%20gegeben.

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <iterator>
#include <initializer_list>
#include <numeric>

bool isNumeric(std::string str) {
	for (int i = 0; i < str.length(); i++)
		if (isdigit(str[i]) == false)
			return false; //when one non numeric value is found, return false
	return true;
}

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

bool  saisie_non_valide{};
float  valeur_attendue;
std::string str;
float eingabe() {
	do {
		std::string  str;
		std::cin >> str;         // lire une ligne sans polluer le flux std::cin
		std::istringstream  iss{ str };     // début de l'analyse
		// analyser avec iss par exemple:
		saisie_non_valide = true;
		if (!(iss >> valeur_attendue)) {
			std::cout << "valeur numérique attendue, recommencez";
		}
		else if (valeur_attendue > std::numeric_limits<float>::max() || valeur_attendue < -std::numeric_limits<float>::max())
			std::cout << "valeur numérique hors limite, recommencez";
		else
			saisie_non_valide = false;

	} while (saisie_non_valide);
	return valeur_attendue;
}
int main() {
	Point poiA(0, 0);
	Point poiB(2, pow(2.0f, 2.0f));
	std::cout << "std::numeric_limits<float>::min(): " << std::numeric_limits<float>::min();

	Kurve parabole({ 0,0 });
	for (float i = 0; i < 100; i++)
		parabole.kur.push_back({ i * 0.1f,pow(i * 0.1f,2.0f) });


	float xQ, yQ;
	std::cout << "Veuillez calculer le point à partir duquel la tangente est calculée sur la parabole:   " << std::endl;
	std::cout << "S’il vous plaît x: ";
	xQ = eingabe();



	std::cout << std::endl;
	std::cout << "S’il vous plaît y: ";
	yQ = eingabe();


	float aa, bb, cc;

	std::cout << std::endl;
	std::cout << "a * x^2 + b * x + c: S'il vous plait a: " << std::endl;
	aa = eingabe();
	std::cout << std::endl;
	std::cout << "a * x^2 + b * x + c: S'il vous plait b: " << std::endl;
	bb = eingabe();
	std::cout << std::endl;
	std::cout << "a * x^2 + b * x + c: S'il vous plait c: " << std::endl;
	cc = eingabe();
	Kurve parabole_Bsp_1({ 0.0f,0.0f });
	for (float i = -30.0f; i < 100; i++) {
		parabole_Bsp_1.kur.push_back({ i * 0.1f, aa * pow(i * 0.1f,2.0f) + bb * i * 0.1f + cc });
	}

	// Calculer la tangente , Point Q connu Q(-1,-1), La tangente a une forme y = Ax + B , Parabole f(x) = ax^2 + bx +c
	// Point de contact T(xT,yT) , yT = A*xT + B, A est tangente de l’angle de la tangente A = f'(x) = 2ax + b



	// Parabel yT = aa * xT^2 + bb * xT + cc  ; Tangente yT = (2aa * xT +bb) * xT + B




	//  https://www.youtube.com/watch?v=ql_w5paclOs

	// f(x)Tangente = f(x)Parabel
	// aax^2 +bbx + cc = AxO + B = (2 * aa * x + bb) * x + B ; A = 2 * aa * x + bb
	// aa * x^2  + bb * x  + cc = 2 * aa * x^2 + bb * x + B ; yO = A * xO + B; B = yO - (2 * aa * x * xO + bb * xO) = 
	// -aa *  x^2 + (2 * xQ - yQ + 1) + yO - 2 * aa *x * xO - bb * xO = 0
	// -aa * x^2 - 2 * aa * xO * x + cc - bb * xO + yO = 0
	// aa * x^2 + 2 aa * xO * x - cc + bb * xO + yO = 0


	float a = aa;
	std::cout << "a : " << a << std::endl;

	float b = -2 * aa * xQ;
	std::cout << "b : " << b << std::endl;
	float c = yQ - bb * xQ - cc;
	//float c = bb - cc - bb * xQ + yQ ? Error;
	std::cout << "c : " << c << std::endl;
	float xT1 = ((-1) * b + std::sqrt(pow(b, 2.0f) - 4 * a * c)) / (2 * a);
	float d = pow(b, 2.0f) - 4 * a * c;
	std::cout << "d : " << d << std::endl;
	std::cout << "xT1: " << xT1 << std::endl;
	float xT2 = ((-1) * b - std::sqrt(pow(b, 2.0f) - 4 * a * c)) / (2 * a);
	std::cout << "xT2: " << xT2 << std::endl;
	float A1 = 2 * aa * xT1 + bb;
	float A2 = 2 * aa * xT2 + bb;
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


}