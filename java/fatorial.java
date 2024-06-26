// Source code is decompiled from a .class file using FernFlower decompiler.
public class fatorial {
    public fatorial() {
    }
 
    public static void main(String[] var0) {
       System.out.println(fat(12));
    }
 
    public static int fat(int var0) {
       return var0 == 0 ? 1 : var0 * fat(var0 - 1);
    }
 }
 