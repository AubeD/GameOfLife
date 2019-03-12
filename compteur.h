#ifndef COMPTEUR_H
#define COMPTEUR_H

#include <QObject>
//La classe compteur permet de gérer et afficher le score ainsi que les valeurs des cases du jeu (qui sont stockées dans une matrice)
class Compteur : public QObject
{   Q_OBJECT
    Q_PROPERTY(QString cptQML READ readCompteur NOTIFY cptChanged) //Permet le transfert du score au QML pour l'affichage : cptQML est utilisé dans le QML et mis à jour à l'aide de readCompteur lors de l'utilisation de cptChanged
    Q_PROPERTY(QString stQML READ readScoretotal NOTIFY stChanged) //Permet l'affichage du meilleur score
    Q_PROPERTY(QList<QString> casesQML READ readCases NOTIFY casesChanged) //Permet l'affichage des valeurs des cases de la grille
    Q_PROPERTY(QList<QString> couleurQML READ readColor NOTIFY colorChanged) // Permet de colorer les cases de la grille selon les valeurs
    Q_PROPERTY(bool dialog_visibleQML READ readDialog_visible NOTIFY dialogChanged) //Permet l'affichage d'un message lorsque l'on perd
public:
    explicit Compteur(QObject *parent=nullptr);
    Q_INVOKABLE void nouvelle_case(); // Permet la création d'une case de valeur 2 au hasard parmi les cases libres
    Q_INVOKABLE void up(); //Mouvement lors de l'appui sur la flêche up
    Q_INVOKABLE void down(); // flêche du bas
    Q_INVOKABLE void right(); //flêche de droite
    Q_INVOKABLE void left(); //flêche gauche
    Q_INVOKABLE void nouvelle_partie(); //Réinitialise la grille et le score
    Q_INVOKABLE void retour(); // Revient à l'état précédent
    Q_INVOKABLE void savePrecedent(); //Permet d'enregistrer un état pour la fonction retour()

    int rand_a_b(int a,int b); // Choisi un entier au hasard entre a et b

    QString readCompteur();
    QString readScoretotal();
    bool readDialog_visible();
    void score(); //Permet de calculer le score et le meilleur score
    QList<QString> readCases();
    QList<QString> readColor();

signals:
    void cptChanged();
    void stChanged();
    void casesChanged();
    void colorChanged();
    void dialogChanged();

public slots:

private:
    QString couleur[4][4]; //Stockage des couleurs des cases de la grille
    int cpt; //Stockage du score
    int st; //Stockage du meilleur score
    int cases[4][4]; //Stockage des valeurs des cases
    bool dialog_visible; //Dit si le message de game over est visible ou non
    int precedent[4][4]; //Stocke l'état précédent de la grille
};

#endif // COMPTEUR_H
