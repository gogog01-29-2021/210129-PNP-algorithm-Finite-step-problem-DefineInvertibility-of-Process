import java.util.HashMap;
import java.util.Scanner;

public class Main{
    public static void main(String[] args){
        Scanner sc=new Scanner(System.in);
        HashMap<Character,Integer> Hashmap_a=new HashMap<>();
        String a=sc.nextLine();
        for(int i=0;i<a.length();i++){
            Hashmap_a.put(a.charAt(i),1);
            Hashmap_a.getOrDefault(i);
        }

        System.out.println(Hashmap_a);
    }
}
