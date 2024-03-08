#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"



ImagePPM *readPPM(char *filename)
{
    int rows;
    int cols;
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        return NULL;
    }


    ImagePPM *image = malloc(sizeof(ImagePPM));
    
    fscanf(input, "%s", image->magic);
    fscanf(input, "%d", &image->numCols);
    fscanf(input, "%d", &image->numRows);
    fscanf(input, "%d", &image->maxVal);
    
    rows = image->numRows;
    cols = image->numCols;

   

    image->pixels = (Pixel **)malloc(sizeof(Pixel *)*rows);
    for (int i = 0; i < rows; i++) {
        image->pixels[i] = (Pixel *)malloc(sizeof(Pixel)*cols);
    }


    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            fscanf(input, "%d %d %d", &image->pixels[i][j].red, &image->pixels[i][j].green, &image->pixels[i][j].blue);
            
        }
    }

    fclose(input);

    return image;

}



int writePPM(ImagePPM *pImagePPM, char *filename)
{   
    FILE *output= fopen(filename, "w");
    if (output == NULL) {
        return 0;
    }

    fprintf(output, "%s\n", pImagePPM->magic);
    fprintf(output, "%d %d\n", pImagePPM->numCols, pImagePPM->numRows);
    fprintf(output, "%d\n", pImagePPM->maxVal);

    for (int i=0;i<pImagePPM->numRows;i++) {
      for (int j=0;j<pImagePPM->numCols;j++) {
         fprintf(output, "%3d %3d %3d\t ", pImagePPM->pixels[i][j].red, pImagePPM->pixels[i][j].green, pImagePPM->pixels[i][j].blue);
        }
      fprintf(output, "\n");
    }
    fclose(output);

    return 1;
}



void freePPM(ImagePPM *pImagePPM)
{
    for (int i=0;i<pImagePPM->numRows;i++) {
        free(pImagePPM->pixels[i]);
    }
    free(pImagePPM->pixels);

    free(pImagePPM);
}



ImagePGM *readPGM(char *filename)
{
    int rows;
    int cols;
    FILE *input = fopen(filename, "r");
    if (input == NULL) {
        return NULL;
    }


    ImagePGM *image = malloc(sizeof(ImagePGM));
    
    fscanf(input, "%s", image->magic);
    fscanf(input, "%d", &image->numCols);
    fscanf(input, "%d", &image->numRows);
    fscanf(input, "%d", &image->maxVal);
    
    rows = image->numRows;
    cols = image->numCols;



    image->pixels = (int **)malloc(sizeof(int *)*rows);
    for (int i = 0; i < rows; i++) {
        image->pixels[i] = (int *)malloc(sizeof(int)*cols);
    }

  

    for (int i=0;i<rows;i++) {
        for (int j=0;j<cols;j++) {
            fscanf(input, "%d", &image->pixels[i][j]);
        }
    }

    fclose(input);
    return image;

    
}



int writePGM(ImagePGM *pImagePGM, char *filename)
{
    FILE *output= fopen(filename, "w");
    if (output == NULL) {
        return 0;
    }

    fprintf(output, "%s\n", pImagePGM->magic);
    fprintf(output, "%d %d\n", pImagePGM->numCols, pImagePGM->numRows);
    fprintf(output, "%d\n", pImagePGM->maxVal);

    

    for (int i=0;i<pImagePGM->numRows;i++) {
      for (int j=0;j<pImagePGM->numCols;j++) {
         fprintf(output, "%3d ", pImagePGM->pixels[i][j]);
        }
      fprintf(output, "\n");
    }

    fclose(output);

    return 1;
}



void freePGM(ImagePGM *pImagePGM)
{
    for (int i=0;i<pImagePGM->numRows;i++) {
        free(pImagePGM->pixels[i]);
    }
    free(pImagePGM->pixels);

    free(pImagePGM);
}

ImagePGM *convertToPGM(ImagePPM *pImagePPM)
{   

    ImagePGM *newPGM = malloc(sizeof(ImagePGM));

    newPGM->pixels = (int **)malloc(sizeof(int *) * pImagePPM->numRows);
    for (int i = 0; i < pImagePPM->numRows; i++) {
        newPGM->pixels[i] = (int *)malloc(sizeof(int) * pImagePPM->numCols);
    }

    strcpy(newPGM->magic, "P2");
    newPGM->numCols = pImagePPM->numCols;
    newPGM->numRows = pImagePPM->numRows;
    newPGM->maxVal = pImagePPM->maxVal;

    

    int avg;
    int sum= 0;
    for (int i = 0 ; i < pImagePPM->numRows; i++) {
        for (int j =0; j < pImagePPM->numCols; j++) {
            sum += pImagePPM->pixels[i][j].red + pImagePPM->pixels[i][j].green + pImagePPM->pixels[i][j].blue;
            avg = sum / 3;
            newPGM->pixels[i][j] = avg;
            sum = 0;
            avg = 0;
        }
    }

    return newPGM;
}

ImagePGM *shrinkPGM(ImagePGM *pImagePGM)
{   
    int rows = pImagePGM->numRows / 2;
    int cols = pImagePGM->numCols / 2;

    ImagePGM *shrunkenPPM = malloc(sizeof(ImagePGM));
    shrunkenPPM->pixels = (int **)malloc(sizeof(int *) * rows);
    for (int i = 0; i < rows; i++) {
        shrunkenPPM->pixels[i] = (int *)malloc(sizeof(int) * cols);
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            int sum = 0;
            for (int x = 0; x < 2; x++) {
                for (int y = 0; y < 2; y++) {
                    sum+= pImagePGM->pixels[2*i+x][2*j+y];
                }
            }
            shrunkenPPM->pixels[i][j] = sum / 4;
        }
    }

    strcpy(shrunkenPPM->magic, pImagePGM->magic);
    shrunkenPPM->numCols = cols;
    shrunkenPPM->numRows = rows;
    shrunkenPPM->maxVal = pImagePGM->maxVal;

    return shrunkenPPM;
}
