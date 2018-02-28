#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QTime>
#include <QTimer>
#include <QString>
#include <QLabel>
#include <algorithm>
#include <chrono>
#include <cmath>
#include <iostream>
#include <memory>
#include <string>
#include <grpc/grpc.h>
#include <grpc++/grpc++.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include <timeline.grpc.pb.h>

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;
using timeline::answer;
using timeline::ask;
using timeline::gettime;

namespace Ui {
class Widget;
class gettimeClient;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QString _tt;
signals:
    void getValue();
private slots:
    void on_pushButton_clicked(QString value);
private:
    Ui::Widget *ui;
};

class gettimeClient : public Widget { //B
    Q_OBJECT
public:
    gettimeClient(std::shared_ptr<Channel> channel) : stub_(gettime::NewStub(channel)) {}
    friend class Widget;
    void timeget() {
        timeline::ask request;
        answer Answer;
        ClientContext context;
        request.set_needtime(1000);
        std::unique_ptr<ClientReader<answer>> reader(stub_->obmen(&context, request));

        while (reader->Read(&Answer)) {
            val = Answer.timeis();
            value = QString::fromStdString(val);
        };
        connect(this->parent(), SIGNAL(getValue()), this, SLOT(signalGetValue()));
        connect(this, SIGNAL(getValue(QString)), this->parent(), SLOT(on_pushButton_clicked(QString)));
    }
signals:
    void getValue(QString value);
private slots:
    void signalGetValue() {
        emit getValue(this->value);
    }
private:
    std::unique_ptr<gettime::Stub> stub_;
    QString value;
    std::string val;
    Widget* widget;
};

#endif // WIDGET_H
