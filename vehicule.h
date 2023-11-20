#ifndef ETUDIANT_H
#define ETUDIANT_H
#include<QSqlQueryModel>
#include<QString>
#include<QTableView>
class Facture
{
public:
    Facture();
    Facture (int,int,QString,QString,QString,int,QString
             );
    int getbudget();
QString getstatus();

    QString getmatricule();
    QString getpiecesderechanges();
    QString gettypedepanne();
    int getid();
     int getdate();
    void setbudget(int);
   ;
    QMap<QString, QVariant> getStatistics();

    void setmatricule(QString);
    void setpiecesdedrechanges(QString);void settypedepanne(QString);
    void setid(int);
     void setdate(int);
      void setstatus(QString);
bool ajouter();
QSqlQueryModel*afficher();
QSqlQueryModel * tri_typedepanne();
QSqlQueryModel * tri_matricule();QSqlQueryModel * tri_piecesderechanges();
bool supprimer(QString);
bool update( );
 QSqlQueryModel* rechercher(int);
  QSqlQueryModel* planifier(int);
bool restaurerFacturesSupprimees();
private:
    int budget,id,date;
    QString matricule,piecesderechanges,typedepanne,status;


};

#endif // ETUDIANT_H
