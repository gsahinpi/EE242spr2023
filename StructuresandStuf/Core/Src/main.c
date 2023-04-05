

typedef struct {
double realpart;
double imaginarypart;

} komplex ;
typedef struct
{
komplex corners[4];

}komplexRectangle;

  komplex addcomplex( komplex,komplex);

int main()
{
	int num=5;
	double imaginary,real;
	komplex komplexNumber1;
	komplex komplexNumber2;
	komplex monitor;
	double * realptr;
	double * imaginaryptr;
	komplex  komplexNumberArray [5];
	komplexRectangle firstrectangle;
	//assign the value 5+2*i to komplexNumber1
	komplexNumber1.imaginarypart=2;
	komplexNumber1.realpart=5;
	komplexNumber2=komplexNumber1;
	real=komplexNumber2.realpart;
	komplexNumber2.realpart=8;
	komplexNumber2.imaginarypart=9;
	komplex *kpoint;
   realptr=&(komplexNumber1.realpart);
   imaginaryptr=&(komplexNumber2.imaginarypart);
	for (int i=0;i<5;i++)
	{
		komplexNumberArray[i].imaginarypart=i+1;
		komplexNumberArray[i].realpart=i*2;
	}
for (int i=0;i<5;i++)
{
 firstrectangle.corners[i].imaginarypart=i+1;
 firstrectangle.corners[i].realpart=i+2;
}

monitor=addcomplex(komplexNumber2, komplexNumber1);
kpoint=&komplexNumber1;
(*kpoint).realpart=3;
(*kpoint).imaginarypart=6;
kpoint->realpart=9;//(*kpoint).realpart=9;
kpoint->imaginarypart=12;


}//main
komplex addcomplex( komplex num1,komplex num2)
{
	komplex result;
	result.realpart=num1.realpart+num2.realpart;
	result.imaginarypart=num1.imaginarypart+num2.imaginarypart;
	return result;
}//addcomplex

