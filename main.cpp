#include "widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    gettimeClient client(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    client.timeget();
    Widget w;
    w.show();
    return a.exec();
}
