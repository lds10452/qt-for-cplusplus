#include "smallwidget.h"
#include<QSpinBox>
#include<QSlider>
#include<QHBoxLayout>

smallWidget::smallWidget(QWidget *parent) : QWidget(parent)
{
    QSpinBox *spin=new QSpinBox(this);
    QSlider *slider=new QSlider(Qt::Horizontal,this);
    QHBoxLayout *hLayout=new QHBoxLayout(this);
    hLayout->addWidget(spin);
    hLayout->addWidget(slider);
    //setLayout(hLayout);
    connect(spin,static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),slider,&QSlider::setValue);
    connect(slider,&QSlider::valueChanged,spin,&QSpinBox::setValue);
}
