#include "actions.h"

const std::size_t sizeActionHome = 3;
const std::size_t sizeActionVisualization = 12;
const std::size_t sizeActionCurve = 14;
const std::size_t sizeHiddenActionCurve = 18;

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

const char homeKey[sizeActionHome] {
	'v',
	'c',
	27
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

const char visualizationKey[sizeActionVisualization] {
	'r',
	75,
	72,
	77,
	80,
	'e',
	'q',
	'w',
	'a',
	's',
	'd',
	27
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

const char curveKey[sizeActionCurve] {
	72,
	80,
	75,
	77,
	'z',
	'x',
	'#',
	's',
	'c',
	't',
	'p',
	'e',
	'l',
	27
};

const HiddenAction curveHiddenAction[sizeHiddenActionCurve] {
	HiddenAction::CurveCoefEditIncrease1,
	HiddenAction::CurveCoefEditIncrease2,
	HiddenAction::CurveCoefEditIncrease3,
	HiddenAction::CurveCoefEditIncrease4,
	HiddenAction::CurveCoefEditIncrease5,
	HiddenAction::CurveCoefEditIncrease6,
	HiddenAction::CurveCoefEditIncrease7,
	HiddenAction::CurveCoefEditIncrease8,
	HiddenAction::CurveCoefEditIncrease9,
	HiddenAction::CurveCoefEditDecrease1,
	HiddenAction::CurveCoefEditDecrease2,
	HiddenAction::CurveCoefEditDecrease3,
	HiddenAction::CurveCoefEditDecrease4,
	HiddenAction::CurveCoefEditDecrease5,
	HiddenAction::CurveCoefEditDecrease6,
	HiddenAction::CurveCoefEditDecrease7,
	HiddenAction::CurveCoefEditDecrease8,
	HiddenAction::CurveCoefEditDecrease9
};

const char hiddenCurveKey[sizeHiddenActionCurve] {
	49,
	50,
	51,
	52,
	53,
	54,
	55,
	56,
	57,
	59,
	60,
	61,
	62,
	63,
	64,
	65,
	66,
	67
};
