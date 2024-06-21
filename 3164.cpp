int main() {
    int x1,x2,x3,x4;
    scanf("%d %d %d %d",x1,y1,x2,y2);
    for(int i=y1%2==1?y1+1:y1+2;i<=y2;i+=2){
        if(i<=x1){
            continue;
        }else{
            sum+=Math.min(i,x2)-x1;
        }
    }
    for(int j=x1%2==1?x1+1:x1+2;j<=x2;j++){
        if(i-1<=y1){
            continue;
        }
        else{
            sum+=Math.min(i-1,y2)-y1;
        }
        System.out.println(sum);
    }
    public static void main(String[] args) throws Exception{
        new main().solution();
    }
}