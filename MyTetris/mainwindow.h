#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class IScene;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    static constexpr QSize mainSize = QSize(1024, 600);

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//public slots:
//    void newGame();
//    void exitGame();
//    void saveGame();
//    void loadGame();
//    void pauseGame();
//    void resumeGame();


private:
    Ui::MainWindow  *ui;
    IScene          *scene;
};
#endif // MAINWINDOW_H
