#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char* getfield(char* line, int num){
    for (char* tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
        if (!--num)return tok;
    return NULL;
}
void convert_csv_array(float houses[306][13] ,float preds[],float means[],FILE* stream){
    char line[1024];
    int count =-1;
    while (fgets(line, 1024, stream)){
        if(count==-1){
            count++;
            continue;
        }
        for(int i=0;i<13;i++){
            float temp = atof(getfield(strdup(line), i+2));
            houses[count][i] =temp;
            means[i] +=temp; 
            if(i==13)preds[count] = atof(getfield(strdup(line), i+2));
        }
        count++;
    }
    for(int i=0;i<13;i++)means[i]/=506;
}

void calculate_std(float input[306][13] ,float means[] , float std[]){
    int count=2; 
    for(int count=0;count<306;count++){
        for(int i=0;i<13;i++){
            std[i]    += sqrt((pow(input[count][i]-means[i],2))/306);
        }
    }
    for(int count=0;count<306;count++){
        for(int i=0;i<13;i++){
            input[count][i] = (input[count][i]-means[i])/std[i];
        }
    }
}
int main()
{
    FILE* stream = fopen("/home/sathwik/Storage/100DaysOfCode/DATASETS/Linear Regression/Boston.csv","r");
    float input[508][13],output[506],means[13],std[13];
    convert_csv_array(input,output,means,stream);
    calculate_std(input,means,std);

    for(int i=0;i<5;i++){
        for(int j=0;j<13;j++){
            printf("%lf ",input[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    for(int i=0;i<13;i++)printf("%lf ",means[i]);
    printf("\n");
    for(int i=0;i<13;i++)printf("%lf ",means[i]);
    printf("\n");
}