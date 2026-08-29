#include "actions.h"
#include "terminal.h"

const std::size_t sizeActionHome = 3;
const std::size_t sizeActionVisualization = 12;
const std::size_t sizeActionCurve = 14;
const std::size_t sizeHiddenActionCurve = 11;

const std::string homeName[sizeActionHome] {
	" V : Interactive view",
	" C : Curve edition",
	" * : Quit"
};

const Action homeAction[sizeActionHome] {
	Action::ModeInteractiveView,
	Action::ModeCurveEdition,
	Action::Quit
};

const int homeKey[sizeActionHome] {
	'v',
	'c',
	Key::Escape
};

const std::string visualizationName[sizeActionVisualization] {
	" R : Reset view",
	" < : Move left",
	" ^ : Move up",
	" > : Move right",
	" v : Move down",
	" E : Zoom-in",
	" Q : Zoom-out",
	" W : Y-axis zoom-in",
	" A : X-axis zoom-out",
	" S : Y-axis zoom-out",
	" D : X-axis zoom-in",
	" * : Return"
};

const Action visualizationAction[sizeActionVisualization] {
	Action::VisualizationResetView,		
	Action::VisualizationPanLeft,			
	Action::VisualizationPanUp,				
	Action::VisualizationPanRight,		
	Action::VisualizationPanDown,
	Action::VisualizationZoomIn,
	Action::VisualizationZoomOut,
	Action::VisualizationZoomInY,
	Action::VisualizationZoomOutX,
	Action::VisualizationZoomOutY,
	Action::VisualizationZoomInX,
	Action::ModeMain
};

const int visualizationKey[sizeActionVisualization] {
	'r',
	Key::ArrowLeft,
	Key::ArrowUp,
	Key::ArrowRight,
	Key::ArrowDown,
	'e',
	'q',
	'w',
	'a',
	's',
	'd',
	Key::Escape
};

const std::string curveName[sizeActionCurve] {
	" ^ : Select previous",
	" v : Select next",
	" < : Select first",
	" > : Select last",
	" Z : Show all curves",
	" X : Show only current",
	" # : Remove current",
	" S : Add sinus",
	" C : Add cosinus",
	" T : Add tangent",
	" P : Add polynomial",
	" E : Add exponential",
	" L : Add logarithmic",
	" * : Return"
};

const Action curveAction[sizeActionCurve] {
	Action::CurveSelectUp,
	Action::CurveSelectDown,
	Action::CurveSelectFirst,
	Action::CurveSelectLast,
	Action::CurveShowAll,
	Action::CurveShowCurrentOnly,
	Action::CurveRemoveCurrent,				
	Action::CurveAddSinus,					
	Action::CurveAddCosinus,				
	Action::CurveAddTangent,				
	Action::CurveAddPolynomial,				
	Action::CurveAddExponential,			
	Action::CurveAddLogarithmic,
	Action::ModeMain,
};

const int curveKey[sizeActionCurve] {
	Key::ArrowUp,
	Key::ArrowDown,
	Key::ArrowLeft,
	Key::ArrowRight,
	'z',
	'x',
	'#',
	's',
	'c',
	't',
	'p',
	'e',
	'l',
	Key::Escape
};

const HiddenAction curveHiddenAction[sizeHiddenActionCurve] {
	HiddenAction::CurveParameterSelect1,
	HiddenAction::CurveParameterSelect2,
	HiddenAction::CurveParameterSelect3,
	HiddenAction::CurveParameterSelect4,
	HiddenAction::CurveParameterSelect5,
	HiddenAction::CurveParameterSelect6,
	HiddenAction::CurveParameterSelect7,
	HiddenAction::CurveParameterSelect8,
	HiddenAction::CurveParameterSelect9,
	HiddenAction::CurveParameterIncrease,
	HiddenAction::CurveParameterDecrease
};

const int hiddenCurveKey[sizeHiddenActionCurve] {
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'+',
	'-'
};
