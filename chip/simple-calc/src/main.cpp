#include <functional>
#include <iostream> //knihovna pro vztupy a výstupy
#include <map>
#include <string>

#include "main.hpp"

using namespace std; //umoznuje vynechat std

struct Operation {
	string                           help;
	function<double(double, double)> mathOperation;
};

map<char, Operation> mathOperations{
    {'+', Operation{"scitani", [](double a, double b) { return a + b; }}},
    {'-', Operation{"odcitani", [](double a, double b) { return a - b; }}},
    {'*', Operation{"nasobeni", [](double a, double b) { return a * b; }}},
    {
        '/',
        Operation{
            "deleni",
            [](double a, double b) {
	            if (b == 0) {
		            throw runtime_error("Deli nulou.");
	            }
	            return a / b;
            }},
    }};

double getNumber(int loop) {
	double x{};
	cin >> x;

	int i{};
	for (i; i < loop; i++) {
		if (!cin.fail()) {
			break;
		}
		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Zadejte prosim cislo." << endl;
			cin >> x;
		}
	}

	if (i == loop) {
		cout << "Tak nic." << endl;
		throw runtime_error("Nezadal cislo.");
	}
	return x;
}

int main() {
	try {
		cout << "Zadejte prvni cislo: " << endl;

		constexpr int loop{2};
		double        a = getNumber(loop);

		cout << "Zadej druhe cislo: " << endl;

		double b = getNumber(loop);

		cout << "Jakou operaci s cisli " << a << " a " << b << " chces provest:" << endl;

		for (auto [symbol, op] : mathOperations) {
			cout << symbol << " -> " << op.help << endl;
		}

		char operat{}; //deklarace
		cin >> operat;

		int i{};
		for (i; i < loop; i++) {
			if (mathOperations.contains(operat)) {
				break;
			} else {
				cout << "Takovou operaci neumim." << endl;
				cout << "Zkus to znovu. Jakou operaci chces provest:" << endl;
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				cin >> operat;
			}
		}
		if (i == loop) {
			cout << "Tak nic." << endl;
			throw runtime_error("Nezadal spravny operator.");
		}

		double x{};
		x = mathOperations[operat].mathOperation(a, b);
		cout << "Vysledek je:" << endl;
		cout << x << endl;

		return 0;
	} catch (const exception& e) {
		cerr << e.what();
		return 1;
	}
}
