#pragma once

enum class Action {					
	NoAction,

	Quit,							// [ 1]
	
	ModeMain,						// [ 2]
	ModeInteractiveView,			// [ 2]
	ModeCurveEdition,

	VisualizationZoomInX,			// [ 2]
	VisualizationZoomOutX,			// [ 2]
	VisualizationZoomInY,			// [ 2]
	VisualizationZoomOutY,			// [ 2]
	VisualizationZoomIn,			// [ 2]
	VisualizationZoomOut,			// [ 2]
	VisualizationPanLeft,			// [ 2]
	VisualizationPanUp,				// [ 2]
	VisualizationPanRight,			// [ 2]
	VisualizationPanDown,			// [ 2]
	VisualizationResetView,			// [ 2]

	CurveSelectUp,					// [ 5]
	CurveSelectDown,				// [ 5]
	CurveSelectFirst,				// [ 5]
	CurveSelectLast,				// [ 5]
	CurveShowAll,					// [ 5]
	CurveShowCurrentOnly,			// [ 5]

	CurveRemoveCurrent,				// [ 6]
	CurveAddSinus,					// [ 6]
	CurveAddCosinus,				// [ 6]
	CurveAddTangent,				// [ 6]
	CurveAddPolynomial,				// [ 6]
	CurveAddExponential,			// [ 6]
	CurveAddLogarithmic,			// [ 6]
};

enum class HiddenAction {
	NoAction,
	CurveCoefEditIncrease1,			// [ 9]
	CurveCoefEditIncrease2,			// [ 9]
	CurveCoefEditIncrease3,			// [ 9]
	CurveCoefEditIncrease4,			// [ 9]
	CurveCoefEditIncrease5,			// [ 9]
	CurveCoefEditIncrease6,			// [ 9]
	CurveCoefEditIncrease7,			// [ 9]
	CurveCoefEditIncrease8,			// [ 9]
	CurveCoefEditIncrease9,			// [ 9]
	CurveCoefEditDecrease1,			// [ 9]
	CurveCoefEditDecrease2,			// [ 9]
	CurveCoefEditDecrease3,			// [ 9]
	CurveCoefEditDecrease4,			// [ 9]
	CurveCoefEditDecrease5,			// [ 9]
	CurveCoefEditDecrease6,			// [ 9]
	CurveCoefEditDecrease7,			// [ 9]
	CurveCoefEditDecrease8,			// [ 9]
	CurveCoefEditDecrease9,			// [ 9]
};