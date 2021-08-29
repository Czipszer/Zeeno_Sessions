#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "circle.hpp"
#include "main.hpp"
#include "rectangle.hpp"
#include "shape.hpp"
#include "triangle.hpp"

using namespace std;

int main() {
	try {
		vector<shared_ptr<Shape>> shapes{make_shared<Rectangle>(3, 5), make_shared<Triangle>(5, 3, 4), make_shared<Circle>(8)};

		// zpusob volani classy bez konstruktoru
		auto a = make_shared<Triangle>();
		a->setSize(2, 1, 5);
		shapes.push_back(a);

		for (auto& i : shapes) {
			cout << "Obvod je: " << i->perimeter() << endl;
			cout << "Obsah je: " << i->area() << endl << endl;
		}
		return 0;
	} catch (const exception& e) {
		cerr << e.what();
		return 1;
	}
}
