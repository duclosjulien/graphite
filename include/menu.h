#pragma once

#include <cstddef>
#include <string>

#include "action.h"
#include "box.h"

constexpr std::size_t sizeMenu = 16;
constexpr std::size_t sizeHiddenMenu = 18;

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
	std::size_t size;
	bool isHiddenAction = false;
	HiddenMenuItem hiddenItems[sizeHiddenMenu];
	std::size_t sizeHidden;
	Colors textColor = { Color::_wht, Color::blk };
};


void initializeMenu(Menu& menu, const Box& box, const std::string& title, bool isHidden = false);

void populateMenu(Menu& menu, const std::string name[], const Action action[], const char key[], std::size_t size,
	const HiddenAction hiddenActions[] = nullptr, const char hiddenKeys[] = nullptr,
	std::size_t hiddenSize = 0);

ResolvedAction resolveAction(const Menu& menu);

void draw(const Menu& menu);
