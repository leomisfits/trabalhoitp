//98337687
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int r;
    int g;
    int b;
} Pixel;

int saturacao(int v) {
    if (v > 255) return 255;
    if (v < 0) return 0;
    return v;
}

Pixel** applyFilterTresholding(Pixel** filtered, Pixel** newImg,int height, int width) {
    int i;
    int b;
    int acc;
    long int tresh = 0, treshr = 0,treshg = 0,treshb = 0;
        for (i = 0; i < height ; ++i)
    {
        for ( b = 0; b < width ; ++b)
        {
            treshr = (newImg[i][b].r/10) + treshr;
            treshg = (newImg[i][b].g/10) + treshg;
            treshb = (newImg[i][b].b/10) + treshb;

        }
    }
    tresh = treshr/(height*width);
    tresh += treshg/(height*width);
    tresh+= treshb/(height*width);
    tresh = (tresh*10)/3;
    printf("treshrr = %li\n",tresh);
    printf("treshr = %li\ntreshg = %li\ntreshb = %li",treshr,treshg,treshb);


    for (i = 0; i < height ; ++i)
    {
        for ( b = 0; b < width; ++b)
        {
            if ((newImg[i][b].r + newImg[i][b].g + newImg[i][b].b)/3 > tresh)
            {
             newImg[i][b].r = 255;
             newImg[i][b].g = 255;
             newImg[i][b].b = 255;
            }
            else{
                newImg[i][b].r = 1;
                newImg[i][b].g = 1;
                newImg[i][b].b = 1;
            }
            filtered[i][b].r = newImg[i][b].r;
            filtered[i][b].g = newImg[i][b].g;
            filtered[i][b].b = newImg[i][b].b;
        }
    }

    return filtered;
}


Pixel** applyFilterBlur(Pixel** filtered, Pixel** newImg,int height, int width) {
    int i;
    int b;
    int acc;

    for (i = 1; i < height - 1; ++i)
    {
        for ( b = 1; b < width - 1; ++b)
        {
            acc = newImg[i][b].r * 1.2/9.0;
            acc += newImg[i-1][b].r * 1.2/9.0; /* vizinho de cima */
            acc += newImg[i+1][b].r * 1.2/9.0; /* vizinho de baixo */
            acc += newImg[i][b-1].r * 1.2/9.0; /* vizinho da esquerda */
            acc += newImg[i][b+1].r * 1.2/9.0; /* vizinho da direita */
            acc += newImg[i-1][b-1].r * 1.2/9.0; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].r * 1.2/9.0; /* vizinho superior direito */
            acc += newImg[i+1][b-1].r * 1.2/9.0; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].r * 1.2/9.0; /* vizinho inferior direito */

            filtered[i][b].r = saturacao(acc);

            acc = newImg[i][b].g * 1.2/9.0;
            acc += newImg[i-1][b].g * 1.2/9.0; /* vizinho de cima */
            acc += newImg[i+1][b].g * 1.2/9.0; /* vizinho de baixo */
            acc += newImg[i][b-1].g * 1.2/9.0; /* vizinho da esquerda */
            acc += newImg[i][b+1].g * 1.2/9.0; /* vizinho da direita */
            acc += newImg[i-1][b-1].g * 1.2/9.0; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].g * 1.2/9.0; /* vizinho superior direito */
            acc += newImg[i+1][b-1].g * 1.2/9.0; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].g * 1.2/9.0; /* vizinho inferior direito */

            filtered[i][b].g = saturacao(acc);

            acc = newImg[i][b].b * 1.2/9.0;
            acc += newImg[i-1][b].b * 1.2/9.0; /* vizinho de cima */
            acc += newImg[i+1][b].b * 1.2/9.0; /* vizinho de baixo */
            acc += newImg[i][b-1].b * 1.2/9.0; /* vizinho da esquerda */
            acc += newImg[i][b+1].b * 1.2/9.0; /* vizinho da direita */
            acc += newImg[i-1][b-1].b * 1.2/9.0; /* vizinho superior esquerdo */
            acc += newImg[i-1][b+1].b * 1.2/9.0; /* vizinho superior direito */
            acc += newImg[i+1][b-1].b * 1.2/9.0; /* vizinho inferior esquerdo */
            acc += newImg[i+1][b+1].b * 1.2/9.0; /* vizinho inferior direito */

            filtered[i][b].b = saturacao(acc);

        }
    }

    return filtered;
}

void save_image(char* name, Pixel** img, int width, int height) {
    FILE* file;
    int i;
    int j;

    file = fopen(name, "w");

    fprintf(file, "P3\n%i %i\n255\n", width, height);
    for (i = 0; i < width; ++i) {
        for (j = 0; j < height; ++j) {
            fprintf(file, "%i %i %i\n", img[i][j].r, img[i][j].g, img[i][j].b);
        }
    }

    fclose(file);
}

Pixel** get_image(FILE* img, Pixel ** newImg,int* height, int* width) {
    int i;
    int j;
    int fcount;
    int scount;
    int count;
    int dcc;
    char init[3];
    fscanf(img,"%s",init);

    if (init[0] == 'P' && init[1] == '3') {
        printf("worked!\n");
        fscanf(img,"%d %d",&j,&i);
        *width = j;
        *height = i;
        fscanf(img, "%d",&dcc);
        newImg = (Pixel**) malloc(sizeof(Pixel*) * i);

        for ( count = 0; count < i ; ++count)
        {
            newImg[count] = (Pixel*) malloc(sizeof(Pixel) * j);
        }
        for (fcount = 0; fcount < i ; ++fcount)
        {
            for (scount = 0; scount < j; ++scount)
            {
                fscanf(img,"%i %i %i",&newImg[fcount][scount].r,&newImg[fcount][scount].g,&newImg[fcount][scount].b);
            }
        }
    }
    else
        printf("Type of newFile not recognized\n");

    fclose(img);
    return newImg;
}
void func (int a){
    printf("teste %i\n",a);
}


int main(int argc, char const *argv[])
{
    int height = 0, width = 0;
    int* pHeight, *pWidth;
    pHeight = &height;
    pWidth = &width;
    FILE* image;
    Pixel** newImg;
    Pixel ** filteredImg;
    image = fopen(argv[1],"r");

    newImg = get_image(image,newImg,pHeight,pWidth);
    image = fopen(argv[1],"r");
    filteredImg = get_image(image, filteredImg, pHeight, pWidth);

    printf("%i %i\n",height,width);

    filteredImg = applyFilterTresholding(filteredImg, newImg,height,width);
    printf("name: 'new_imppm'\n");
    save_image("new_img.ppm",filteredImg,height,width);
    printf("%i %i %i\n",filteredImg[5][5].r,filteredImg[5][5].g,filteredImg[5][5].b);
    return 0;
}
