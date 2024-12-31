import java.util.*;
public class Main{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        int n=sc.nextInt(); //newInteger();
        int a[]=new int[n];
        boolean[]occur=new boolean[2000001];
        for(int i=0;i<a.length;i++){
        a[i]=sc.nextInt();
        }
        int b=sc.nextInt();
        int cnt=0;
        for(int i=0;i<a.length;i++){
            if(b-a[i]>0 && occur[b-a[i]]){
                cnt++;
            }
            occur[a[i]]=true;
        }
        System.out.println(cnt);
    }
}
