#include <stdio.h>
#include <complex>
#define  MAX  (1<<17)

std::complex<double> ca[MAX], cb[MAX];
void fft(std::complex<double> a[], int n, bool inv)
{
  int i, j, k, bit;
  for(i=1,j=0;i<n;i++) 
  {
    for(bit=n>>1;!((j^=bit)&bit);bit>>=1);
    if(i<j) swap(a[i], a[j]);
  }
  for(i=1;i<n;i<<=1) 
  {
    double x = (inv ? 1 : -1) * M_PI / i;
    std::complex<double> w={cos(x),sin(x)}, th, tmp;
    for(j=0;j<n;j+=i<<1) for(k=0,th=1;k<i;k++)
    {
      tmp = a[i+j+k]*th;
      a[i+j+k] = a[j+k]-tmp;
      a[j+k] += tmp;
      th *= w;
    }
  }
  if(inv) for(i=0;i<n;i++) a[i]/=n;
}

int main(){
    int n;
    int []a,[]b;
    scanf("%d",n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
    }
    for(int i=0;i<n;i++){
        scanf("%d",&b[i]);
    }
    
    
}