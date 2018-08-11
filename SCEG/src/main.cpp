#include "Pong.h"
#include <cstdlib>

int main() {
	SCEG::Engine *eng = new Pong();
	eng->run();
	delete eng;

	system("pause");

	return 0;
}