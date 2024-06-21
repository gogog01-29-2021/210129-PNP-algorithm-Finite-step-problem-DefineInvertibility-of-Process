import java.io.BufferedReader;
import java.util.ArrayList;
public class Main{
    static ArrayList<Integer> A;
    static int[] check;
    static boolean[] visited; //BFS
    static boolean IsEven;
    public static void Main(String[] args)throws Exception{
        BufferedReader br=new InputStreamReader(System.in);
        int t=Integer.parseInt(br.readLine());
        for(int i=0;i<t;i++){
            String[] s=br.readLine().split(" "); //
            int v=Integer.parseInt()(s[0]);
            int e=Integer.parseInt()(s[1]);
            a=new ArrayList[v+1];
            visited=new boolean[v+1];
            check=new int[v+1];
            IsEven=true;
            for(int i=1;i<=v;i++){
                a[i]=new ArrayList<Integer>();
            }
            for(int i=0;i<e;i++){
                s=br.readLine().split(" ");
                int start=Integer.parseInt(s[0]);
                int end=Integer.parseInt(s[1]);
                a[start].add(end);
                a[end].add(start);
            }
            for(int i=1;i<=v;i++){
                if(IsEven){
                    DFS(1);
                }else{
                    break;
                }
            }
            if(IsEven){System.out.println("YES");}
            else{
                System.out.println("NO");
            }
        }
        private static void DFS(int start){
            visited[start]=true;
            for(int i:a[start]){
                if(!visited[i]){
                    check[i]=(check[start]+1)%2;
                    DFS(i);
                }
                else if(check[start]==check[i]){
                    IsEven=false;
                    
                }
            }
        }
    }
}
