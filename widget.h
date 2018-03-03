#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QtCore>
#include <QtGui>
#include <QTime>
#include <QTimer>
#include <QString>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <thread>
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
class Transit;
}

class Widget : public QWidget {
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void getValWidgetSlot(QString value);
private slots:
    void on_pushButton_clicked();
    void text_change();

private:
    Ui::Widget *ui;
    QString vallue;
    QTimer *tmr;
};

class gettimeClient: public QObject { //B
    Q_OBJECT
public:
    gettimeClient(std::shared_ptr<Channel> channel) : stub_(gettime::NewStub(channel)) {}
    void timeget() {
        timeline::ask request;
        answer Answer;
        ClientContext context;
        request.set_needtime(1000);
        std::unique_ptr<ClientReader<answer>> reader(stub_->obmen(&context, request));
        while (reader->Read(&Answer)) {
            val = Answer.timeis();
            value = QString::fromStdString(val);
            std::cout<< val << std::endl;

        };
        Status status = reader->Finish();
        if (status.ok()) {
            emit getValTimeSIg(this->value);
        } else {
            value = "Nothing to show";
        };
    }
signals:
    void getValTimeSIg(QString value);
private:
    std::unique_ptr<gettime::Stub> stub_;
    std::string val;
    QString value;
};

#endif // WIDGET_H
