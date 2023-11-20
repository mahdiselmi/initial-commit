#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include"vehicule.h"




QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_ajouter_clicked();

    void on_supprimer_clicked();



    void on_modifier_clicked();

void exportt();



    void on_trier_clicked(bool checked);











    void on_chercher_clicked();


    void on_restore_clicked();

    void on_ledaterech_clicked();

    void on_afficherstatistiques_clicked();

    void on_trie2_clicked(bool checked);

    void on_trie3_clicked(bool checked);

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

        Facture F;


};
#endif // MAINWINDOW_H
