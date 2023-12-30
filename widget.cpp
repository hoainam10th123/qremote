#include "widget.h"
#include "ui_widget.h"
#include <QThread>
#include <QProcess>
#include <QMessageBox>
#include <cstring>

extern "C" {
    #include "vnc_plugin_client/vncclient.h"
}

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setWindowTitle("QRemote Client");
}

Widget::~Widget()
{
    delete ui;    
}

void Widget::setParams(char** argv){
    this->argv = argv;
}

void Widget::on_pushButton_clicked()
{
    QString server = ui->lineEditServer->text();

    int exitCode = QProcess::execute("ping", QStringList() << "-c1" << server);
    if (0 == exitCode) {
        // it's alive
        qDebug() << "it's alive";
        std::string serverStringStd = server.toStdString();// 127.0.0.1

        char **myArgv = new char *[2];
        myArgv[0] = new char[strlen(argv[0]) + 1];
        strcpy(myArgv[0], argv[0]);

        myArgv[1] = new char[serverStringStd.length() + 1];
        strcpy(myArgv[1], serverStringStd.c_str());

        QThread *thread = QThread::create([=]{
            start(2, myArgv);
        });
        thread->start();
    } else {
        // it's dead
        qDebug() << "it's dead";
        QMessageBox::critical(this, tr("QRemote Client"),
                                       tr("Server name or IP invalid.\n"
                                          "We can't ping to server"));
    }
}

