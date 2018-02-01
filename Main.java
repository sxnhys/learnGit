import java.util.Scanner;
import java.math.*;

public class Main {
    public static void main(String[] args) {
        Scanner cin = new Scanner(System.in);
/*        int GOTO = 1;
        System.out.println(GOTO);*/
/*        int i = 3;
        System.out.println(i++ + i++ + --i);*/
        BigInteger n;
        while(cin.hasNext()) {
            n = cin.nextBigInteger();
            BigInteger zero = BigInteger.ZERO;
            BigInteger one = BigInteger.ONE;
            BigInteger two = one.add(one);
            BigInteger three = two.add(one);
            BigInteger five = two.add(three);

            if(n.remainder(two).equals(zero) || n.remainder(three).equals(zero) || n.remainder(five).equals(zero))
                System.out.println("YES");
            else
                System.out.println("NO");
        }
    }
}
