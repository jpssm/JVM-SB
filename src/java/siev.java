public class siev {
    public static void main(String[] args) {
        final int max = 100000;
        boolean isPrime;
        for (int n  = 5; n < max; n++){
            isPrime = true;
            for (int div = 2; div < n; div++){
                if (n%div == 0){
                    isPrime = false;
                    break;
                }
            }
            if (isPrime){
                System.out.print(n);
                System.out.println(" is Prime");
            }
        }
    }
}
