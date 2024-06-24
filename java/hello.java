public  class hello{
    public static void main(String[] args) {
        int c = 0;

        while (c < 10){
            int i1 = 1+c;
            int i2 = 2+c;
            int i3 = i1 + i2 + 1;
            System.out.print(i1);
            System.out.print('+');
            System.out.print(i2);
            if (i3 == 3){
                System.out.print(" = ");
            }
            else System.out.print("!=");
            //System.out.print(" = ");
            System.out.print(i3);
            c++;
        }
    }
}