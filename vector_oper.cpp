#include <iostream>
#include <stdlib.h>
#include <math.h>

typedef unsigned int u_int;

double average(u_int *vec, u_int n){
    int sum = 0;
    double average;

    for(u_int k = 0; k < n; k++){
        sum += vec[k];
    }

    average = ((double)sum / (double)n);
    return average;
}

double average(u_int *vec, u_int b, u_int e){
    int sum = 0;
    double average;

    for(u_int k = b; k < e; k++){
        sum += vec[k];
    }

    average = ((double)sum / (double)(e - b));
    return average;
}

double covariance(u_int vectorX[], u_int vectorY[], u_int n, double averageX, double averageY){
    double covariance, sumCovariance = 0;

    for(u_int k = 0; k < n; k++){
        sumCovariance += ((double)vectorX[k] - averageX)*((double)vectorY[k] - averageY);
    }

    covariance = abs((double)sumCovariance) / (double)(n - 1);

    return covariance;
}

float variance(u_int vec[], u_int n, float average){
    float sum = 0.0;

    for(u_int k = 0; k < n; k++){
        sum += (((float)vec[k] - average)*((float)vec[k] - average));
    }

    return sum / n;
}

double *inverse(double matrix[]){
    double det;
    double *m_inverse;

    m_inverse = (double*) malloc(3*3*sizeof(double));

    det =   (matrix[0] * matrix[4] * matrix[8]) + (matrix[1] * matrix[5] * matrix[6]) + (matrix[2] * matrix[3] * matrix[7]) -
            ((matrix[6] * matrix[4] * matrix[2]) + (matrix[7] * matrix[5] * matrix[0]) + (matrix[8] * matrix[3] * matrix[6]));

    if(det != 0){
        m_inverse[0] = (1 / det) * ((matrix[4] * matrix[8]) - (matrix[7] * matrix[5]));
        m_inverse[1] = - ((1 / det) * ((matrix[3] * matrix[8]) - (matrix[6] * matrix[5])));
        m_inverse[2] = (1 / det) * ((matrix[3] * matrix[7]) - (matrix[6] * matrix[4]));
        m_inverse[3] = - ((1 / det) * ((matrix[1] * matrix[8]) - (matrix[7] * matrix[2])));
        m_inverse[4] = (1 / det) * ((matrix[0] * matrix[8]) - (matrix[6] * matrix[2]));
        m_inverse[5] = - ((1 / det) * ((matrix[0] * matrix[7]) - (matrix[6] * matrix[1])));
        m_inverse[6] = (1 / det) * ((matrix[1] * matrix[5]) - (matrix[4] * matrix[2]));
        m_inverse[7] = - ((1 / det) * ((matrix[0] * matrix[5]) - (matrix[3] * matrix[2])));
        m_inverse[8] = (1 / det) * ((matrix[0] * matrix[4]) - (matrix[3] * matrix[1]));
    }
    else{
        printf("DETERMINANTE 0 \n");
    }


    return m_inverse;
}
