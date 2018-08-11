#include "SCEG.h"
#include <cstdlib>

int main() {
	SCEG::Engine *eng = new SCEG::Engine();
	eng->run();
	delete eng;

	system("pause");


	return 0;
}