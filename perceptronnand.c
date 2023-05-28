#include <stdio.h>
#include <stdlib.h>
#include<time.h>
static int perceptroncount=0;
typedef struct 
{
 int id;
 int Ninput;
 double *weights;
 double threshold;
}Perceptron;
void initializeperceptron(Perceptron *p,int size)
{
    p->id=perceptroncount;
    perceptroncount++;
p->Ninput=size;
p->weights = (double*) malloc(size * sizeof(double));
    
p->threshold=((float)(rand()%100))/100; 
for (int i=0;i<size;i++)
{
  p->weights[i]=((float)(rand()%100))/100;  
}
};//init
void verbose(Perceptron p)
{
printf("my id is %d \n", p.id);
printf("my input size is %d \n", p.Ninput);
printf("my threshold is %f \n",p.threshold);
printf("my weights are :\n"); 
for (int i=0;i<p.Ninput;i++)
{
printf("weight[%d]= %f \n",i,p.weights[i]); 
}



};//verb

double predict(Perceptron p, double * input)
{
  double sum=0.0;
  int N=p.Ninput;
  printf("predicting  \n");
  for (int i=0;i<N;i++)
  {
   printf("input=%f, weights[%d]=%f \n",input[i],i,p.weights[i]);
  sum+=p.weights[i] *input[i]; 
  }//for
  sum+=p.threshold;
  printf("sum is %f with activation %d\n",sum,sum >0 ? 1:0);
  //activation
 if (sum >= 0 )
  {
    return 1.0;
   }  else

    return 0.0;
};//predict
double study(Perceptron *p, double eta, double truevalue,double *input)//outtput is assumed to be of dim1
{
   //predict for input array of size N
 double prediction= predict(*p,input);
 double err=truevalue-prediction;
 printf("prediction\ttrueval\terr\n");
 printf("%f\t%f\t%f\n",prediction,truevalue,err);
 //update weights
 for (int i=0;i<p->Ninput;i++)
 {
  p->weights[i]+=eta*err*input[i];
 }
 //update threshold
 p->threshold+=eta*err;
 return err;
};
int main()
{ Perceptron p1;
int sz=0;
int flag=1;
srand(time(NULL));
//printf("hello enter size of the perceptron"); 
//scanf("%d",&sz );
initializeperceptron(&p1,2);//perceptron with one input
verbose(p1);
double input[]={1};
printf("predict %f",predict(p1,input));
//study for input 1
study(&p1,0.4,0,input);
verbose(p1);
//study for input 0
input[0]=0;//true is 1
study(&p1,0.4,1,input);
verbose(p1);
///////////////////////////////////
double allinputs  [4][2]={{0,0},
                         {1,0},
                         {0,1},
                         {1,1}
                         };
double truevals[]={1,1,1,0};
int count=0;
while(flag)
{count++;
 double errsum=0;
  for (int ind=0;ind<4;ind++)//index trueval sizesize
  {
  errsum+=  study(&p1,0.4,truevals[ind],allinputs[ind]);
    verbose(p1);
    
  }
  if (errsum==0)
  break;


//scanf("%d",&flag);
//if (!flag) break;

}
printf("learned to solve the problem in %d steps the perceptron is\n",count);
verbose(p1);



return 0;
}