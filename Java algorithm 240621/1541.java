public class Main{
    public static void main(String[] args) {
        Scanner sc=new Scanner(System.in);
        static int answer=0;
        //int[] a=sc.nextInt();
        String example=sc.nextLine();
        String[] str=example.split("-");
        for(int i=0;i<str.length();i++){
            int temp=mySum(str[i]); //
            if(i==0)answer+=temp;
            else answer-=temp;
        }
        System.out.println(answer);
        
        
        
        
    }
    private static int mySum(String a) {
        int sum=0;
        String[] str=example.split("[+]");
        for(int i=0;i<temp.length;i++){
            sum+=Integer.parseInt(temp[i]);
        }
        return sum;
    }
}