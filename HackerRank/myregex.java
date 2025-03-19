import java.io.*;
import java.util.*;

public class Solution {

    public static void main(String[] args) {
        /* Enter your code here. Read input from STDIN. Print output to STDOUT. Your class should be named Solution. */
        MyRegex myregex=new MyRegex();
        Scanner sc=new Scanner(System.in);
        while(sc.hasNext()){
            String input=sc.next();
            System.out.println(input.matches(myregex.pattern));
        }
        //if(){
            
        //}else{
            
        //}
    }
}
class MyRegex{
    String pattern =
"^((25[0-5]|2[0-4]\\d|1\\d{2}|0?\\d{1,2})\\.){3}(25[0-5]|2[0-4]\\d|1\\d{2}|0?\\d{1,2})$";
                                   
}
