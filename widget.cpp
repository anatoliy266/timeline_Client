#include "widget.h"
#include "ui_widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    gettimeClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    connect(&client, SIGNAL(getValTimeSIg(QString)), this, SLOT(getValWidgetSlot(QString)));
    client.timeget();
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked()));
}

Widget::~Widget()
{
    delete ui;
    delete tmr;
}

/*void Widget::getValWidgetSlot(QString value) {
    ui->label_2->setText(value);
}*/
void Widget::on_pushButton_clicked()
{
    tmr = new QTimer;
    tmr->setInterval(1000);
    connect(tmr, SIGNAL(timeout()), this, SLOT(text_change()));
    tmr->start();
}

void Widget::text_change() {
    ui->label_2->setText(vallue);
}

void Widget::getValWidgetSlot(QString value) {
    std::cout << value.toStdString() << std::endl;
    vallue = value;
}
