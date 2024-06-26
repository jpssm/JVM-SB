public class siev {
    public static void main(String[] args) {
        final int max = 20000;
        int primes[] = new int[20000];
        primes[0] = 2;
        primes[1] = 3;
        primes[2] = 5;
        int i = 3;
        for (int n  = 6; n < max; n++){
            if (isPrime(n, primes, i)){
                System.out.println(n);
                primes[i] = n;
                i++;
            }
        }
    }

    public static boolean isPrime(int n, int primes[], int max_i){
        for (int i = 0; i < max_i; i++){
            if (n%primes[i] == 0){
                return false;
            }
        }
        return true;
    }
    public static boolean test(int m[][][][]){

        return true;
    }
}
