#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class IScene;
class Controller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    static constexpr QSize mainSize = QSize(1024, 600);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow  *ui;
    IScene          *_scene;
    Controller      *_controller;
};
#endif // MAINWINDOW_H
