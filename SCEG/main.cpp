#include "SCEG.h"
#include <cstdlib>

int main() {
	SCEG::Engine *eng = new SCEG::Engine();
	eng->run();
	delete eng;
#ifdef DEBUG && _WIN32
	system("pause");
#endif

	return 0;
}