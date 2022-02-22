#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int* neighbours;
    int degree;
}Point;

Point* megepitSzomszedsagilista();
int** megepitSzomszedsagiMatrix();

int main() {
    int numberofPoints;
    Point* graph = megepitSzomszedsagilista(&numberofPoints);

    for (int i = 1; i <= numberofPoints; ++i) {
        printf("%d: %ddb:",i,graph[i].degree);
        for (int j = 0; j < graph[i].degree; ++j) {
            printf("%d ",graph[i].neighbours[j]);
        }
        printf("\n");
    }
    printf("\nMatrix:\n");

    int** matrix = megepitSzomszedsagiMatrix(&numberofPoints);

    for (int i = 1; i <= numberofPoints ; ++i) {

        for (int j = 1; j <= numberofPoints; ++j) {
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
    for (int i = 1; i <= numberofPoints; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}
Point* megepitSzomszedsagilista(int* numberofPoints){
    FILE* file = fopen("ellista.txt","r");

    if(file==NULL){
        printf("Fajlkezelesi hiba\n");
        return NULL;
    }
    int pontokSzama,ellekSzama;
    fscanf(file,"%d%d",&pontokSzama,&ellekSzama);

    Point* graph = (Point*) malloc(pontokSzama * sizeof(Point));

    for (int i = 1; i <= pontokSzama; ++i) {
        graph[i].neighbours = (int*) malloc((pontokSzama+1)*sizeof(int));
        graph[i].degree=0;
    }

    for (int i = 0; i < ellekSzama; ++i) {
        int point1,point2;
        fscanf(file,"%d",&point1);
        fscanf(file,"%d",&point2);


        graph[point1].neighbours[graph[point1].degree] = point2;
        graph[point2].neighbours[graph[point2].degree] = point1;


        graph[point1].degree++;
        graph[point2].degree++;

    }
    for (int i = 1; i <= pontokSzama; ++i) {
        realloc(graph[i].neighbours, sizeof(int)*(graph[i].degree+1));
    }
    fclose(file);
    *numberofPoints = pontokSzama;
    return graph;
}

int** megepitSzomszedsagiMatrix(int* numberofPoints){
    FILE* file = fopen("ellista.txt","r");

    if(file==NULL){
        printf("Fajlkezelesi hiba\n");
        return NULL;
    }
    int pontokSzama,ellekSzama;
    fscanf(file,"%d%d",&pontokSzama,&ellekSzama);

    int** matrix = (int**) malloc((pontokSzama+1)*sizeof(int*));

    for (int i = 1; i <= pontokSzama; ++i) {
        *(matrix+i) = (int*) calloc(pontokSzama+1,sizeof(int));
    }

    for (int i = 0; i < ellekSzama; ++i) {
        int el1,el2;
        fscanf(file,"%d%d",&el1,&el2);


        matrix[el1][el2]=1;
        matrix[el2][el1]=1;
    }
    fclose(file);
    *numberofPoints = pontokSzama;
    return matrix;
}