#include <cstdlib>
#include <iostream>

#include "application.h"
#include "terminal.h"

int main() {
	const std::optional<TerminalSize> terminalSize =
		getTerminalSize();

	if (!terminalSize) {
		std::cerr << "Unable to determine terminal size.\n";
		return EXIT_FAILURE;
	}

	if (
		terminalSize->width < minimumTerminalWidth ||
		terminalSize->height < minimumTerminalHeight
	) {
		std::cerr
			<< "Graphite requires a terminal of at least "
			<< minimumTerminalWidth << 'x'
			<< minimumTerminalHeight << ".\n"
			<< "Current terminal: "
			<< terminalSize->width << 'x'
			<< terminalSize->height << ".\n"
			<< "Resize the terminal and restart.\n";

		return EXIT_FAILURE;
	}

	Application app;

	initialize(
		app,
		terminalSize->width,
		terminalSize->height
	);

	enterAlternateScreen();
	show(false);

	run(app);
	finalize(app);

	restoreTerminal();

	return EXIT_SUCCESS;
}