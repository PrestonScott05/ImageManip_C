#ifndef _IMAGE_H_
#define _IMAGE_H_

typedef struct _pixel {
    int red;
    int green;
    int blue;
} Pixel;

typedef struct _imagePPM {
    char magic[3]; 
    int numRows; 
    int numCols; 
    int maxVal; 
    Pixel **pixels; 
} ImagePPM;

typedef struct _imagePGM {
    char magic[3]; 
    int numRows; 
    int numCols; 
    int maxVal;
    int **pixels; 
} ImagePGM;

ImagePPM *readPPM(char *filename);
int writePPM(ImagePPM *pImagePPM, char *filename);
void freePPM(ImagePPM *pImagePPM);

ImagePGM *readPGM(char *filename);
int writePGM(ImagePGM *pImagePGM, char *filename);
void freePGM(ImagePGM *pImagePGM);

ImagePGM *convertToPGM(ImagePPM *pImagePPM);
ImagePGM *shrinkPGM(ImagePGM *pImagePGM);

#endif
