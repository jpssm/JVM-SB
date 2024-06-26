/**
 * func_test
 */
public class func_test {

    public static void main(String[] args) {
        int i1 = 1;
        int i2 = 2;
        int i3 = 3;
        
        int result = function(i1,i2,i3);
        System.err.print("\n\n\n\n\n\nRESULLLLLLLTTTTTTTTTTTTTTTT: ");
        System.err.println(result);
    }

    public static int function(int arg1, int arg2, int arg3){
        return arg1+arg2+arg3;
    }
}