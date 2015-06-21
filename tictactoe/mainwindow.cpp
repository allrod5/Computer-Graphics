#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	connect(ui->actionHow_to_Play, SIGNAL(triggered()), this, SLOT(showHelp()));
	connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));
	connect(ui->actionNew_Game, SIGNAL(triggered()), this, SLOT(newGame()));
	connect(ui->actionRestart, SIGNAL(triggered()), this, SLOT(restartGame()));

	getSettings();
	//setupGrid();

	player = false;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::getSettings()
{
	QVBoxLayout *layout = new QVBoxLayout;
	layout->setObjectName("initialLayout");

	QFont font(QApplication::font());
	QLabel *text = new QLabel;
	text->setText("Please choose the desired board height and the sequence length to win. "
				  "Board size is given by the number of rows the board will have as it "
				  "will be a square board.");
	text->setWordWrap(true);
	font.setPointSize(14);
	text->setFont(font);
	layout->addWidget(text);

	QFormLayout *formLayout = new QFormLayout;
	formLayout->setObjectName("formLayout");
	QLineEdit *size = new QLineEdit();
	size->setText("3");
	size->setObjectName("boardSize");
	QLineEdit *seq = new QLineEdit();
	seq->setText("3");
	seq->setObjectName("sequenceLength");
	formLayout->addRow(tr("&Board Height:"), size);
	formLayout->addRow(tr("&Sequence Length:"), seq);
	layout->addLayout(formLayout);

	QPushButton *startButton = new QPushButton();
	connect(startButton, SIGNAL(clicked()), this, SLOT(setupGame()));
	startButton->setText("Start Game");
	font.setPointSize(16);
	startButton->setFont(font);
	layout->addWidget(startButton);

	ui->widget->setLayout(layout);
}

void MainWindow::setupGrid()
{
	QGridLayout *layout = new QGridLayout;
	QHBoxLayout *bottom = new QHBoxLayout;
	QVBoxLayout *grand = new QVBoxLayout;
	layout->setSpacing(0);
	for(int i=0; i<bSize*bSize; i++)
	{
		ticButtons[i] = createButton(SLOT(ticClicked()), i);
		ticButtons[i]->setObjectName(QString::number(i));
		layout->addWidget(ticButtons[i], i/bSize, i%bSize);
	}
	grand->addLayout(layout);

	QFont font(QApplication::font());
	font.setPointSize(16);
	QPushButton *restartButton = new QPushButton();
	restartButton->setText("Restart");
	restartButton->setFont(font);
	connect(restartButton, SIGNAL(clicked()), this, SLOT(restartGame()));

	QPushButton *newGameButton = new QPushButton();
	newGameButton->setText("New Game");
	newGameButton->setFont(font);
	connect(newGameButton, SIGNAL(clicked()), this, SLOT(newGame()));

	bottom->addWidget(restartButton);
	bottom->addWidget(newGameButton);

	grand->addLayout(bottom);

	ui->widget->setLayout(grand);
}

QPushButton *MainWindow::createButton(const QString member, int pos)
{
	QPushButton *button = new QPushButton();
	//int size = ui->widget->size().width()/bSize;
	//button->setGeometry(QRect(QPoint(pos%3*size, pos/3*size), QSize(size, size)));
	button->setSizePolicy(QSizePolicy::Ignored,QSizePolicy::Ignored);
	button->setText("");
	QFont font(QApplication::font());
	font.setPointSize(16+130/bSize);
	button->setFont(font);

	connect(button, SIGNAL(clicked()), this, member.toStdString().c_str()); //connect button signal to SLOT(itemClicked)

	return button;
}

//slot
void MainWindow::setupGame()
{
	bSize = ui->widget->findChild<QLineEdit *>("boardSize")->text().toInt();
	sLength = ui->widget->findChild<QLineEdit *>("sequenceLength")->text().toInt();
	ticButtons = new QPushButton*[bSize*bSize];
	board = new int*[bSize];
	for(int i=0; i<bSize; i++)
		board[i] = new int[bSize];
	for(int i=0; i<bSize; i++)
		for(int j=0; j<bSize; j++)
			board[i][j] = 0;
	winningSequence = new int[sLength];
	qDeleteAll(ui->widget->children());
	delete ui->widget->layout();
	ui->label->setText("O Starts");
	turns = 0;
	ended = false;
	setupGrid();
}

// slot
void MainWindow::ticClicked()
{
	QPushButton *ticButton = qobject_cast<QPushButton*>(sender());

	ticButton->setAutoExclusive(false);
	ticButton->setChecked(false);
	ticButton->setAutoExclusive(true);

	if (ticButton->text().isEmpty() && !ended) {
		ticButton->setText((player) ? "X" : "O");
		int i = ticButton->objectName().toInt()%bSize;
		int j = ticButton->objectName().toInt()/bSize;
		play(i,j);
	}
}

//slot
void MainWindow::newGame()
{
	ui->label->setText("Tic Tac Toe");
	qDeleteAll(ui->widget->children());
	delete ui->widget->layout();
	ended = false;
	getSettings();
}

//slot
void MainWindow::restartGame()
{
	for(int i=0; i<bSize; i++)
		board[i] = new int[bSize];
	for(int i=0; i<bSize; i++)
		for(int j=0; j<bSize; j++)
			board[i][j] = 0;
	winningSequence = new int[sLength];
	qDeleteAll(ui->widget->children());
	delete ui->widget->layout();
	if (player)
		ui->label->setText("X Starts");
	else
		ui->label->setText("O Starts");
	ended = false;
	turns = 0;
	setupGrid();
}

//slot
void MainWindow::showHelp()
{
	QMessageBox msgBox;
	msgBox.setText("Tic Tac Toe is a game where two players try to make "
				   "a sequence of a defined length with their symbol ('O' or 'X') in "
				   "order to win. The sequence can be formed horizontally, vertically "
				   "or diagonally.\n A good choice for the sequence length to win is "
				   "either 5 or the height of the board.");
	msgBox.exec();
}

//slot
void MainWindow::showAbout()
{
	QMessageBox msgBox;
	msgBox.setText("Tic Tac Toe\nDeveloped by Rodrigo Martins de Oliveira\nUFABC - Brazil, 2015");
	msgBox.exec();
}

void MainWindow::play(int i, int j)
{
	board[i][j] = (player) ? 2 : 1;
	player = !player;
	if (player)
		ui->label->setText("Mark X");
	else
		ui->label->setText("Mark O");

	turns++;
	winningSequence[0] = i+bSize*j;

	// Winner?
	// Check line
	int seq = 1;
	int a=i-1;
	while(0<=a)
	{
		if(board[a][j] == board[i][j])
		{
			winningSequence[seq] = a+bSize*j;
			seq++;
		}
		else break;
		a--;
	}
	a=i+1;
	while(a<bSize)
	{
		if(board[a][j] == board[i][j])
		{
			winningSequence[seq] = a+bSize*j;
			seq++;
		}
		else break;
		a++;
	}
	if(seq==sLength)
	{
		board[i][j]==1 ? ui->label->setText("O Won!") : ui->label->setText("X Won!");
		for(int p=0; p<seq; p++)
			ticButtons[winningSequence[p]]->setStyleSheet(	"background-color:#99FF99;"
															"border-radius: 3px;"		);
		ended = true;
	}
	else
	{
		// Check column
		seq = 1;
		int b=j-1;
		while(0<=b)
		{
			if(board[i][b] == board[i][j])
			{
				winningSequence[seq] = i+bSize*b;
				seq++;
			}
			else break;
			b--;
		}
		b=j+1;
		while(b<bSize)
		{
			if(board[i][b] == board[i][j])
			{
				winningSequence[seq] = i+bSize*b;
				seq++;
			}
			else break;
			b++;
		}
		if(seq==sLength)
		{
			board[i][j]==1 ? ui->label->setText("O Won!") : ui->label->setText("X Won!");
			for(int p=0; p<seq; p++)
				ticButtons[winningSequence[p]]->setStyleSheet(	"background-color:#99FF99;"
																"border-radius: 3px;"		);
			ended = true;
		}
		else
		{
			// Check right diagonal
			seq = 1;
			a=i-1;
			b=j+1;
			while(0<=a && b<bSize)
			{
				if(board[a][b] == board[i][j])
				{
					winningSequence[seq] = a+bSize*b;
					seq++;
				}
				else break;
				a--;
				b++;
			}
			a=i+1;
			b=j-1;
			while(a<bSize && b>=0)
			{
				if(board[a][b] == board[i][j])
				{
					winningSequence[seq] = a+bSize*b;
					seq++;
				}
				else break;
				a++;
				b--;
			}
			if(seq==sLength)
			{
				board[i][j]==1 ? ui->label->setText("O Won!") : ui->label->setText("X Won!");
				for(int p=0; p<seq; p++)
					ticButtons[winningSequence[p]]->setStyleSheet(	"background-color:#99FF99;"
																	"border-radius: 3px;"		);
				ended = true;
			}
			else
			{
				// Check left diagonal
				seq = 1;
				a=i+1;
				b=j+1;
				while(a<bSize && b<bSize)
				{
					if(board[a][b] == board[i][j])
					{
						winningSequence[seq] = a+bSize*b;
						seq++;
					}
					else break;
					a++;
					b++;
				}
				a=i-1;
				b=j-1;
				while(a>=0 && b>=0)
				{
					if(board[a][b] == board[i][j])
					{
						winningSequence[seq] = a+bSize*b;
						seq++;
					}
					else break;
					a--;
					b--;
				}
				if(seq==sLength)
				{
					board[i][j]==1 ? ui->label->setText("O Won!") : ui->label->setText("X Won!");
					for(int p=0; p<seq; p++)
						ticButtons[winningSequence[p]]->setStyleSheet(	"background-color:#99FF99;"
																		"border-radius: 3px;"		);
					ended = true;
				}
				else  // Draw?
				{
					if(turns==bSize*bSize)
					{
						ui->label->setText("Draw!");
						ended = true;
					}
				}
			}
		}
	}
}
