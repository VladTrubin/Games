#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "scenemodel.h"

#include <QGuiApplication>
#include <QScreen>

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
    scene = new Scene(ui->sceneView->rows(), ui->sceneView->columns());

    // Bind view with model
    ui->sceneView->setModel(scene);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete scene;
}

