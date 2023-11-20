#include "mainwindow.h"

#include"QValidator"
#include"QMessageBox"
#include"ui_mainwindow.h"
#include <QFileDialog>
#include <QtPrintSupport/QPrinter>
#include "qpainter.h"

#include<QSqlQuery>

#include "vehicule.h"
#include<QSqlQuery>
#include<QtDebug>
#include<QObject>
#include<QTableView>
#include<QSqlError>
Facture::Facture()
{id=0;
    budget=0;
      matricule=" ";
      piecesderechanges=" ";
        typedepanne=" ";
         date=0;


}
Facture::Facture(int id,int budget,QString matricule,QString typedepanne,QString piecesderechanges,int date,QString status )
{
    this->budget=budget;
    this->matricule=matricule;
    this->piecesderechanges=piecesderechanges;
    this->typedepanne =typedepanne;
     this->id=id; this->date=date;
    this->status=status;
}
int Facture::getbudget()
{
    return budget;
}
QString Facture::getmatricule()
{
    return matricule;
}
QString Facture::getpiecesderechanges()
{
    return piecesderechanges;
}
int Facture::getdate()
{
    return date;
}

QString Facture::gettypedepanne()
{
    return  typedepanne;
}
int Facture::getid()
{
    return id;
}

QString Facture::getstatus()
{
    return status;
}

void Facture::setbudget(int budget)
{
    this->budget=budget;

}
void Facture::setdate(int date)
{
    this->date=date;

}
void Facture::setmatricule(QString matricule)
{
    this->matricule=matricule
            ;

}
void Facture::setpiecesdedrechanges(QString piecesderechanges)
{
    this->piecesderechanges=piecesderechanges;


}

void Facture::settypedepanne(QString typedepanne)
{
    this->typedepanne=typedepanne;


}void Facture::setid(int id)
{this->id=id;}

void Facture::setstatus(QString status)
{this->status=status;}

bool Facture::ajouter()
{


    QSqlQuery query;
    QString budget_string=QString::number(budget);
 QString id_string=QString::number(id);QString date_string=QString::number(date);
 query.prepare("INSERT INTO FINANCE(BUDGET, MATRICULE, TYPEDEPANNE, PIECESDERECHANGES, ID, LADATE, STATUS)"
               "VALUES (:BUDGET, :MATRICULE, :TYPEDEPANNE, :PIECESDERECHANGES, :ID, :LADATE, 'active')");
         query.bindValue(":BUDGET", budget_string);
         query.bindValue(":MATRICULE", matricule);
         query.bindValue(":TYPEDEPANNE", typedepanne);
         query.bindValue(":PIECESDERECHANGES", piecesderechanges);
query.bindValue("active", status);
query.bindValue(":ID", id_string);

query.bindValue(":LADATE", date);


               return query.exec();


}
QSqlQueryModel *Facture::afficher()
{
    QSqlQueryModel *model=new QSqlQueryModel();

          model->setQuery("SELECT* FROM FINANCE");
          model->setHeaderData(0, Qt::Horizontal, QObject::tr("BUDGET"));
          model->setHeaderData(1, Qt::Horizontal, QObject::tr("MATRICULE"));
          model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPEDEPANNE"));
          model->setHeaderData(3, Qt::Horizontal, QObject::tr("PIECESDERECHANGES"));
          model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));

           model->setHeaderData(5, Qt::Horizontal, QObject::tr("LADATE"));




          return  model;}

bool Facture::supprimer(QString matricule)
{
    QSqlQuery query;

    query.prepare("DELETE FROM FINANCE WHERE MATRICULE = :MATRICULE");

query.bindValue(":MATRICULE", matricule);
    return query.exec();
}

bool Facture::update(){
    QSqlQuery query;

    query.prepare("UPDATE FINANCE SET BUDGET  = :BUDGET , MATRICULE = :MATRICULE, PIECESDERECHANGES= :PIECESDERECHANGES, TYPEDEPANNE = :TYPEDEPANNE ,ID=:ID,LADATE=DATE");

    query.bindValue("BUDGET", budget);
    query.bindValue(":MATRICULE", matricule);
    query.bindValue(":TYPEDEPANNE", typedepanne);
    query.bindValue(":PIECESDERECHANGES", piecesderechanges);

    query.bindValue(":ID", id);

    query.bindValue("LADATE", id);

    return query.exec();
}

QSqlQueryModel * Facture::tri_typedepanne()
{QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FINANCE order by TYPEDEPANNE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("BUDGET"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("MATRICULE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPEDEPANNE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PIECESDERECHANGES"));

model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("LADATE"));
    return model;
}
QSqlQueryModel * Facture::tri_matricule()
{QSqlQueryModel * model= new QSqlQueryModel();


model->setQuery("select * from FINANCE order by MATRICULE");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("BUDGET"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("MATRICULE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPEDEPANNE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PIECESDERECHANGES"));

model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("LADATE"));
    return model;
}

QSqlQueryModel* Facture::rechercher(int id)
{QSqlQuery query;

    query.prepare("SELECT FROM FINANCE WHERE ID = :ID");

query.bindValue(":MATRICULE", matricule);
    //return query.exec();
   /* QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Construction de la requête en fonction de l'id fourni
    QString queryString = "SELECT * FROM FINANCE WHERE ID = " + QString::number(id);
    query.prepare(queryString);

    if (query.exec()) {
        model->setQuery(query);
    *

    return model;
*/}
QSqlQueryModel* Facture::planifier(int date)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;


    QString queryString = "SELECT * FROM FINANCE WHERE LADATE = "  + QString ::number(date) ;
    query.prepare(queryString);

    if (query.exec()) {
        model->setQuery(query);
    }

    return model;
}
bool Facture::restaurerFacturesSupprimees()
{
    QSqlQuery query;

    // Mettez à jour la colonne 'status' pour restaurer les factures
    query.prepare("UPDATE FINANCE SET STATUS = 'active' WHERE STATUS = 'deleted'");

    return query.exec();
}
QMap<QString, QVariant> Facture::getStatistics()
{
    QMap<QString, QVariant> statistics;

    QSqlQuery query;


    query.exec("SELECT COUNT(*) FROM FINANCE");
    if (query.next()) {
        statistics["TotalFactures"] = query.value(0);


    query.exec("SELECT SUM(BUDGET) FROM FINANCE");
    if (query.next()) {
        statistics["BudgetTotal"] = query.value(0);
    }


    query.exec("SELECT AVG(BUDGET) FROM FINANCE");
    if (query.next()) {
        statistics["MoyenneBudget"] = query.value(0);
    }


    return statistics;
    }}
    QSqlQueryModel * Facture::tri_piecesderechanges(){
QSqlQueryModel * model= new QSqlQueryModel();

model->setQuery("select * from FINANCE order by PIECESDERECHANGES");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("BUDGET"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("MATRICULE"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("TYPEDEPANNE"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("PIECESDERECHANGES"));

model->setHeaderData(4, Qt::Horizontal, QObject::tr("ID"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("LADATE"));
    return model;
}
    void MainWindow::exportt()
    {
        QString filePath = QFileDialog::getSaveFileName(nullptr, "Exporter en PDF", "", "Fichiers PDF (*.pdf)");

                if (filePath.isEmpty()) {
                    return;
    }
                       QPrinter printer;
                       printer.setOutputFormat(QPrinter::PdfFormat);
                       printer.setOutputFileName(filePath);

                       QPainter painter(&printer);


                       painter.begin(&printer);


                       printer.setPageSize(QPrinter::A4);


                       painter.setFont(QFont("Arial", 12));


                       painter.drawText(100, 100, "      LIste des Factures          ");
                       painter.drawText(100, 120,  "PIECESRCH");
                       painter.drawText(200, 120,   "MATRICULE");
                       painter.drawText(300, 120,    "TYPEDEPANNE");

                       QSqlQuery query;
                       query.prepare("SELECT * FROM FINANCE");
                       if (query.exec()) {
                           int row = 140;
                           int rowCount = 0;
                           while (query.next()) {

                               QString matricule= query.value("MATRICULE").toString();
                               QString typedepanne = query.value("TYPEDEPANNE").toString();
    QString piecesderechanges = query.value("PIECESDERECHANGES").toString();

                               painter.drawText(100, row, matricule);
                               painter.drawText(200, row, typedepanne);
                               painter.drawText(300, row, piecesderechanges);
                               row += 20;
                               rowCount++;
                               if (rowCount % 20 == 0) {
                                   printer.newPage();
                                   row = 100;
                               }
                           }
                       } else {

                           QMessageBox::warning(this, "Erreur", "Erreur lors de l'exécution de la requête SQL : " + query.lastError().text());
                       }
                       painter.end();

    }
