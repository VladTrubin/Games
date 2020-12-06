#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scenemodel.h"
#include "controller.h"

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
    _scene = new Scene(ui->sceneView->rows(), ui->sceneView->columns());
    _controller = new Controller(_scene, ui->sceneView);

    // Bind view with model & controller
    ui->sceneView->setModel(_scene);
    ui->sceneView->setController(_controller);

    // Set focus
    ui->sceneView->setFocus();

    ui->rightVLay->setAlignment(ui->speedNum, Qt::AlignCenter);

    // Valid input for speed
    auto valid = new QIntValidator(0, 9, ui->speedNum);
    ui->speedNum->setValidator(valid);

    // Connections
    connect(ui->speedNum, &QLineEdit::textChanged, _controller, &Controller::setSpeed);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete _scene;
    delete _controller;
}

