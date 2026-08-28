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

	CurveParameterSelect1,
	CurveParameterSelect2,
	CurveParameterSelect3,
	CurveParameterSelect4,
	CurveParameterSelect5,
	CurveParameterSelect6,
	CurveParameterSelect7,
	CurveParameterSelect8,
	CurveParameterSelect9,

	CurveParameterIncrease,
	CurveParameterDecrease
};
