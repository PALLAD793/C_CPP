#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double szereg_T(double x, double e)
{
    int n=1;
    double s=0, eps=1, il, a, logarytm=0;
    if(x>0.5) il = (x-1)/x; /* obliczanie ilorazu (x-1)/x*/
    else il=(1/x -1) * x;
    do
    {
        s += pow(il, n)/n; /*obliczanie sumy wyrazów od 1 do n*/
        if(x<0.5) eps = -(s + log(x));
        else if(x>0.5) eps =log(x) -s;
        if(n==2 || n==3 || n==4 || n%5==0)
        {
            printf("Dla N rownego %d przyblizenie wynosi %e \n", n, eps);
        }

        if(x<1) logarytm += pow(-1, n+1) * pow(x-1, n) /n;
        else if(x>1) logarytm += - pow(-1, n+1) * pow(1/x - 1, n) /n;
        else logarytm = 0;
        n++;
    } while(eps>e); /*sprawdzanie czy epsilon spe³nia zadane kryterium*/

    a = log(x);
    printf("\nWartosc logarytmu z liczby %f przy uzyciu wbudowanej funkcji wynosi %.10f \n", x, a);
    printf("Wartosc logarytmu z liczby %f przy uzyciu szeregu Taylora wynosi %.10f\n", x, logarytm);
    printf("Wartosc paremetru N dla szukanego epsilona wynosi %d, a epsilon jest rowny %e", n-1, eps);
    return 0;
}

int main(int argc, char **argv)
{
    double x, epsilon;
    if(argc !=3)
    {
        puts("Zle dane");
        return 0;
    }
    x = atof(argv[1]);
    epsilon = atof(argv[2]);
    if(x <= 0 || x>1 || epsilon <= 0 || epsilon > 1) /*wczytywanie i sprawdzanie danych - czy liczby i czy x wiêkszy od 0*/
    {
        puts("Zle dane");
        return 0;
    }

    szereg_T(x, epsilon);
    printf("\n");
    return 0;
}
