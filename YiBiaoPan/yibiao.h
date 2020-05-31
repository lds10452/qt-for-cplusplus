#ifndef YIBIAO_H
#define YIBIAO_H

#include <QWidget>
#include <QMainWindow>

#include <QTimer>
class yiBiao : public QWidget
{
    Q_OBJECT

public:
    yiBiao(QWidget *parent = 0);
    ~yiBiao();
protected:
    void thresholdManager();
    void paintEvent(QPaintEvent *);

    void drawCrown(QPainter *painter);
    void drawBackground(QPainter *painter);
    void drawScale(QPainter *painter);
    void drawScaleNum(QPainter *painter);
    void drawTitle(QPainter *painter);
    void drawIndicator(QPainter *painter);
    void drawNumericValue(QPainter *painter);

private:
    bool m_numericIndicatorEnabled;
    QColor m_crownColor;
    QColor m_foreground;
    QColor m_background;

    QString m_units;
    QString m_title;

    int m_scaleMajor;
    int m_scaleMinor;

    int m_maxValue, m_minValue;

    int m_startAngle,m_endAngle;

    double m_value;
    int m_precision;
    QTimer *m_updateTimer;
public Q_SLOTS:
      void UpdateAngle();

};

#endif // YIBIAO_H
