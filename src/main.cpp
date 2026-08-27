#include "application.h"
#include "terminal.h"

int main() {
	Application app;

	initialize(app);
	run(app);
	finalize(app);

	restoreTerminal();
}
	
