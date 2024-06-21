import java.util.Scanner;
public class Main{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int m=sc.nextInt();
        int n=sc.nextInt();
        int []a=new int[n+1];
        for(int i=1;i<n;i++){
            a[i]=i;
            }
        
        }for(int i=2;i<Math.sqrt(n);i++){
        if(a[i]==0)continue;
           for(int j=i+1;j<=n;j+=i){
               a[j]==0;
           }
        }
    for(int i=m;i<=n;i++){
        if(a[i]!=0){
            system.out.println(a[i]);
        }
    }
        
}

    
