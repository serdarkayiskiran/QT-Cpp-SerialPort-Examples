#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    int i=0;

    bool baglantiAcik;
    bool baglantiKapali;

private slots:

void serialPortAc();
void serialPortKapat();
void veriOku();
void veriGonder(const QByteArray &data);

void on_seriPortAcButon_clicked();
void on_seriPortKapatButon_clicked();



void on_veriGonderButon_clicked();

void on_terminalEkranitTemizle_clicked();

public slots:


private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
