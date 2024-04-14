#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

double norm(double **DataPoints, int i, int j, int dimensions) { /*-- calculate the ||X_i-X_j|| */
    int z;
    double result = 0;
    for (z = 0; z < dimensions; z++) {

        result += pow(DataPoints[i][z] - DataPoints[j][z], 2);
    }
    return result;
}

double **mat_multiply(double **A_mat, double **B_mat,int N){
    /* performs normal matrix multiplication from algebra*/
    int i, j, z;
    double **resultMat;
    resultMat = (double **) malloc(N * sizeof(double*));
    if(resultMat==NULL){
        printf("An Error Has Occurred");
        return NULL;
    }
    for (i = 0; i < N; i++) {
        resultMat[i] = (double *) malloc(N * sizeof(double));
        if(resultMat[i]==NULL){
            printf("An Error Has Occurred");
            return NULL;
        }
    }
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            resultMat[i][j] = 0;
            for (z = 0; z < N; z++) {
                resultMat[i][j] += A_mat[i][z] * B_mat[z][j];
            }
        }
    }
    return resultMat;
}

double **mat_multiply_plus(double **A_mat, double **B_mat,int row1,int column1 ,int column2){
    /*/ performs normal matrix multiplication from algebra*/
    int i, j, z;
    double **resultMat=NULL;
    resultMat = (double **) malloc(row1 * sizeof(double*));
    if(resultMat==NULL){
        printf("An Error Has Occurred");
        return NULL;
    }
    for (i = 0; i < row1; i++) {
        resultMat[i] = (double *) malloc(column2 * sizeof(double));
        if(resultMat[i]==NULL){
            printf("An Error Has Occurred");
            return NULL;
        }
    }
    for (i = 0; i < row1; i++) {
        for (j = 0; j < column2; j++) {
            resultMat[i][j] = 0;
            for (z = 0; z < column1; z++) {
                resultMat[i][j] += A_mat[i][z] * B_mat[z][j];
            }
        }
    }
    return resultMat;
}



/*Given matrix A return Transpose(A)/*/
double** Transpose(double** A,int N,int d){
    int i,j;
    double** res;

    res=(double **)malloc(d* sizeof(double *));
    if(res==NULL){
        printf("An Error Has Occurred");
        return NULL;
    }
    for(i=0;i<d;i++) {
        res[i] = (double *)malloc(N * sizeof(double));
        if (res[i] == NULL) {
            printf("An Error Has Occurred");
            return NULL;
        }
    }
    for(i=0;i<d;i++){
        for(j=0;j<N;j++){
            res[i][j]=A[j][i];
        }
    }
    return res;
}




double **Similarity_matrix(double **DataPoints, int PointCount, int dimensions) {
    /*func to calc and update the similarity matrix*/
    int i, j;
    double **similarity_matrix=NULL;
    similarity_matrix = (double **) malloc(PointCount * sizeof(double *));
    if(similarity_matrix==NULL){
        printf("An Error Has Occurred");
        return NULL;
    }
    for (i = 0; i < PointCount; i++) {
        similarity_matrix[i] = (double *) malloc(PointCount * sizeof(double));
        if(similarity_matrix[i]==NULL){
            printf("An Error Has Occurred");
            return NULL;
        }

    }
    for (i = 0; i < PointCount; i++) {
        for (j = i; j < PointCount; j++) {
            if (i == j)
                similarity_matrix[i][j] = 0;
            else {
                similarity_matrix[i][j] = exp(norm(DataPoints, i, j, dimensions) / (-2.0)); /*apply the formula of the norm*/
                similarity_matrix[j][i] = similarity_matrix[i][j]; /*symmetric matrix*/
            }
        }
    }
    return similarity_matrix;
}

double **DDG(double **Simi_mat, int PointCount) {
/*returns the diagonal matrix of weighted adj matrix*/
    int i,j;
    double **DDG_mat, sum;
    DDG_mat = (double **) malloc(PointCount * sizeof(double *));
    if(DDG_mat==NULL){
        printf("An Error Has Occurred");
        return NULL;
    }
    for (i = 0; i < PointCount; i++) {
        DDG_mat[i] = (double *) calloc(PointCount, sizeof(double));
        if(DDG_mat[i]==NULL){
            printf("An Error Has Occurred");
            return NULL;
        }
    }
    for (i = 0; i < PointCount; i++) {
        sum =0;
        for (j = 0; j < PointCount; j++) {
            sum += Simi_mat[i][j];
        }
        DDG_mat[i][i]=sum;
    }
    return DDG_mat;
}

double **Normal_sim(double **DDG, double **sim_mat, int PointCount){
    int i;
    double **DA, **DAD;
    for(i=0; i<PointCount; i++){
        DDG[i][i]=1.0/ sqrt(DDG[i][i]);
    }
    DA = mat_multiply(DDG,sim_mat,PointCount);
    DAD = mat_multiply(DA,DDG,PointCount);
    for(i=0; i<PointCount; i++){
        free(DA[i]);
    }
    free(DA);
    return DAD;
}

void Sizefile(char *filename, int *dimension, int *rows) {
    int tmp_dimension;
    int tmp_rows;
    FILE *f;
    char c;
    f = fopen(filename, "rt");
    tmp_dimension=0;
    tmp_rows=0;


    while ((c = fgetc(f)) != EOF) {
        if (c == ',') {
            tmp_dimension++;
        }
        if (c == '\n') {
            tmp_rows++;
        }
    }

    tmp_dimension = tmp_dimension / tmp_rows + 1;
    fclose(f);
    *dimension = tmp_dimension;
    *rows = tmp_rows;
}

void print_matrix(double **matrix, int row, int col) { /*print the matrix*/
    int i, j;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col - 1; j++) {
            printf("%.4f,", matrix[i][j]);
        }

        printf("%.4f", matrix[i][col - 1]);
        printf("\n");
    }
}


double **sym_case(double **matrix, int N, int d) {
    return Similarity_matrix(matrix,N, d);
}

double **ddg_case(double **matrix, int N, int d) {
    double **sym_matrix, **result;
    int i;
    sym_matrix = sym_case(matrix, N, d);
    result = DDG(sym_matrix, N);
    for(i=0;i<N;i++){
        free(sym_matrix[i]);
    }
    free(sym_matrix);
    return result;
}

double **norm_case(double **matrix, int N,int d) {
    double **sym_mat, **ddg_mat, **returnMat;
    int i;
    sym_mat = sym_case(matrix, N, d);
    ddg_mat = ddg_case(matrix, N,d);
    returnMat = Normal_sim(ddg_mat,sym_mat,N);
    for(i=0;i<N;i++){
        free(sym_mat[i]);
    }
    for(i=0;i<N;i++){
        free(ddg_mat[i]);
    }
    free(sym_mat);
    free(ddg_mat);
    return returnMat;
}



double **symnmf(double **DataPoints, double **init_H, int N, int d, int k){
    double eps= 1e-4;
    double Frobenius_norm;
    int max_iter=300;
    int i,j;
    int iter=0;
    int flag=1;
    double **H,**H_old,**W,**WH,**HHt,**TRIPLE_H,**trans;
    H_old=init_H;
    W= norm_case(DataPoints,N,d);
    H = (double **) malloc(N * sizeof(double*));
    if(H==NULL){
        printf("An Error Has Occurred");
        return NULL;
    }
    for (i = 0; i < N; i++) {
        H[i] = (double *) malloc(k * sizeof(double));
        if (H[i] == NULL) {
            printf("An Error Has Occurred");
            return NULL;
        }
    }
    while ((iter<max_iter)&&(flag)){
        iter++;
        Frobenius_norm=0;
        trans=Transpose(H_old,N,k);
        WH= mat_multiply_plus(W,H_old,N,N,k);
        HHt= mat_multiply_plus(H_old, trans,N,k,N);
        TRIPLE_H= mat_multiply_plus(HHt,H_old,N,N,k);

        for(i=0;i<N;i++){
            for(j=0;j<k;j++){
                H[i][j]=H_old[i][j]*(0.5+(0.5*((WH[i][j])/(TRIPLE_H[i][j]))));
            }
        }

        for(i=0;i<N;i++){
            for(j=0;j<k;j++){
                Frobenius_norm += ((H[i][j]-H_old[i][j])*(H[i][j]-H_old[i][j]));
            }
        }
        if(Frobenius_norm<eps){
            flag=0;
        }
        for(i=0;i<N;i++){
            for(j=0;j<k;j++){
                H_old[i][j]=H[i][j];
            }
        }
    }
    free(H_old);
    free(W);
    free(WH);
    free(HHt);
    free(TRIPLE_H);
    free(trans);

    return H;

}


int main(int argc, char **argv) {
    int dimensions, PointCount,i,j;
    double Value;
    char *file_name, *goal;
    FILE *file;
    double **DataPoints;
    double **result=NULL;
    if (argc != 3){
        printf("An Error Has Occurred");
        return 0;
    }
    goal = argv[1];
    if (!(strcmp(goal, "sym")==0
          || strcmp(goal, "ddg")==0
          || strcmp(goal, "norm")==0)){
        printf("An Error Has Occurred");
    }
    file_name = argv[2];
    Sizefile(file_name, &dimensions, &PointCount);
    DataPoints = malloc(sizeof(double *) * PointCount);
    if(DataPoints==NULL){
        printf("An Error Has Occurred");
        return 0;
    }
    for (i = 0; i < PointCount; i++) {
        DataPoints[i] = (double *) malloc((dimensions) * sizeof(double));
        if(DataPoints[i]==NULL){
            printf("An Error Has Occurred");
            return 0;
        }
    }

    file = fopen(file_name, "rt");
    for (i = 0; i < PointCount; i++) {
        for (j = 0; j < dimensions; j++) {
            if(fscanf(file, "%lf", &Value)==0){
                printf("An Error Has Occurred");
                return 0;
            }
            DataPoints[i][j] = (double) Value;
            fgetc(file);
        }
    }
    fclose(file);

    if (DataPoints == NULL){
        return 0;
    }
    /*we filled the data from the input file into the DataPoitns matrix*/
    /*-- need to find a way for python to execute the functions without entering the main and doing double the work
      -- main thought is to use envelope funcs*/

    if (strcmp(goal, "sym")==0){
        result= sym_case(DataPoints,PointCount,dimensions);
        print_matrix(result,PointCount,PointCount);

    }

    if (strcmp(goal, "ddg")==0){
        result= ddg_case(DataPoints,PointCount,dimensions);
        print_matrix(result,PointCount,PointCount);
    }

    if (strcmp(goal, "norm")==0){
        result= norm_case(DataPoints,PointCount,dimensions);
        print_matrix(result,PointCount,PointCount);
    }

    for(i=0; i<PointCount;i++){
        free(DataPoints[i]);
    }
    free(DataPoints);
    if (result != NULL) {
        for (i = 0; i < PointCount; i++) {
            free(result[i]);
        }
        free(result);
    }
    return 0;
}
