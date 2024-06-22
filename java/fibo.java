public class fibo {
    public static void main(String[] args){
        int n = 91;
        long fn1 = 0;
        long fn2 = 1;
        long temp;

        while (n > 0){
            temp = fn2;
            fn2 = fn2 + fn1;
            fn1 = temp;
            System.out.print(92-n);
            System.out.print(": ");
            System.out.println(fn2);
            n--;
        }
    }
}
