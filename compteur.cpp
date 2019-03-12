#include "compteur.h"
#include <QtWidgets/QMessageBox>
#include <QQuickView>


Compteur::Compteur(QObject *parent): QObject(parent) { //Constructeur
    cpt=0; //On initialise le score à 0
    st=0; //Lors de la création du compteur le meilleur score est à 0 aussi
    emit cptChanged(); //On signale que le compteur du score à été mis à jour
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            cases[i][j]=0; //On rempli la grille de 0 (ce qui signifie case vide)
    dialog_visible=false; //On ne veut pas afficher la fenetre de game over
    emit dialogChanged(); //On met à jour dialog_visible
    emit casesChanged(); //On met à jour la grille
}


QString Compteur::readCompteur(){ // On lit le score pour le transmettre au QML
    return QString::number(cpt);

}
QString Compteur::readScoretotal(){ // De même pour le meilleur score
    return QString::number(st);

}
bool Compteur::readDialog_visible(){ // De même pour le booléen signalant si la fenetre de game over est affichée
    return dialog_visible;

}

QList<QString> Compteur::readColor(){ //On lit les valeurs des cases ce qui nous permet de déterminer les couleurs des cases que l'on stocke dans la matrice couleur pour les transmettre au QML sous la forme d'une liste
    QList<QString> list;
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            switch (cases[i][j]) { //On fait une couleur différente pour chaque valeur que peuvent prendre les cases
            case 2:
                couleur[i][j]="#476FEC";
                list.append(couleur[i][j]);
                break;
            case 4:
                couleur[i][j]="#47C1EC";
                list.append(couleur[i][j]);
                break;
            case 8:
                couleur[i][j]="#47ECDA";
                list.append(couleur[i][j]);
                break;
            case 16:
                couleur[i][j]="#47EC98";
                list.append(couleur[i][j]);
                break;
            case 32:
                couleur[i][j]="#6AEC47";
                list.append(couleur[i][j]);
                break;
            case 64:
                couleur[i][j]="#E2EC47";
                list.append(couleur[i][j]);
                break;
            case 128:
                couleur[i][j]="#ECC947";
                list.append(couleur[i][j]);
                break;
            case 256:
                couleur[i][j]="#ECA847";
                list.append(couleur[i][j]);
                break;
            case 512:
                couleur[i][j]="#EC7747";
                list.append(couleur[i][j]);
                break;
            case 1024:
                couleur[i][j]="#EC4B47";
                list.append(couleur[i][j]);
                break;
            case 2048:
                couleur[i][j]="#EC4765";
                list.append(couleur[i][j]);
                break;
            default: //Si la case est vide ou au dessus de 2048 on met en gris
                couleur[i][j]="gray";
                list.append(couleur[i][j]);
                break;
            }

        }
    }
    return list;

}

void Compteur::nouvelle_partie(){
    cpt=0; //Lors d'une nouvelle partie on remet le score à 0 (mais pas le meilleur score (st))
    emit cptChanged(); //On signal le changement de score
    for(int i=0; i<4; i++)
        for(int j=0; j<4; j++)
            cases[i][j]=0; //On remet les cases vides
    dialog_visible=false; //On veut cacher la fenetre de game over
    emit dialogChanged(); // On signale les changement
    emit casesChanged();
}

QList<QString> Compteur::readCases(){ //On lit les valeurs de la matrice case pour les transmettre au QML sous forme de liste
    QList<QString> list;
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (cases[i][j]==0){
                list.append(""); //Si la valeur est 0 alors on veut une case vide
            }
            else{
                list.append(QString::number(cases[i][j])); // Sinon on veut voir la valeur affichée
            }

        }
    }
    score(); //On calcule le score et le meilleur score
    emit colorChanged(); //On signale le changement de couleur pour recalculer les couleurs selon les nouvelles valeurs
    return list;


}

void Compteur::score(){ //calcule le score et le meilleur score
    int somme=0;
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            somme=somme+cases[i][j]; //On somme la valeur des cases de la matrice
        }
    }
    cpt=somme; //On met le compteur de score à cette valeur
    if (st <= cpt){
        st= cpt;}//Si le meilleur score est inférieur au score actuel alors le meilleur score devient le score actuel
    emit cptChanged(); //On signale les changements
    emit stChanged();
}

void Compteur::nouvelle_case(){
    int compteur=0;
    //On compte le nombre de case vide (permet de vérifier que la grille n'est pas déjà pleine
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (cases[i][j]==0){
                compteur++;
            }
        }
    }
    if (compteur!=0){ //Si la grille n'est pas pleine alors on prend une case au hasard pour mettre un 2 dedans
        int Rligne=rand_a_b(0,4); //On choisi au hasard Rligne entre 0 et 4 non inclu
        int Rcolonne=rand_a_b(0,4); //De même pour Rcolonne
        while (cases[Rligne][Rcolonne]!=0){//si la case est déjà occupée on recommence jusqu'à tomber sur une case vide
            Rligne=rand_a_b(0,4);
            Rcolonne=rand_a_b(0,4);
        }
        cases[Rligne][Rcolonne]=2;
        emit casesChanged();
    }
    else{//Si la grille est pleine on affiche le message de game over
        dialog_visible=true;
        emit dialogChanged();
    }
}



void Compteur::up(){ //Mouvement lors de l'appui sur la flêche du haut
    //Copie du tableau initial:
    int copy[4][4];
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            copy[i][j]=cases[i][j];
        }
    }
    // déplacement: on déplace les cases vers le haut et on rassemble et somme les cases de même valeurs situé au dessus
    for (int i=0;i<3;i++){
        for (int j=0;j<4;j++){
            if (cases[i][j]==cases[i+1][j]){ //Si la case à la même valeur que la case d'au dessus on somme et rassemble
                cases[i][j]=cases[i][j]+cases[i+1][j];
                cases[i+1][j]=0;
            }
            if (cases[i][j]==0){ //Si la case est vide on déplace la case d'en dessous dessus
                cases[i][j]=cases[i+1][j];
                cases[i+1][j]=0;
            }
        }
    }
    // Vérification : On rééfectue le déplacement up() tant que le déplacement à changé quelque chose
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (cases[i][j]!=copy[i][j]){
                up();
                break; //Si le déplacement a changé une case cela suffit pour savoir qu'il faut réeffectuer up()
            }
        }
    }
    emit casesChanged(); //On signale le changement
}




void Compteur::down(){ //Même logique que pour up mais dans l'autre sens
    //Copie du tableau:
    int copy[4][4];
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            copy[i][j]=cases[i][j];
        }
    }
    // déplacement:
    for (int i=3;i>0;i--){
        for (int j=0;j<4;j++){
            if (cases[i][j]==cases[i-1][j]){
                cases[i][j]=cases[i][j]+cases[i-1][j];
                cases[i-1][j]=0;
            }
            if (cases[i][j]==0){
                cases[i][j]=cases[i-1][j];
                cases[i-1][j]=0;
            }
        }
    }
    // Vérification
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (cases[i][j]!=copy[i][j]){
                down();
                break;
            }
        }
    }
    emit casesChanged();
}

void Compteur::left(){ // De même pour le déplacement vers la gauche
    //Copie du tableau:
    int copy[4][4];
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            copy[i][j]=cases[i][j];
        }
    }
    // déplacement:
    for (int i=0;i<3;i++){
        for (int j=0;j<4;j++){
            if (cases[j][i]==cases[j][i+1]){
                cases[j][i]=cases[j][i]+cases[j][i+1];
                cases[j][i+1]=0;
            }
            if (cases[j][i]==0){
                cases[j][i]=cases[j][i+1];
                cases[j][i+1]=0;
            }
        }
    }
    // Vérification
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (cases[i][j]!=copy[i][j]){
                left();
                break;
            }
        }
    }
    emit casesChanged();
}

void Compteur::right(){// Même schéma que précédemment
    //Copie du tableau:
    int copy[4][4];
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            copy[i][j]=cases[i][j];
        }
    }
    // déplacement:
    for (int i=3;i>0;i--){
        for (int j=0;j<4;j++){
            if (cases[j][i]==cases[j][i-1]){
                cases[j][i]=cases[j][i]+cases[j][i-1];
                cases[j][i-1]=0;
            }
            if (cases[j][i]==0){
                cases[j][i]=cases[j][i-1];
                cases[j][i-1]=0;
            }
        }
    }
    // Vérification
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            if (cases[i][j]!=copy[i][j]){
                right();
                break;
            }
        }
    }
    emit casesChanged();
}
void Compteur::retour(){ //On revient à la situation précédente
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            cases[i][j]=precedent[i][j]; //La grille précédente était stockée dans précédent
        }
    }
    emit casesChanged();
}

void Compteur::savePrecedent(){ //On stocke la grille avant de la changer pour pouvoir faire retour (appelé dans QML)
    for (int i=0;i<4;i++){
        for (int j=0;j<4;j++){
            precedent[i][j]=cases[i][j];
        }
    }
}

// Trouver une valeur au hasard entre a et b : on suppose a<b
int Compteur::rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}
