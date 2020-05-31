#include <QApplication>
#include <QWidget>
#include <QPushButton>
int main(int argc, char **argv)
{
    QApplication app(argc,argv);

    QWidget w;
    w.setWindowTitle("主要看气质");


    QPushButton b;
    b.setText("^-^");
    b.setParent(&w);
    b.move(100,100);

    QPushButton b1(&w);
    b1.setText("abc");

    w.show();
    app.exec();
    return 0;
}
