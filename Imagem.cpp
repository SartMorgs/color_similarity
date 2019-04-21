#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "vector_oper.cpp"

using namespace std;

typedef unsigned int u_int;
typedef unsigned char u_char;
typedef struct pixel{
	u_int r, g, b, i;
}PIXEL;

class Imagem{
	private:
		u_int width, height, n;
		char type[2];
		PIXEL *px;
	public:

		// Componente necessários da imagem
		void setWidth(u_int w);
		u_int getWidth();
		void setHeight(u_int h);
		u_int getHeight();
		void setType(char t[]);
		char* getType();
		void setPGM(PIXEL* pgm);
		void setPPM(PIXEL* ppm);
		void setPPM(u_int R[], u_int G[], u_int B[]);
		void setImg(PIXEL* pgm, PIXEL* ppm, PIXEL* img, u_int w, u_int h);
		PIXEL* getImg();

		// Funções separar componentes RGB
	    u_int* getR();
	    u_int* getG();
	    u_int* getB();

		// Funções de leitura e escrita
		void readPGM(FILE* arq, const char* filename);
		void writePGM(FILE* arq, const char* filename);
		void readPPM(FILE* arq, const char* filename);
		void writePPM(FILE* arq, const char* filename);

		// Funções de escala cinza
		void thresholdGray(u_int th);
		void thresholdGray(u_int thlow, u_int thhigh);
		void inverseGray();
		void addGray(unsigned char value);

		// Funções de RGB
		void inverseColor();
		void addColor(unsigned char value);
		void addColor(unsigned char valueR, unsigned char valueG, unsigned char valueB);
		void rgb2Gray();
		void thresholdRGB(u_int thR, u_int thG, u_int thB);
		void thresholdRGB(u_int thRlow, u_int thRhigh, u_int thGlow, u_int thGhigh, u_int thBlow, u_int thBhigh);

		// Funções distância
		void normL1(u_int refR, u_int refG, u_int refB, u_int th);
		void normL2(u_int refR, u_int refG, u_int refB, u_int th);
		void normMahalanobis(u_int *vectorR, u_int *vectorG, u_int *vectorB, u_int n, u_int th);
		void normKneighbors(u_int *vectorR, u_int *vectorG, u_int *vectorB, u_int s, u_int numOrb, u_int th);

		void convolve(int kernel[], u_int s);

};

void Imagem::setWidth(u_int w){
	width = w;
}

u_int Imagem::getWidth(){
	return width;
}

void Imagem::setHeight(u_int h){
	height = h;
}

u_int Imagem::getHeight(){
	return height;
}

void Imagem::setType(char t[]){
	strcpy(type, t);
}

char* Imagem::getType(){
	return type;
}

void Imagem::setPGM(PIXEL* pgm){

    for(u_int k = 0; k < n; k++){
        px[k].i = pgm[k].i;
    }
}

void Imagem::setPPM(PIXEL* ppm){
    for(u_int k = 0; k < n; k++){
        px[k].r = ppm[k].r;
        px[k].g = ppm[k].g;
        px[k].b = ppm[k].b;
    }
}

void Imagem::setPPM(u_int R[], u_int G[], u_int B[]){
    for(u_int k = 0; k < n; k++){
        px[k].r = R[k];
        px[k].g = G[k];
        px[k].b = B[k];
    }
}

void Imagem::setImg(PIXEL* pgm, PIXEL* ppm, PIXEL* img, u_int w, u_int h){

}

PIXEL* Imagem::getImg(){
    return px;
}

u_int* Imagem::getR(){
    u_int *result;

    result = (u_int*) malloc(n*sizeof(u_int));

    for(u_int k = 0; k < n; k++){
        result[k] = px[k].r;
    }

    return result;
}

u_int* Imagem::getG(){
    u_int *result;

    result = (u_int*) malloc(n*sizeof(u_int));

    for(u_int k = 0; k < n; k++){
        result[k] = px[k].g;
    }

    return result;
}

u_int* Imagem::getB(){
    u_int *result;

    result = (u_int*) malloc(n*sizeof(u_int));

    for(u_int k = 0; k < n; k++){
        result[k] = px[k].b;
    }

    return result;
}

void Imagem::readPGM(FILE* arq, const char* filename){
	u_int w, h, maxsize;
	char t[2];

	arq = fopen(filename, "r");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fscanf(arq, "%s %u %u %u", &t, &w, &h, &maxsize);

		setType(t);
		width = w;
		height = h;
		n = w * h;

		px = (PIXEL*) malloc(sizeof(PIXEL)*w*h);

		for(u_int k = 0; k < n; k++){
			fscanf(arq, "%u", &px[k].i);
		}
	}

	fclose(arq);
}


void Imagem::writePGM(FILE* arq, const char* filename){
    u_int maxsize = 255;
	arq = fopen(filename, "w");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fprintf(arq, "P2\n");
		fprintf(arq, "%u %u ", width, height);
		fprintf(arq, "%u\n", maxsize);

		for(u_int k = 0; k < n; k++){
			fprintf(arq, "%u ", px[k].i);
		}
	}

	fclose(arq);
}

void Imagem::readPPM(FILE* arq, const char* filename){
	u_int w, h, maxsize;
	char t[2];

	arq = fopen(filename, "r");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fscanf(arq, "%s %u %u %u", &t, &w, &h, &maxsize);

		setType(t);
		width = w;
		height = h;
		n = w * h;


        if(px == NULL){
            px = (PIXEL*) malloc(sizeof(PIXEL)*n);
        }
        for(u_int k = 0; k < n; k++){
            fscanf(arq, "%u %u %u", &px[k].r, &px[k].g, &px[k].b);
        }


	}

	fclose(arq);
}


void Imagem::writePPM(FILE* arq, const char* filename){
    u_int maxsize = 255;
	arq = fopen(filename, "w");

	if(arq == NULL) cout<< "Erro na abertura do arquivo" << "\n";
	else{
		fprintf(arq, "P3\n");
		fprintf(arq, "%u %u ", width, height);
		fprintf(arq, "%u\n", maxsize);

		for(u_int k = 0; k < n; k++){
			fprintf(arq, "%u %u %u ", px[k].r, px[k].g, px[k].b);
		}
	}

	fclose(arq);
}

void Imagem::thresholdGray(u_int th){
	for(u_int k = 0; k < n; k++){
		if((u_int) px[k].i < th) px[k].i = 255;
		else px[k].i = 0;
	}
}

void Imagem::thresholdGray(u_int thlow, u_int thhigh){

	for(u_int k = 0; k < n; k++){
		if(((u_int) px[k].i > thlow) && ((u_int) px[k].i < thhigh)) px[k].i = 255;
		else px[k].i = 0;
	}
}

void Imagem::inverseGray(){

	for(u_int k = 0; k < n; k++){
		px[k].i = 255 - px[k].i;
	}
}

void Imagem::addGray(unsigned char value){

	for(u_int k = 0; k < n; k++){
		if((int) (px[k].i + value) > 255) px[k].i = 255;
        else px[k].i += value;
	}
}

void Imagem::inverseColor(){
	for(u_int k = 0; k < n; k++){
		px[k].r = 255 - px[k].r;
		px[k].g = 255 - px[k].g;
		px[k].b = 255 - px[k].b;
	}
}

void Imagem::addColor(unsigned char value){
	for(u_int k = 0; k < n; k++){
		if((int) (px[k].r + value) > 255) px[k].r = 255;
        else px[k].r += value;
        if((int) (px[k].g + value) > 255) px[k].g = 255;
        else px[k].g += value;
        if((int) (px[k].b + value) > 255) px[k].b = 255;
        else px[k].b += value;
	}
}

void Imagem::addColor(unsigned char valueR, unsigned char valueG, unsigned char valueB){

	for(u_int k = 0; k < n; k++){
		if((int) (px[k].r + valueR) > 255) px[k].r = 255;
        else px[k].r += valueR;

        if((int) (px[k].g + valueG) > 255) px[k].g = 255;
        else px[k].g += valueG;

        if((int) (px[k].b + valueB) > 255) px[k].b = 255;
        else px[k].b += valueB;
	}
}

void Imagem::rgb2Gray(){
	u_int value;

	for(u_int k = 0; k < n; k++){
		value = ((u_int) px[k].r + px[k].g + px[k].b) / 3;
        px[k].i = value;
	}
}

void Imagem::thresholdRGB(u_int thR, u_int thG, u_int thB){
    for(u_int k = 0; k < n; k++){
		if((u_int) px[k].r < thR) px[k].r = 255;
		else px[k].r = 0;
		if((u_int) px[k].g < thG) px[k].g = 255;
		else px[k].g = 0;
		if((u_int) px[k].b < thB) px[k].b = 255;
		else px[k].b = 0;
	}
}

void Imagem::thresholdRGB(u_int thRlow, u_int thRhigh, u_int thGlow, u_int thGhigh, u_int thBlow, u_int thBhigh){
    for(u_int k = 0; k < n; k++){
		if( ((u_int) px[k].r > thRlow) && ((u_int) px[k].r < thRhigh) &&
            ((u_int) px[k].g > thGlow) && ((u_int) px[k].g < thGhigh) &&
            ((u_int) px[k].b > thBlow) && ((u_int) px[k].b < thBhigh)){
            px[k].r = 255;
            px[k].g = 255;
            px[k].b = 255;
		}
		else{
            px[k].r = 0;
            px[k].g = 0;
            px[k].b = 0;
		}
	}
}

void Imagem::normL1(u_int refR, u_int refG, u_int refB, u_int th){
    int l1;

    for(u_int k = 0; k < n; k++){
        //index = k / width;
        l1 = abs(((int)px[k].r - (int)refR) + ((int)px[k].g - (int)refG) + ((int)px[k].b - (int)refB));
        if(l1 < th){
            px[k].r = 0;
            px[k].g = 0;
            px[k].b = 0;
        }
        else{
            px[k].r = 255;
            px[k].g = 255;
            px[k].b = 255;
        }
    }
}

void Imagem::normL2(u_int refR, u_int refG, u_int refB, u_int th){
    int l2;

    for(u_int k = 0; k < n; k++){
        //index = k / width;
        l2 = sqrt(((px[k].r - refR)*(px[k].r - refR)) + ((px[k].g - refG)*(px[k].g - refG)) + ((px[k].b - refB)*(px[k].b - refB)));
        if(l2 < th){
            px[k].r = 0;
            px[k].g = 0;
            px[k].b = 0;
        }
        else{
            px[k].r = 255;
            px[k].g = 255;
            px[k].b = 255;
        }
    }
}

void Imagem::normMahalanobis(u_int *vectorR, u_int *vectorG, u_int *vectorB, u_int tam, u_int th){
    u_int index = 0;
    double *mCovariance, *aux;
    double *mCov_inv, dist;
    double mR, mG, mB;

    mCovariance = (double*) malloc(9*sizeof(double));
    aux = (double*)malloc(width*height*3*sizeof(double));

    mR = average(vectorR, tam);
    mG = average(vectorG, tam);
    mB = average(vectorB, tam);


    //Linha 1
    mCovariance[0] = covariance(vectorR, vectorR, tam, mR, mR);
    mCovariance[1] = covariance(vectorR, vectorG, tam, mR, mG);
    mCovariance[2] = covariance(vectorR, vectorB, tam, mR, mB);
    //Linha 2
    mCovariance[3] = covariance(vectorG, vectorR, tam, mG, mR);
    mCovariance[4] = covariance(vectorG, vectorG, tam, mG, mG);
    mCovariance[5] = covariance(vectorG, vectorB, tam, mG, mB);
    //Linha 3
    mCovariance[6] = covariance(vectorB, vectorR, tam, mB, mR);
    mCovariance[7] = covariance(vectorB, vectorG, tam, mB, mG);
    mCovariance[8] = covariance(vectorB, vectorB, tam, mB, mB);

    mCov_inv = inverse(mCovariance);

    for(u_int k = 0; k < (width * height); k++){
        aux[index] = ((px[k].r - mR) * mCov_inv[0]) + ((px[k].g - mG) * mCov_inv[1]) + ((px[k].b - mB) * mCov_inv[2]);
        aux[index + 1] = ((px[k].r - mR) * mCov_inv[3]) + ((px[k].g - mG) * mCov_inv[4]) + ((px[k].b - mB) * mCov_inv[5]);
        aux[index + 2] = ((px[k].r - mR) * mCov_inv[6]) + ((px[k].g - mG) * mCov_inv[7]) + ((px[k].b - mB) * mCov_inv[8]);
        index += 3;

    }

    /*for(u_int k = 0; k < (width*height*3); k++){
        printf("%.7f ", aux[k]);
    }
    */

    index = 0;
    for(u_int k = 0; k < (width * height); k++){
        dist = sqrt((aux[index] * (px[k].r - mR)) + (aux[index + 1] * (px[k].g - mG)) + (aux[index + 2] * (px[k].b - mB)));
        //printf("%.4f\n", dist);
        index += 3;
        if(dist < (double)th){
            px[k].r = 0;
            px[k].g = 0;
            px[k].b = 0;
        }
        else{
            px[k].r = 255;
            px[k].g = 255;
            px[k].b = 255;
        }
    }
}

void Imagem::normKneighbors(u_int *vectorR, u_int *vectorG, u_int *vectorB, u_int s, u_int numOrb, u_int th){
    u_int sizeSeg;
    double mR, mG, mB;
    double de;
    PIXEL *aux;

    aux = (PIXEL*) malloc(width*height*sizeof(PIXEL));

    for(u_int k = 0; k < (width*height); k++){
        aux[k].r = px[k].r;
        aux[k].g = px[k].g;
        aux[k].b = px[k].b;
    }

    sizeSeg = s / numOrb;


    for(u_int i = 1; i <= numOrb; i++){
        mR = average(vectorR, (i*sizeSeg - sizeSeg), (i*sizeSeg));
        mG = average(vectorG, (i*sizeSeg - sizeSeg), (i*sizeSeg));
        mB = average(vectorB, (i*sizeSeg - sizeSeg), (i*sizeSeg));

        //printf("%.4f  %.4f  %.4f \n", mR, mG, mB);

        for(u_int k = 0; k < (width*height); k++){
            de = ((px[k].r - mR)*(px[k].r - mR)) + ((px[k].g - mG)*(px[k].g - mG)) + ((px[k].b - mB)*(px[k].b - mB));


            if(sqrt(de) < (double)th){
                //printf("%.2f  %.2f  %.2f\n", (px[k].r - mR), (px[k].g - mG), (px[k].b - mB));
                //printf("%.4f\n", sqrt(de));
                aux[k].r = 0;
                aux[k].g = 0;
                aux[k].b = 0;
            }
            else{
                aux[k].r = 255;
                aux[k].g = 255;
                aux[k].b = 255;
            }
        }
    }
    setPPM(aux);
}

void Imagem::convolve(int kernel[], u_int s){
    PIXEL *result;
    u_int k = 0, sumR, sumG, sumB, cnt_l = 0, cnt_c = 0, cnt_k = 0, maxR = 0, maxG = 0, maxB = 0;
    u_int *vectR, *vectG, *vectB;
    int posX, posY;

    result = (PIXEL*) malloc(n*sizeof(PIXEL));
    vectR = (u_int*) malloc(n*sizeof(u_int));
    vectG = (u_int*) malloc(n*sizeof(u_int));
    vectB = (u_int*) malloc(n*sizeof(u_int));

    for(u_int i_line = 0; i_line < width; i_line++){
        for(u_int i_column = 0; i_column < height; i_column++){
            k = i_line*height + i_column;

            // Set 0 para variáveis auxiliares
            cnt_l = 0; cnt_c = 0;
            sumR = 0; sumG = 0; sumB = 0;
            posX = 0; posY = 0;

            while(1){
                posX = (i_line - (s / 2) + cnt_l);
                posY = (i_column - (s / 2) + cnt_c);

                // trata as bordas superiores
                if(posX < 0){
                    if(posY < 0)
                        cnt_k = (width + posX) * height + (height + posY);
                    else if(posY >= height)
                        cnt_k = (width + posX) * height + (height - posY);
                    else
                        cnt_k = (width + posX) * height + posY;
                }
                // trata as bordas inferiores
                else if(posX >= width){
                    if(posY < 0)
                        cnt_k = (width - posX) * height + (height + posY);
                    else if(posY >= height)
                        cnt_k = (width - posX) * height + (height - posY);
                    else
                        cnt_k = (width - posX) * height + posY;
                }
                // trata as bordas laterais
                else{
                    if(posY < 0)
                        cnt_k = posX * height + (height + posY);
                    else if(posY >= height)
                        cnt_k = posX * height + (height - posY);
                    else
                        cnt_k = posX * height + posY;
                }
                // printf("cnt_k = %d   \n", cnt_k);
                // printf("cnt_l = %d   cnt_c = %d   ", cnt_l, cnt_c);
                if(cnt_l == (s-1) && cnt_c == (s-1)){
                    //printf("kernel i = %d   ", cnt_l*s + cnt_c);
                    sumR += kernel[cnt_l*s + cnt_c]*px[cnt_k].r;
                    sumG += kernel[cnt_l*s + cnt_c]*px[cnt_k].g;
                    sumB += kernel[cnt_l*s + cnt_c]*px[cnt_k].b;
                    break;
                }
                else{
                    //printf("kernel i = %d   ", cnt_l*s + cnt_c);
                    sumR += kernel[cnt_l*s + cnt_c]*px[cnt_k].r;
                    sumG += kernel[cnt_l*s + cnt_c]*px[cnt_k].g;
                    sumB += kernel[cnt_l*s + cnt_c]*px[cnt_k].b;
                    cnt_c++;
                }
                if(cnt_c == s){
                    cnt_l++;
                    cnt_c = 0;
                }
                //printf("\n");
            }
            result[k].r = sumR; result[k].g = sumG; result[k].b = sumB;
        }
    }

    // Normalizando os valores dos pixels entre 0 e 255
    for(u_int k = 0; k < n; k++){
        vectR[k] = result[k].r;
        vectG[k] = result[k].g;
        vectB[k] = result[k].b;
    }
    maxG = maxFind(vectG, n);
    maxR = maxFind(vectR, n);
    maxB = maxFind(vectB, n);
    vectR = parameterize(vectR, n, maxR, 255);
    vectG = parameterize(vectG, n, maxG, 255);
    vectB = parameterize(vectB, n, maxB, 255);

    setPPM(vectR, vectG, vectB);
    //printf("\n");
}

