#ifndef GRILLE_H
#define GRILLE_H


class Grid
{
public:
    Grid(int width, int height, int grille[width][height]): width(width), height(height), grille(grille){};
    int width;
    int height;
    int grille;

    void contruct(){
        for (int i = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                grille[i][j] = 0;
            }
        }
    }
};

#endif // GRILLE_H
