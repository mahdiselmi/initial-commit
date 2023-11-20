
#include "mainwindow.h"
#include "vehicule.h"
#include"QValidator"
#include"QMessageBox"
#include"ui_mainwindow.h"
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include "qpainter.h"
#include<QSqlError>
#include<QSqlQuery>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)

  {
   ui->setupUi(this);
   ui->tableaufacture->setModel(F.afficher());
}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow:: on_ajouter_clicked()



{int id=ui->leid->text().toInt();
    int budget=ui->lebudget->text().toInt();
    QString matricule=ui->lematricule->text();
    QString  piecesderechanges=ui->lepiecesderechange->text();
    QString typedepanne=ui->letypedepanne->text();
    int date=ui->ledate->text().toInt();
  QString status=ui->lestatus->text();
    Facture F(id,budget,matricule,piecesderechanges,typedepanne,date,status);
   bool test=F.ajouter();
   QMessageBox msgBox;
    if (test)
    {
        msgBox.setText("Ajout avec succes");
        ui->tableaufacture->setModel(F.afficher());

    } else
        msgBox.setText("Echec d ajout");
    msgBox.exec();


    // Code à exécuter lorsque le bouton "Ajouter" est cliqué
    // Par exemple, ajouter un élément à la liste, afficher une boîte de dialogue, etc.
}

void MainWindow::
 on_supprimer_clicked()
{
    Facture F1;
    F1.setmatricule (ui->lematriculesupp->text());
    bool test =F1.supprimer(F1.getmatricule());  QMessageBox msgBox;
    if (test)

    {
        msgBox.setText("supp avec succes");
         ui->tableaufacture->setModel(F1.afficher());

    }
    else
            msgBox.setText("Echec d ajout");
        msgBox.exec();

}void MainWindow::on_modifier_clicked()

{
    int budget=ui->lebudget->text().toInt();

    QString matricule=ui->lematricule2->text();
    QString piecesderechanges=ui->lepiecesderechnges2->text();
    QString typedepanne=ui->letypedepanne2->text();
    int id=ui->leid->text().toInt(); QString date=ui->ledate->text();
Facture F;
    bool test= F.update();
    if (test)
    {
        ui->tableaufacture->setModel(F.afficher());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                    QObject::tr("modification effectué\n"
                           "Click cancel to exit."), QMessageBox::Cancel);
        ui->tableaufacture->setModel(F.afficher());
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                              ("modification non effectué\n"
                              "Click cancel to exit."), QMessageBox::Cancel);
}







void MainWindow::on_trier_clicked(bool )
{
   bool test=F.tri_typedepanne();
   if(test)
   { ui->tableaufacture->setModel(F.tri_typedepanne());

       QMessageBox::information(nullptr,QObject::tr("OK"),
                                    QObject::tr("modification effectué\n"
                                           "Click cancel to exit."), QMessageBox::Cancel);

}}




void MainWindow::on_chercher_clicked()
{ Facture F1;
    F1.setid( (ui->recher->text().toInt()));
    bool test =F1.rechercher(F1.getid());  QMessageBox msgBox;
    if (test)

    {
        msgBox.setText("rechercavec succes");
         ui->tableaufacture->setModel(F1.afficher());

    }
    else
            msgBox.setText("Echec d ajout");
        msgBox.exec();
 /*int id= ui->recher->text().toInt();  // Ajoutez un QLineEdit pour l'id dans votre interface

    QSqlQueryModel*resultatRecherche=F.rechercher(id);

    if (resultatRecherche->rowCount() > 0) {
        // Des résultats ont été trouvés, affichez-les dans une QMessageBox
        QString message = "Résultats de la recherche :\n";
        for (int row = 0; row < resultatRecherche->rowCount(); ++row) {
            for (int col = 0; col < resultatRecherche->columnCount(); ++col) {
                message += resultatRecherche->data(resultatRecherche->index(row, col)).toString() + " ";
            }
            message += "\n";
        }
        QMessageBox::information(this, "Résultats de la recherche", message);
    } else {
        // Aucun résultat trouvé
        QMessageBox::information(this, "Résultats de la recherche", "Aucun résultat trouvé pour l'ID spécifié.");
    }

    // Libérer la mémoire du modèle
    delete resultatRecherche;

*/}




void MainWindow::on_restore_clicked()
{ Facture F; // Assuming F is an instance of your Facture class

        if (F.restaurerFacturesSupprimees())
        {
            QMessageBox::information(this, "Restauration réussie", "Les factures ont été restaurées avec succès.");
            ui->tableaufacture->setModel(F.afficher());
            // Rafraîchissez votre interface utilisateur ou mettez à jour la vue au besoin
        }
        else
        {
            QMessageBox::warning(this, "Erreur de restauration", "La restauration des factures a échoué.");
        }

}


void MainWindow::on_ledaterech_clicked()
{
    int date= ui->daterech->text().toInt();

        QSqlQueryModel*resultatRecherche=F.planifier(date);

        if (13>resultatRecherche->rowCount() > 0) {

            QString message = "les factures de ce mois :\n";
            for (int row = 0; row < resultatRecherche->rowCount(); ++row) {
                for (int col = 0; col < resultatRecherche->columnCount(); ++col) {
                    message += resultatRecherche->data(resultatRecherche->index(row, col)).toString() + " ";
                }
                message += "\n";
            }
            QMessageBox::information(this, "les factures de ce  mois ", message);
        } else {
            // Aucun résultat trouvé
            QMessageBox::information(this, "Résultats de la recherche", "Aucun résultat trouvé pour l'ID spécifié.");
        }

        delete resultatRecherche;

}

void MainWindow::on_afficherstatistiques_clicked()
{
    Facture F;

    // Appelez la fonction statistique
    QMap<QString, QVariant> statistics = F.getStatistics();

    // Affichez les résultats où vous le souhaitez, par exemple dans une boîte de dialogue
    QString message = "Statistiques:\n";
    for (auto it = statistics.begin(); it != statistics.end(); ++it) {
        message += QString("%1: %2\n").arg(it.key(), it.value().toString());
    }

    QMessageBox::information(this, "Statistiques", message);

}






void MainWindow::on_trie2_clicked(bool checked)
{

    bool test=F.tri_matricule();
    if(test)
    { ui->tableaufacture->setModel(F.tri_matricule());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("modification effectué\n"


                                                 "Click cancel to exit."), QMessageBox::Cancel);


}
}

void MainWindow::on_trie3_clicked(bool checked)
{
    bool test=F.tri_piecesderechanges();
    if(test)
    { ui->tableaufacture->setModel(F.tri_piecesderechanges());

        QMessageBox::information(nullptr,QObject::tr("OK"),
                                     QObject::tr("modification effectué\n"
                                            "Click cancel to exit."), QMessageBox::Cancel);


}
}

void MainWindow::on_pushButton_clicked()
{
    exportt();
}
