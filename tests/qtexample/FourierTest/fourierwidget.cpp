#include "fourierwidget.h"
#include "ui_fourierwidget.h"

FourierWidget::FourierWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FourierWidget)
{
    ui->setupUi(this);
}

FourierWidget::~FourierWidget()
{
    delete ui;
}
