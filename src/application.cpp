#include <fstream>
#include <iostream>

#include "actions.h"
#include "application.h"
#include "terminal.h"
#include "information.h"
#include "curvePersistence.h"

namespace {
    void doAction(Application& application);
    void handleHiddenAction(Application& application, HiddenAction hiddenAction);
    void draw(const Application& application);
    void saveCurveList(const Application& application);
    void drawCurves(const CurveCollection& curves, const Graph& graph);
    void loadSavedCurves(Application& application);
}

void initialize(Application& application, int width, int height) {
    application.applicationIsRunning = true;
    application.width = width;
    application.height = height;
    application.layoutOffset = 1;
    application.currentMenu = Mode::HomeMenu;
    application.showAllCurves = true;
   
    const int spacing = application.layoutOffset;
    const int visualizationWidth = 22 + spacing * 2;     
    const int informationHeight = 5 + spacing * 2;
    const int graphLenght = application.width - spacing - visualizationWidth;
    const int graphHeight = application.height - informationHeight - spacing;

    IntRectangle graphRect = { { spacing, spacing }, { graphLenght - 3 * spacing, graphHeight - 3 * spacing } };
    IntRectangle menuRect = { { graphLenght, spacing }, { application.width - 3 * spacing, graphHeight - 3 * spacing } };
    IntRectangle infoRect = { { spacing , graphHeight}, {application.width - 3 * spacing, application.height - 3 * spacing}};

    initialize(application.box[0], graphRect, "Graphic");
    initialize(application.box[1], menuRect, "Action Menu");
    initialize(application.box[2], infoRect, "Function Grapher");

    initialize(application.graph, application.box[0]);

    initializeMenu(application.menu[0], application.box[1], " Home");
    initializeMenu(application.menu[1], application.box[1], " Interactive View");
    initializeMenu(application.menu[2], application.box[1], " Curve", true);

    populateMenu(application.menu[0], homeName, homeAction, homeKey, sizeActionHome);
    populateMenu(application.menu[1], visualizationName, visualizationAction, visualizationKey, sizeActionVisualization);
    populateMenu(application.menu[2], curveName, curveAction, curveKey, sizeActionCurve, curveHiddenAction, hiddenCurveKey, sizeHiddenActionCurve);
}


void run(Application& application) {
    loadSavedCurves(application);

    show(false);
    setcp(437);

    draw();
    draw(application.box, boxSize);

    doAction(application);
}

void finalize(Application& application) {
    saveCurveList(application);
}

namespace {
    void doAction(Application& application) {
        draw(application.box[1]);
        draw(application.menu[static_cast<std::size_t>(application.currentMenu)]);
        draw(application);
        drawInformationBox(application);

        while (application.applicationIsRunning) {
            const ResolvedAction resolved = resolveAction(
                application.menu[static_cast<std::size_t>(application.currentMenu)]);

            if (resolved.hiddenAction != HiddenAction::NoAction) {
                handleHiddenAction(application, resolved.hiddenAction);
            }

            switch (resolved.action) {
            case Action::Quit:
                application.applicationIsRunning = false;
                break;

            case Action::ModeMain:
                application.currentMenu = Mode::HomeMenu;
                draw(application.box[1]);
                draw(application.menu[static_cast<std::size_t>(application.currentMenu)]);
                break;

            case Action::ModeInteractiveView:
                application.currentMenu = Mode::InteractiveView;
                draw(application.box[1]);
                draw(application.menu[static_cast<std::size_t>(application.currentMenu)]);
                break;

            case Action::ModeCurveEdition:
                application.currentMenu = Mode::CurveMenu;
                draw(application.box[1]);
                draw(application.menu[static_cast<std::size_t>(application.currentMenu)]);
                break;

            case Action::VisualizationZoomInX:
                zoomInX(application.graph);
                break;

            case Action::VisualizationZoomOutX:
                zoomOutX(application.graph);
                break;

            case Action::VisualizationZoomInY:
                zoomInY(application.graph);
                break;

            case Action::VisualizationZoomOutY:
                zoomOutY(application.graph);
                break;

            case Action::VisualizationZoomIn:
                zoomIn(application.graph);
                break;

            case Action::VisualizationZoomOut:
                zoomOut(application.graph);
                break;

            case Action::VisualizationPanLeft:
                panLeft(application.graph);
                break;

            case Action::VisualizationPanRight:
                panRight(application.graph);
                break;

            case Action::VisualizationPanUp:
                panUp(application.graph);
                break;

            case Action::VisualizationPanDown:
                panDown(application.graph);
                break;

            case Action::VisualizationResetView:
                reset(application.graph);
                break;

            case Action::CurveSelectUp:
                application.curves.selectPrevious();
                break;

            case Action::CurveSelectDown:
                application.curves.selectNext();
                break;

            case Action::CurveSelectFirst:
                application.curves.selectFirst();
                break;

            case Action::CurveSelectLast:
                application.curves.selectLast();
                break;

            case Action::CurveRemoveCurrent:
                application.curves.removeCurrent();
                break;

            case Action::CurveShowAll:
                application.showAllCurves = true;
                break;

            case Action::CurveShowCurrentOnly:
                application.showAllCurves = false;
                break;

            case Action::CurveAddSinus:
                application.curves.insertAfterCurrent(createSinus());
                break;

            case Action::CurveAddCosinus:
                application.curves.insertAfterCurrent(createCosinus());
                break;

            case Action::CurveAddTangent:
                application.curves.insertAfterCurrent(createTangent());
                break;

            case Action::CurveAddPolynomial:
                application.curves.insertAfterCurrent(createPolynomial());
                break;
            
            case Action::CurveAddExponential:
                application.curves.insertAfterCurrent(createExponential());
                break;
       
            case Action::CurveAddLogarithmic:
                application.curves.insertAfterCurrent(createLogarithmic());
                break;
            default:
                break;
            }

            draw(application);
            clearBoxContent(application.box[2]);
            drawInformationBox(application);
        }
    }

    void handleHiddenAction(Application& application, HiddenAction hiddenAction) {
        Curve* currentCurve = application.curves.current();

        if (!currentCurve) {
            return;
        }

        int index = -1;
        double increment = 0.1;

        switch (hiddenAction) {
        case HiddenAction::CurveCoefEditIncrease1: index = 0; increment *= -1; break;
        case HiddenAction::CurveCoefEditIncrease2: index = 1; increment *= -1; break;
        case HiddenAction::CurveCoefEditIncrease3: index = 2; increment *= -1; break;
        case HiddenAction::CurveCoefEditIncrease4: index = 3; increment *= -1; break;
        case HiddenAction::CurveCoefEditIncrease5: index = 4; increment *= -1; break;
        case HiddenAction::CurveCoefEditIncrease6: index = 5; increment *= -1; break;
        case HiddenAction::CurveCoefEditIncrease7: index = 6; increment *= -1; break;
        case HiddenAction::CurveCoefEditIncrease8: index = 7; increment *= -1; break;
        case HiddenAction::CurveCoefEditIncrease9: index = 8; increment *= -1; break;

        case HiddenAction::CurveCoefEditDecrease1: index = 0; increment *= 1; break;
        case HiddenAction::CurveCoefEditDecrease2: index = 1; increment *= 1; break;
        case HiddenAction::CurveCoefEditDecrease3: index = 2; increment *= 1; break;
        case HiddenAction::CurveCoefEditDecrease4: index = 3; increment *= 1; break;
        case HiddenAction::CurveCoefEditDecrease5: index = 4; increment *= 1; break;
        case HiddenAction::CurveCoefEditDecrease6: index = 5; increment *= 1; break;
        case HiddenAction::CurveCoefEditDecrease7: index = 6; increment *= 1; break;
        case HiddenAction::CurveCoefEditDecrease8: index = 7; increment *= 1; break;
        case HiddenAction::CurveCoefEditDecrease9: index = 8; increment *= 1; break;
        default:
            break;
        }
        
        if (index < 0) {
            return;
        }

        const auto parameterIndex = static_cast<std::size_t>(index);

        if (parameterIndex >= currentCurve->parameterValues.size()) {
            return;
        }

        modifyParameter(*currentCurve, increment, parameterIndex);
    }
}

namespace {
    void draw(const Application& application) {
        draw(application.graph.box);
        drawAxis(application.graph);

        if (application.showAllCurves) {
            drawCurves(application.curves, application.graph);
        }
        else if (const Curve* currentCurve = application.curves.current()) {
            draw(*currentCurve, application.graph);
        }
    }
}

namespace {
    void drawCurves(const CurveCollection& curves, const Graph& graph) {
        for (const Curve& curve : curves) {
            draw(curve, graph);
        }
    }
}

namespace {
    void saveCurveList(const Application& application) {
        std::fstream f;

        std::string fname = "curves";

        f.open(fname, std::ios::out);
    
        if (f.is_open()) {
            f << "\n n_curves = " << application.curves.size() << "\n";

            for (const Curve& curve : application.curves) {
                f << "\n [curve]\n";
                f << " type = " << toStringCurveTypeShort(curve.curveType) << "\n";
                f << " coef = { ";

                for (std::size_t j = 0; j < curve.parameterValues.size(); ++j) {
                    if (j > 0) {
                        f << ", ";
                    }

                    f << curve.parameterValues[j];
                }

                f << " }\n";
                f << " char = " << curve.curveChar << "\n";
                f << " color = " << static_cast<int>(curve.color) << "\n";
            }

            f.close();
        }
    }
}

namespace {
    void loadSavedCurves(Application& application) {
        std::ifstream file{"curves"};

        if (!file) {
            return;
        }

        CurveLoadResult result = loadCurves(file);

        if (!result.succeeded()) {
            std::cerr << "Could not load saved curves: "
                      << result.error << '\n';
            return;
        }

        application.curves.clear();

        for (const Curve& curve : result.curves) {
            application.curves.insertAfterCurrent(curve);
        }
    }
}
