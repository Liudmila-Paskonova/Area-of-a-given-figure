#include <getopt.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

double f1(double x); //forward declarations:
double f2(double x);
double f3(double x);
double f4(double x);
double f5(double x);
double f6(double x);
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1);
double integral(double (*f)(double), double a, double b, double eps2);
int iterations(double (*f)(double), double (*g)(double), double a, double b, double eps1);

double f4(double x){ //additional simple functions:
	return x*x+2;
}
double f5(double x){
	return -x+2;
}
double f6(double x){
	return x+8;
}
double root(double (*f)(double), double (*g)(double), double a, double b, double eps1){ //root. Chord method
	if(a>b){
		double t=a;
		a=b;
		b=t;
	}
	double c=(a*(f(b)-g(b))-b*(f(a)-g(a)))/(f(b)-g(b)-f(a)+g(a));
	double p=(f(a)-g(a)); //F'(x)
	double q=f((a+b)/2)-g((a+b)/2)-((f(a)-g(a))/2)-((f(b)-g(b))/2); //F''(x)
	if((p*q)>0){
		while((f(c)-g(c))*(f(c+eps1)-g(c+eps1))>0){
			a=c;
			c=(a*(f(b)-g(b))-b*(f(a)-g(a)))/(f(b)-g(b)-f(a)+g(a));
		}
		return c+(eps1/2);
	}
	else{
		while((f(c)-g(c))*(f(c-eps1)-g(c-eps1))>0){
			b=c;
			c=(a*(f(b)-g(b))-b*(f(a)-g(a)))/(f(b)-g(b)-f(a)+g(a));
		}
		return c-(eps1/2);
	}
}

int iterations(double (*f)(double), double (*g)(double), double a, double b, double eps1){ //iterations
	int it=0;
	if(a>b){
		double t=a;
		a=b;
		b=t;
	}
	double c=(a*(f(b)-g(b))-b*(f(a)-g(a)))/(f(b)-g(b)-f(a)+g(a));
	double p=(f(a)-g(a)); //F'(x)
	double q=f((a+b)/2)-g((a+b)/2)-((f(a)-g(a))/2)-((f(b)-g(b))/2); //F''(x)
	if((p*q)>0){
		while((f(c)-g(c))*(f(c+eps1)-g(c+eps1))>0){
			a=c;
			c=(a*(f(b)-g(b))-b*(f(a)-g(a)))/(f(b)-g(b)-f(a)+g(a));
			it+=1;
		}
	}
	else{
		while((f(c)-g(c))*(f(c-eps1)-g(c-eps1))>0){
			b=c;
			c=(a*(f(b)-g(b))-b*(f(a)-g(a)))/(f(b)-g(b)-f(a)+g(a));
			it+=1;
		}
	}
	return it;
}

double integral(double (*f)(double), double a, double b, double eps2){ //integral. Rectangle method
	int n=20;
	double h1, h2, sum1=0.0, sum2=0.0;
	h1=((b-a)/n);
	sum1=0.0;
	for(int i=0; i<n; i++){
		sum1+=f(a+(i+0.5)*h1);
	}
	sum1*=h1;
	sum2=sum1;
	double q=fabs(sum1);
	while(q>=(3*eps2)){
		sum1=sum2;
		h2=((b-a)/(2*n));
		sum2=0.0;
		for(int i=0; i<(2*n); i++){
			sum2+=f(a+(i+0.5)*h2);
		}
		sum2*=h2;
		q=fabs(sum1-sum2);
		n*=2;
	}
	n*=2;
	h2=((b-a)/(n));
	sum2=0.0;
	for(int i=0; i<(n); i++){
		sum2+=f(a+(i+0.5)*h2);
	}
	sum2*=h2;
	return sum2;
}

void *arrf[]={f1,f2,f3,f4,f5,f6}; //array of functions

static void wrong_num(int exp) { //arguments are missed
  printf("Wrong number of arguments: %d agruments expected.\n", exp);
  exit(-1);
}

int main(int argc, char **argv) {

	int NF1, NF2, rez, k, l, m; //num-s of func-s and result, iterations
	double a0, b0, c0, x0, e0, r0, area0; //a,b,c,eps,right ans, area
	int cont=0; //Checks if arguments are or not
	while (1){
	const char *short_options = "hriR:I:";
	const struct option long_options[] = { {"help", no_argument, NULL, 'h'}, {"root", no_argument, NULL, 'r'},
 {"iterations", no_argument, NULL, 'i'}, {"test-root", required_argument, NULL, 'R'}, {"test-integral", required_argument, NULL, 'I'},
  {0,0,0,0} };

	 rez=getopt_long(argc,argv,short_options, long_options, NULL); //use getopt_long

		if(rez==-1){ //end of input
			if((cont==0)&&(argc!=1)){
				printf("Incorrect command :((. Try with --/-\n");
			}
			else if(cont==0){ //No arguments
				a0=root(f1, f2, -2.0, -0.01, 0.0001);
				b0=root(f2, f3, -3.0, -1.0, 0.0001);
				c0=root(f1, f3, -5.0, -3.0, 0.0001);
				area0=integral(f1, a0, c0, 0.0001)+integral(f2, b0, a0, 0.0001)+integral(f3, c0, b0, 0.0001);
				area0=fabs(area0);
				printf("%lf\n", area0);
			}
			break;
		}
cont=1;
		switch(rez){
		case 'h':
			;//help
			printf("--help -h\n");
			printf("--root -r\n");
			printf("--iterations -i\n");
			printf("--test-root -R\n");
			printf("--test-integral -I\n");
			break;

		case 'r':
			;//root option
			a0=root(f1, f2, -0.01, -2, 0.0001);
			b0=root(f2, f3, -3, -1, 0.0001);
			c0=root(f1, f3, -5, -3, 0.0001);
			printf("f1, f2: %lf\n", a0);
			printf("f2, f3: %lf\n", b0);
			printf("f1, f3: %lf\n", c0);
			break;

		case 'i':
			;//iterations option
			k=iterations(f1, f2, -0.01, -2, 0.0001);
			l=iterations(f2, f3, -3, -1, 0.0001);
			m=iterations(f1, f3, -5, -3, 0.0001);
			printf("f1,f2: %d\n", k);
			printf("f2,f3: %d\n", l);
			printf("f1,f3: %d\n", m);
			printf("%d in total\n",k+l+m);
			break;

		case 'R':
			;//test-root option
			if(argc!= 3)
				wrong_num(1);
			sscanf(argv[2], "%d:%d:%lf:%lf:%lf:%lf", &NF1, &NF2, &a0, &b0, &e0, &r0);
			x0=root(arrf[NF1-1], arrf[NF2-1],a0, b0, e0);
			printf("%lf %lf %lf\n", x0, fabs(r0-x0), fabs((r0-x0)/r0));
			break;

		case 'I':
			;//test-integral option
			if(argc!= 3)
				wrong_num(1);
			sscanf(argv[2], "%d:%lf:%lf:%lf:%lf", &NF1, &a0, &b0, &e0, &r0);
			x0=integral(arrf[NF1-1], a0, b0, e0);
			printf("%lf %lf %lf\n", x0, fabs(r0-x0), fabs((r0-x0)/r0));
			break;

		default:
			;//No option
			printf("Incorrect command :((\n");
			break;
		}


	}

	return 0;
}
