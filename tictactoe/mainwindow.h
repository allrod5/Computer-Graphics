#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QGridLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QFrame>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();
	void getSettings();
	void setupGrid();

public slots:
	void setupGame();
	void ticClicked();
	void newGame();
	void restartGame();
	void showHelp();
	void showAbout();

private:
	Ui::MainWindow *ui;
	QPushButton **ticButtons;
	QPushButton *createButton(const QString, int);
	int bSize;
	int sLength;
	int **board;
	int *winningSequence;
	bool player;
	void play(int, int);
	int turns;
	bool ended;
};

#endif // MAINWINDOW_H
