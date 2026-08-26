#pragma once

#include "box.h"
#include "action.h"
#include "graph.h"


const int sizeMenu = 16, sizeHiddenMenu = 18;

struct ResolvedAction {
	Action action = Action::NoAction;
	HiddenAction hiddenAction = HiddenAction::NoAction;
};

struct MenuItem {
	std::string name;
	Action action;
	char key;
};

struct HiddenMenuItem {
	HiddenAction hiddenAction;
	char key;
};

struct Menu {
	Box box;
	std::string title;
	MenuItem items[sizeMenu]; 
	size_t size;
	bool isHiddenAction = false;
	HiddenMenuItem hiddenItems[sizeHiddenMenu];
	size_t sizeHidden;
	Colors textColor = { Color::_wht, Color::blk };
};


void initializeMenu(Menu& menu, const Box& box, const std::string& title, bool isHidden = false);

void addMenu(Menu& menu, const std::string& title, Action action, char key);

void populateMenu(Menu& menu, const std::string name[], Action action[], char key[], int size,
	HiddenAction hiddenActions[] = nullptr, char hiddenKeys[] = nullptr, int hiddenSize = 0);

ResolvedAction resolveAction(const Menu& menu);

void draw(const Menu& menu);
