#include "badis.h"
#include "ui_badis.h"
#include <QMessageBox>
#include "smtp.h"
#include <QString>
#include <QMediaPlayer>
#include <QDesktopWidget>
#include<QSystemTrayIcon>

badis::badis(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::badis)
{
        //MUSIC
    QMediaPlayer * musicplayer = new QMediaPlayer();
            musicplayer->setMedia(QUrl("qrc:/sounds/backgroundmusic.mp3"));
            musicplayer->play();

    ui->setupUi(this);
    ui->tabClient->setModel(tmpclient.afficherclient());
    ui->tabcarte->setModel(tmpcarte.affichercarte());
    ui->comboBox->setModel(tmpclient.getMailModel());
    ui->comboBox_2->setModel(tmpcarte.getMailModel());
    ui->comboBox_3->setModel(tmpclient.getMailModel());

       //EMAIL
    connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));
    connect(ui->exitBtn, SIGNAL(clicked()),this, SLOT(close()));
       //BACKGROUND
    QPixmap bkngd("C:/qtxoracle/projectcplus/bgpic.jpg");
    bkngd=bkngd.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background,bkngd);
    this->setPalette(palette);
        //notification
    notif=new QSystemTrayIcon(this);
        notif->setIcon(QIcon("C:/qtxoracle/projectcplus/iconclient.png"));
        //test
        resize(QDesktopWidget().availableGeometry(this).size() * 0.7);


}

badis::~badis()
{
    delete ui;
}
//client
void badis::on_ajouter_button_clicked()//ajouterclient
{
    QString nom=ui->nom_ajouter->text();
    QString email=ui->email_ajouter->text();
    QString prenom=ui->prenom_ajouter->text();
    int abonne_carte=ui->abonnecarte_ajouter->text().toInt();
    client c(email,nom,prenom,abonne_carte);
    bool added=c.ajouterclient();
    if(added) {ui->tabClient->setModel(tmpclient.afficherclient());

        ui->comboBox->setModel(tmpclient.getMailModel());
        ui->comboBox_3->setModel(tmpclient.getMailModel());

        notif->show();
        QString titre=ui->email_ajouter->text();
        QString msg=ui->nom_ajouter->text();

        qint8 duree=ui->spinBox->value();
        notif->showMessage(titre,msg,QSystemTrayIcon::Information,duree);
    }
}

void badis::on_pushButton_clicked()//supprimerclient
{
    QString mail=ui->emailasupprimer->text();
    client c;
    bool t=c.supprimerclient(mail);
    if(t)
    {
        ui->tabClient->setModel(tmpclient.afficherclient());
        ui->tabcarte->setModel(tmpcarte.affichercarte());
        ui->comboBox->setModel(tmpclient.getMailModel());
        ui->comboBox_3->setModel(tmpcarte.getMailModel());
    }
    else
    {

    }
}



void badis::on_comboBox_currentIndexChanged(const QString &arg1)
{
    //QString mail=QString::number(ui->comboBox->currentText().toInt());
    QString mail=arg1;
    QSqlQuery query;
    query.prepare("select * from client where EMAIL='"+mail+"'");
    query.exec();
    while(query.next())
    {
        ui->nom_modifier->setText(query.value(1).toString());
        ui->prenom_modifier->setText(query.value(2).toString());
        ui->nbcartes_modifier->setText(query.value(3).toString());
    }
}

void badis::on_pushButton_2_clicked()//modifierclient
{
    int nbcartes=ui->nbcartes_modifier->text().toInt();
    QString nom=ui->nom_modifier->text();
    QString prenom=ui->prenom_modifier->text();
    QString email = ui->comboBox->currentText();
    client c;
    bool t=c.modifierclient(email,nom,prenom,nbcartes);
    if(t)
    {
        ui->tabClient->setModel(tmpclient.afficherclient());

        ui->comboBox->setModel(tmpclient.getMailModel());
        ui->comboBox_3->setModel(tmpcarte.getMailModel());
    }
    else
    {

    }
}
//carte

void badis::on_ajouter_button_2_clicked()//ajoutercarte
{
    QString email=ui->comboBox_3->currentText();
    int e;
    carte c(email,e);
    bool added=c.ajoutercarte();
    if(added) {
        ui->tabcarte->setModel(tmpcarte.affichercarte());
        ui->comboBox_2->setModel(tmpcarte.getMailModel());
    }
}


void badis::on_comboBox_3_currentIndexChanged(const QString &arg1)
{

}







void badis::on_pushButton_3_clicked()//supprimercarte
{
    QString mail=ui->emailasupprimer_2->text();
    carte c;
    bool t=c.supprimercarte(mail);
    if(t)
    {
        ui->tabcarte->setModel(tmpcarte.affichercarte());
        ui->comboBox_2->setModel(tmpcarte.getMailModel());

    }
    else
    {

    }
}

void badis::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    QString mail= ui->comboBox_2->currentText();
    QSqlQuery query;
    query.prepare("select * from carte_fid where EMAIL='"+mail+"'");
    query.exec();
    while(query.next())
    {
        ui->carte_modifier->setText(query.value(1).toString());

    }
}





void badis::on_pushButton_4_clicked()//modifercarte
{
    int nb_points=ui->carte_modifier->text().toInt();
    QString email = ui->comboBox_2->currentText();
    carte c;
    bool t=c.modifiercarte(email,nb_points);
    if(t)
    {
        ui->tabcarte->setModel(tmpcarte.affichercarte());
        ui->comboBox->setModel(tmpcarte.getMailModel());
    }
    else
    {

    }
}

void badis::on_pushButton_5_clicked()//ajouterpoints
{
    QString email = ui->comboBox_2->currentText();
    tmpcarte.ajouterpoints(email);
    ui->tabcarte->setModel(tmpcarte.affichercarte());
}





void badis::on_lineEdit_chercher_textChanged(const QString &arg1)
{
    ui->tabClient->setModel(tmpclient.chercher_client_email(arg1));
}

void badis::on_lineEdit_textChanged(const QString &arg1)
{
    ui->tabClient->setModel(tmpclient.chercher_client_nom(arg1));
}


void badis::on_pushButton_tri_clicked()
{
    ui->tabClient->setModel(tmpclient.afficher_tri_email());
}

void badis::on_pushButton_tri_pt_clicked()
{
    ui->tabcarte->setModel(tmpcarte.afficher_tri_nbpoints());
}


void badis::sendMail()
{
    Smtp* smtp = new Smtp(ui->uname->text(), ui->paswd->text(), ui->server->text(), ui->port->text().toUShort());
    connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent(QString)));


    smtp->sendMail(ui->uname->text(), ui->rcpt->text() , ui->subject->text(),ui->msg->toPlainText());
}

void badis::mailSent(QString status)
{
    if(status == "Message sent")
        QMessageBox::warning( nullptr, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );
}


void badis::on_sendBtn_clicked()
{
    sendMail();
}



void badis::on_lineEdit_2_email_carte_textChanged(const QString &arg1)
{
    ui->tabcarte->setModel(tmpcarte.chercher_carte_email(arg1));
}
