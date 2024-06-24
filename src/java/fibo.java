public class fibo {
    public static void main(String[] args){
        int n = 2;
        int fn1 = 0;
        int fn2 = 1;
        int temp;

        while (n < 43){
            temp = fn2;
            fn2 = fn2 + fn1;
            fn1 = temp;
            System.out.print(n);
            System.out.print(": ");
            System.out.print(fn2);
            System.out.print("\n");
            n++;
        }
    }
}
