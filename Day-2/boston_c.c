#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char* getfield(char* line, int num){
    for (char* tok = strtok(line, ","); tok && *tok; tok = strtok(NULL, ",\n"))
        if (!--num)return tok;
    return NULL;
}
// data storeing 
struct input {
    float crim,zn,indus,chas,nox,rm,age,dis,rad,tax,ptratio,black,lstat,medv;
};
struct output{
    float medv;
};
struct input init_zeros(){
    struct input temp;
    temp.crim    = 0;  
    temp.zn      = 0;
    temp.indus   = 0;  
    temp.chas    = 0;  
    temp.nox     = 0; 
    temp.rm      = 0;
    temp.age     = 0; 
    temp.dis     = 0; 
    temp.rad     = 0; 
    temp.tax     = 0; 
    temp.ptratio = 0;  
    temp.black   = 0;  
    temp.lstat   = 0;  
    temp.medv    = 0; 
    return temp;
}
struct input add(struct input in1,struct input in2){
    struct input temp;
    temp.crim    = in1.crim    +in2.crim;
    temp.zn      = in1.zn      +in2.zn;
    temp.indus   = in1.indus   +in2.indus;
    temp.chas    = in1.chas    +in2.chas;
    temp.nox     = in1.nox     +in2.nox;
    temp.rm      = in1.rm      +in2.rm;
    temp.age     = in1.age     +in2.age;
    temp.dis     = in1.dis     +in2.dis;
    temp.rad     = in1.rad     +in2.rad;
    temp.tax     = in1.tax     +in2.tax;
    temp.ptratio = in1.ptratio +in2.ptratio;
    temp.black   = in1.black   +in2.black;
    temp.lstat   = in1.lstat   +in2.lstat;
    temp.medv    = in1.medv;
    return temp;
}
struct input sub(struct input in1,struct input in2){
    struct input temp;
    temp.crim    = in1.crim    -in2.crim;
    temp.zn      = in1.zn      -in2.zn;
    temp.indus   = in1.indus   -in2.indus;
    temp.chas    = in1.chas    -in2.chas;
    temp.nox     = in1.nox     -in2.nox;
    temp.rm      = in1.rm      -in2.rm;
    temp.age     = in1.age     -in2.age;
    temp.dis     = in1.dis     -in2.dis;
    temp.rad     = in1.rad     -in2.rad;
    temp.tax     = in1.tax     -in2.tax;
    temp.ptratio = in1.ptratio -in2.ptratio;
    temp.black   = in1.black   -in2.black;
    temp.lstat   = in1.lstat   -in2.lstat;
    temp.medv    = in1.medv;
    return temp;
}
struct input _div(struct input in1,struct input in2){
    struct input temp;
    temp.crim    = in1.crim    /in2.crim;
    temp.zn      = in1.zn      /in2.zn;
    temp.indus   = in1.indus   /in2.indus;
    temp.chas    = in1.chas    /in2.chas;
    temp.nox     = in1.nox     /in2.nox;
    temp.rm      = in1.rm      /in2.rm;
    temp.age     = in1.age     /in2.age;
    temp.dis     = in1.dis     /in2.dis;
    temp.rad     = in1.rad     /in2.rad;
    temp.tax     = in1.tax     /in2.tax;
    temp.ptratio = in1.ptratio /in2.ptratio;
    temp.black   = in1.black   /in2.black;
    temp.lstat   = in1.lstat   /in2.lstat;
    temp.medv    = in1.medv;
    return temp;
}
struct input mean(struct input in1,int n){
    struct input temp;
    temp.crim    = in1.crim    /n;
    temp.zn      = in1.zn      /n;
    temp.indus   = in1.indus   /n;
    temp.chas    = in1.chas    /n;
    temp.nox     = in1.nox     /n;
    temp.rm      = in1.rm      /n;
    temp.age     = in1.age     /n;
    temp.dis     = in1.dis     /n;
    temp.rad     = in1.rad     /n;
    temp.tax     = in1.tax     /n;
    temp.ptratio = in1.ptratio /n;
    temp.black   = in1.black   /n;
    temp.lstat   = in1.lstat   /n;
    temp.medv    = in1.medv;
    return temp;
}
//data preprocesssing
void convert_csv_array(struct input houses[],struct output preds[],FILE* stream){
    char line[1024];
    int count=1;
    struct input sums;
    while (fgets(line, 1024, stream)){
        if(count==1){
            count++;
            continue;
        }
        houses[count].crim = atof(getfield(strdup(line), 2));
        houses[count].zn = atof(getfield(strdup(line), 3));
        houses[count].indus = atof(getfield(strdup(line), 4));
        houses[count].chas = atof(getfield(strdup(line), 5));
        houses[count].nox = atof(getfield(strdup(line), 6));
        houses[count].rm = atof(getfield(strdup(line), 7));
        houses[count].age = atof(getfield(strdup(line), 8));
        houses[count].dis = atof(getfield(strdup(line), 9));
        houses[count].rad= atof(getfield(strdup(line), 10));
        houses[count].tax = atof(getfield(strdup(line), 11));
        houses[count].ptratio = atof(getfield(strdup(line), 12));
        houses[count].black = atof(getfield(strdup(line), 13));
        houses[count].lstat = atof(getfield(strdup(line), 14));
        houses[count].medv = atof(getfield(strdup(line), 15));
        preds[count-2].medv =  houses[count].medv;
        sums=add(sums,houses[count]);
        count++;
    }
    sums=mean(sums,506);
    houses[0] = sums;
}
double normalize(double component,double avg,int n){
    return pow(component-avg,2);

}
void calculate_std(struct input houses[],int n){
    int count=2; 
    struct input std; 
    while (count<508){ 
        std.crim    += normalize(houses[count].crim ,        houses[0].crim,    n);
        std.zn      += normalize(houses[count].zn ,          houses[0].zn,      n);
        std.indus   += normalize(houses[count].indus ,       houses[0].indus,   n);
        std.chas    += normalize(houses[count].chas ,        houses[0].chas,    n);
        std.nox     += normalize(houses[count].nox ,         houses[0].nox,     n);
        std.rm      += normalize(houses[count].rm ,          houses[0].rm,      n);
        std.age     += normalize(houses[count].age ,         houses[0].age,     n);
        std.dis     += normalize(houses[count].dis ,         houses[0].dis,     n);
        std.rad     += normalize(houses[count].rad ,         houses[0].rad,     n);
        std.tax     += normalize(houses[count].tax ,         houses[0].tax,     n);
        std.ptratio += normalize(houses[count].ptratio ,     houses[0].ptratio, n);
        std.black   += normalize(houses[count].black ,       houses[0].black,   n);
        std.lstat   += normalize(houses[count].lstat ,       houses[0].lstat,   n);
        std.medv    += normalize(houses[count].medv ,        houses[0].medv,    n);
        houses[count].medv =1;
        count++;
    }
    std=mean(std,n);
    std.crim = sqrt(std.crim); 
    std.zn = sqrt(std.zn);
    std.indus = sqrt(std.indus);
    std.chas= sqrt(std.chas);
    std.nox = sqrt(std.nox);
    std.rm = sqrt(std.rm);
    std.age = sqrt(std.age);
    std.dis = sqrt(std.dis);
    std.rad = sqrt(std.rad);
    std.tax = sqrt(std.tax);
    std.ptratio = sqrt(std.ptratio); 
    std.black = sqrt(std.black); 
    std.lstat = sqrt(std.lstat); 
    std.medv = sqrt(std.medv);
    houses[1]=std;
}
void normalize_dataset(struct input houses[]){
    int count=2; 
    struct input std; 
    while (count<508){ 
        houses[count] = _div(sub(houses[count],houses[0]),houses[1]);
        count++;
    }
}
void print(struct input std,int count){
    printf("%d\t%lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n\n"
        ,  count , std.crim , std.zn , std.indus , std.chas , std.nox , std.rm \
        , std.age , std.dis , std.rad , std.tax , std.ptratio , std.black , std.lstat , std.medv);
}
// liner regression model
double hypothesis_LR(struct input house,struct input theta){
    double y_hat = 0.0;
    y_hat += theta.crim    * house.crim;
    y_hat += theta.zn      * house.zn;
    y_hat += theta.indus   * house.indus;
    y_hat += theta.chas    * house.chas;
    y_hat += theta.nox     * house.nox;
    y_hat += theta.rm      * house.rm;
    y_hat += theta.age     * house.age;
    y_hat += theta.dis     * house.dis;
    y_hat += theta.rad     * house.rad;
    y_hat += theta.tax     * house.tax;
    y_hat += theta.ptratio * house.ptratio;
    y_hat += theta.black   * house.black;
    y_hat += theta.lstat   * house.lstat;
    // printf("%lf \n",y_hat);
    return y_hat;
}
double error_LR(struct input houses[],struct output preds[] ,struct input theta){
    double error =0.0;
    for(int i=0;i<506;i++){
        double y_hat = hypothesis_LR(houses[i+2],theta);
        error += pow((preds[i].medv -y_hat),2);
    }
    return error/506;
}
struct input gradient_LR(struct input houses[],struct output preds [],struct input theta){
    int m = 506;
    int n = 14;
    struct input grad ;
    grad = init_zeros();
    for(int i=0;i<m;i++){
        double y_hat = hypothesis_LR(houses[i+2],theta);
        grad.crim    += (y_hat - preds[i].medv) * houses[i+2].crim;
        grad.zn      += (y_hat - preds[i].medv) * houses[i+2].zn;
        grad.indus   += (y_hat - preds[i].medv) * houses[i+2].indus;
        grad.chas    += (y_hat - preds[i].medv) * houses[i+2].chas;
        grad.nox     += (y_hat - preds[i].medv) * houses[i+2].nox;
        grad.rm      += (y_hat - preds[i].medv) * houses[i+2].rm;
        grad.age     += (y_hat - preds[i].medv) * houses[i+2].age;
        grad.dis     += (y_hat - preds[i].medv) * houses[i+2].dis;
        grad.rad     += (y_hat - preds[i].medv) * houses[i+2].rad;
        grad.tax     += (y_hat - preds[i].medv) * houses[i+2].tax;
        grad.ptratio += (y_hat - preds[i].medv) * houses[i+2].ptratio;
        grad.black   += (y_hat - preds[i].medv) * houses[i+2].black;
        grad.lstat   += (y_hat - preds[i].medv) * houses[i+2].lstat;
    }
    // print(mean(grad,m),987);
    return mean(grad,m);
}
struct input gradient_descent_LR(struct input houses[],struct output preds[] , float learning_rate , int max_epochs ){
    int m = 506;
    int n = 14;
    struct input theta;
    theta=init_zeros();
    for(int i=0;i<max_epochs;i++){
        double err = error_LR(houses,preds,theta);
        printf("iter:%d => error = %lf \n",i,err);
        struct input grad;
        grad = gradient_LR(houses,preds,theta);
        theta.crim    = theta.crim   - (learning_rate * grad.crim);
        theta.zn      = theta.zn     - (learning_rate * grad.zn);
        theta.indus   = theta.indus  - (learning_rate * grad.indus);
        theta.chas    = theta.chas   - (learning_rate * grad.chas);
        theta.nox     = theta.nox    - (learning_rate * grad.nox);
        theta.rm      = theta.rm     - (learning_rate * grad.rm);
        theta.age     = theta.age    - (learning_rate * grad.age);
        theta.dis     = theta.dis    - (learning_rate * grad.dis);
        theta.rad     = theta.rad    - (learning_rate * grad.rad);
        theta.tax     = theta.tax    - (learning_rate * grad.tax);
        theta.ptratio = theta.ptratio- (learning_rate * grad.ptratio);
        theta.black   = theta.black  - (learning_rate * grad.black);
        theta.lstat   = theta.lstat  - (learning_rate * grad.lstat);
        print(theta,i);
    }
    
    return theta;
}
void r2_score(struct input houses[],struct output preds[],struct input theta){
    struct output expected[506];
    double sum=0.0;
    double num = 0.0;
    for(int i=0;i<506;i++){
        double pred = hypothesis_LR(houses[i+2],theta);
        sum+=pred;
        num+=pow((preds[i].medv-pred),2);
        expected[i].medv = pred;
    }
    double y_mean = sum/506;
    double denom = 0.0;
    for(int i=0;i<506;i++){
        denom+=pow((preds[i].medv-y_mean),2);
    }
    double score =(1-num/denom);
    printf("score :::%lf",score*100);
}
int main()
{
    FILE* stream = fopen("/home/sathwik/Storage/100DaysOfCode/DATASETS/Linear Regression/Boston.csv","r");
    struct input houses[508];
    struct output preds[506];
    convert_csv_array(houses,preds,stream);
    calculate_std(houses,508);
    normalize_dataset(houses);
    for(int i=0;i<5;i++){
        int count=i;
        print(houses[count],count);
    }
    struct input theta1;
    theta1 =  gradient_descent_LR(houses,preds,0.1,100);
    r2_score(houses,preds,theta1);
}