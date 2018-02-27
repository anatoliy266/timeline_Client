#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    gettimeClient client(grpc::CreateChannel("localhost:50051",
                                             grpc::InsecureChannelCredentials()));
    client.timeget();
    ui->label_2->setText(tt);
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

}
