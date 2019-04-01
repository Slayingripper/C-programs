#include<stdio.h> // include library studio.h



int drake_equation(double R, double fp, int ne, double fl, double fi, double fc, int L)
{
	int N = R*fp*ne*fl*fi*fc*L;   //define the equation we are going to use
	return N;												//return N

}

int main(int argc, char const *argv[])
{
	double R, fp, fl, fi, fc; //declare variables R,fp,fl,fi,fc
unsigned	int ne, L;

	R=1.0;
	fp= 0.2;
	ne=1;
	fl=1.0;
	fi=1.0;
	fc=0.1;
	L=1000;
	//print out SET 1
	printf("N=%.1d R*=%.1lf fp=%.1lf ne=%d fl=%.1lf fi=%.1lf fc=%.1lf L=%d\n",drake_equation(R,fp,ne,fl,fi,fc,L), R, fp, ne, fl, fi, fc, L);

	R=1.0;
	fp= 0.5;
	ne=5;
	fl=1.0;
	fi=1.0;
	fc=0.2;
	L=1000000000;
	//print out SET 2

	printf("N=%.1d R*=%.1lf fp=%.1lf ne=%d fl=%.1lf fi=%.1lf fc=%.1lf L=%d\n",drake_equation(R,fp,ne,fl,fi,fc,L), R, fp, ne, fl, fi, fc, L);
	R=1.5;
	fp= 1.0;
	ne=3;
	fl=1.0;
	fi=0.0001;
	fc=0.001;
	L=304;
	//print out SET 3

	printf("N=%1d R*=%.1lf fp=%.1lf ne=%d fl=%.1lf fi=%.1lf fc=%.1lf L=%d\n",drake_equation(R,fp,ne,fl,fi,fc,L), R, fp, ne, fl, fi, fc, L);

	R=3.0;
	fp= 1.0;
	ne=5;
	fl=1.0;
	fi=1.0;
	fc=0.1;
	L=10000000;
	//print out SET 4
	printf("N=%.d R*=%.1lf fp=%.1lf ne=%d fl=%.1lf fi=%.1lf fc=%.1lf L=%d\n",drake_equation(R,fp,ne,fl,fi,fc,L), R, fp, ne, fl, fi, fc, L);
	return 0;
}
