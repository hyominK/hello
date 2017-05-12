#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QTcpSocket socket;
    QString id;
public slots:
    void sendMessage();
    void recvMsg();
private slots:
    void on_pushButton_connect_clicked();
    void on_lineEdit_msg_returnPressed();
};

#endif // MAINWINDOW_H
