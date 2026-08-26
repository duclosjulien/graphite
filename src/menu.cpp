#include <iostream>

#include "menu.h"
#include "terminal.h"

namespace {
int getKey() {
		int key = getch();

		if (key != 27) {
			return key;
		}

		int second = getch();

		if (second != '[') {
			return 27; // regular Escape
		}

		int third = getch();

		switch (third) {
			case 'A': return 72; // up
			case 'B': return 80; // down
			case 'C': return 77; // right
			case 'D': return 75; // left
			default:  return 27;
		}
}

void addMenu(Menu& menu, const std::string& title, Action action, char key) {
	if (menu.size < sizeMenu) {
		menu.items[menu.size].name = title;
		menu.items[menu.size].action = action;
		menu.items[menu.size].key = key;
		++menu.size;
	}
}

void addHiddenMenu(Menu& menu, HiddenAction hiddenAction, char hiddenKey) {
	if (menu.sizeHidden < sizeHiddenMenu) {
		menu.hiddenItems[menu.sizeHidden].hiddenAction = hiddenAction;
		menu.hiddenItems[menu.sizeHidden].key = hiddenKey;
		++menu.sizeHidden;
	}
}
}

void initializeMenu(Menu& menu, const Box& box, const std::string& title, bool isHidden) {
	menu.box = box;
	menu.title = title;
	menu.size = 0;
	menu.sizeHidden = 0;
	menu.isHiddenAction = isHidden;
}

void populateMenu(
	Menu& menu,
	const std::string name[],
	const Action action[],
	const char key[],
	std::size_t size,
	const HiddenAction hiddenActions[],
	const char hiddenKeys[],
	std::size_t hiddenSize
	) {

	for (std::size_t i = 0; i < size; ++i) {
		addMenu(menu, name[i], action[i], key[i]);
	}

	if (menu.isHiddenAction && hiddenActions && hiddenKeys) {
		for (std::size_t i = 0; i < hiddenSize; ++i) {
			addHiddenMenu(menu, hiddenActions[i], hiddenKeys[i]);
		}
	}
}

ResolvedAction resolveAction(const Menu& menu) {
	ResolvedAction result;
	int key = getKey();

	if (key == 0 || key == 224) {
		const int secondKey = getch();
		for (std::size_t i = 0; i < menu.size; ++i) {
			if (secondKey == menu.items[i].key) {
				result.action = menu.items[i].action;
				return result;
			}
		}
		for (std::size_t i = 0; i < menu.sizeHidden; ++i) {
			if (secondKey == menu.hiddenItems[i].key) {
				result.hiddenAction = menu.hiddenItems[i].hiddenAction;
				return result;
			}
		}
	}
	else  {
		for (std::size_t i = 0; i < menu.size; ++i)  {
			if (key == menu.items[i].key)  {
				result.action = menu.items[i].action;
				return result;
			}
		}
		for (std::size_t i = 0; i < menu.sizeHidden; ++i)  {
			if (key == menu.hiddenItems[i].key)  {
				result.hiddenAction = menu.hiddenItems[i].hiddenAction;
				return result;
			}
		}
	}
	return result;
}

void draw(const Menu& menu) {
	setColors(menu.textColor);

	gotoxy(menu.box.geometry.topLeft.x + 1, menu.box.geometry.topLeft.y + 1); std::cout << menu.title;
	for (std::size_t i = 0; i < menu.size; ++i) {
		const int row = menu.box.geometry.topLeft.y + 2 + static_cast<int>(i);

		gotoxy(menu.box.geometry.topLeft.x + 1, row);
		std::cout << menu.items[i].name;
	}
}
