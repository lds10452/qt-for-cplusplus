#include "mainwindow.h"
#include<QMenuBar>
#include<QMenu>
#include<QAction>
#include<QDebug>
#include<QToolBar>
#include<QPushButton>
#include<QStatusBar>
#include<QLabel>
#include<QTextEdit>
#include<QDockWidget>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QMenuBar *mBar=menuBar();
    QMenu *pFile=mBar->addMenu("文件");
    QAction *pNew= pFile->addAction("新建");
    connect(pNew,&QAction::triggered,
            [=]()
            {
            qDebug()<<"新建被按下";
            }
            );
    pFile->addSeparator();
    QAction *pOpen = pFile->addAction("打开");

    QToolBar *toolBar=addToolBar("toolbar");
    toolBar->addAction(pNew);

    QPushButton *b=new QPushButton(this);
    toolBar->addWidget(b);
    b->setText("^_^");
    connect(b,&QPushButton::clicked,
            [=]()
            {
            b->setText("123");
            }
            );

    QStatusBar *sBar=statusBar();//
    QLabel *label=new QLabel(this);
    label->setText("normal text file");
    sBar->addWidget(label);
    sBar->addWidget(new QLabel("2",this));
    sBar->addPermanentWidget(new QLabel("3",this));
    sBar->addPermanentWidget(new QLabel("4",this));

    QTextEdit *textEdit=new QTextEdit(this);
    setCentralWidget(textEdit);

    QDockWidget *dock=new QDockWidget(this);
    addDockWidget(Qt::RightDockWidgetArea,dock);//

    QTextEdit *textEdit1=new QTextEdit(this);
    dock->setWidget(textEdit1);


}

MainWindow::~MainWindow()
{

}
