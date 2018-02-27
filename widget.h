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

class Widget : public QWidget//A
{
    Q_OBJECT

public:
    friend class gettimeClient;
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();


private:
    Ui::Widget *ui;
    QString tt;
};

class gettimeClient { //B
public:
    gettimeClient(std::shared_ptr<Channel> channel) : stub_(gettime::NewStub(channel)) {}
    friend class Widget;
    void timeget() {
        timeline::ask request;

        ClientContext context;
        request.set_needtime(1000);
        std::unique_ptr<ClientReader<answer>> reader(stub_->obmen(&context, request));
        timeline::answer* reply;
        while (reader->Read(reply)) {
            val = reply->timeis();
            stringval(val);

        }
    }
    std::string val;
    QString stringval(const std::string val) {
        widget->tt = QString::fromStdString(val);
        return widget->tt;
    }

private:
    std::unique_ptr<gettime::Stub> stub_;
    QString value;
    Widget* widget;



};

#endif // WIDGET_H
