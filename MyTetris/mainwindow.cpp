#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scenemodel.h"
#include "controller.h"
#include "figureview.h"
#include "figure.h"

#include <QGuiApplication>
#include <QScreen>
#include <QIntValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->sceneView->setWidgetSize();

    auto screen = QGuiApplication::primaryScreen();
    auto availGeom = screen->availableGeometry();
    setGeometry((availGeom.width()-mainSize.width())/2, (availGeom.height()-mainSize.height())/2,
                 mainSize.width(), mainSize.height());

    // TODO Here we can create model from fuctory
    auto scene      = new Scene(ui->sceneView->rows(), ui->sceneView->columns(), this);
    auto controller = new Controller(scene, ui->sceneView, this);

    // Bind view with model & controller
    ui->sceneView->setModel(scene);
    ui->sceneView->setController(controller);

    // Set focus
    ui->sceneView->setFocus();
    ui->NewGame->setFocusPolicy(Qt::FocusPolicy::NoFocus);
//    ui->rightVLay->setAlignment(ui->nextFig, Qt::AlignCenter);

    // Valid input for speed
    auto valid = new QIntValidator(0, 9, ui->speedNum);
    ui->speedNum->setValidator(valid);

    // View for Figures
    auto currFigView = new FigureView(ui->sceneView, scene->currFig(), ui->sceneView->sideLen());
    auto nextFigView = new FigureView(nullptr,   scene->nextFig(), ui->sceneView->sideLen());
    ui->rightVLay->addWidget(nextFigView, 0, Qt::AlignCenter);
    currFigView->setMovable(true);

    // Connections
    connect(ui->speedNum, &QLineEdit::textChanged,  controller,  &Controller::setSpeed);
    connect(scene,        &Scene::upCurrFigure,     currFigView, &FigureView::drawFigure);
    connect(scene,        &Scene::upNextFigure,     nextFigView, &FigureView::drawFigure);
    connect(scene,        &Scene::scoreChanged,     ui->scoreNum, QOverload<int>::of(&QLCDNumber::display));

    connect(ui->Exit,          &QPushButton::clicked, ui->actionExit,    &QAction::trigger);
    connect(ui->NewGame,       &QPushButton::clicked, ui->actionNewGame, &QAction::trigger);
    connect(ui->actionNewGame, &QAction::triggered,   controller, &Controller::doStart);
    connect(ui->actionPause,   &QAction::triggered,   controller, &Controller::togglePause);
    connect(ui->actionExit,    &QAction::triggered,   this,       &QWidget::close);
}

MainWindow::~MainWindow()
{
    delete ui;
}

