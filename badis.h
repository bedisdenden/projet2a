#ifndef badis_H
#define badis_H
#include "carte.h"
#include "client.h"
#include <QDialog>
#include "smtp.h"
#include <QString>
#include <QMediaPlayer>
#include<QSystemTrayIcon>

namespace Ui {
class badis;
}

class badis : public QDialog
{
    Q_OBJECT

public:
    explicit badis(QWidget *parent = nullptr);
    ~badis();

private slots:


    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_ajouter_button_2_clicked();

    void on_pushButton_3_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_comboBox_3_currentIndexChanged(const QString &arg1);

    void on_lineEdit_chercher_textChanged(const QString &arg1);

    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_tri_clicked();

    void sendMail();
      void mailSent(QString);

      void on_sendBtn_clicked();
void on_ajouter_button_clicked();

      void on_pushButton_tri_pt_clicked();


      void on_lineEdit_2_email_carte_textChanged(const QString &arg1);

private:
    Ui::badis *ui;
    carte tmpcarte;
    client tmpclient;
    QMediaPlayer * musicplayer = new QMediaPlayer();
    QSystemTrayIcon *notif;

};

#endif // badis_H
