import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

public class PrimitiveRootFinder {
    // Найти первые 100 первообразных корней по модулю p
    public static List<BigInteger> findPrimitiveRoots(BigInteger p) {
        List<BigInteger> roots = new ArrayList<>();
        BigInteger phi = p.subtract(BigInteger.ONE);
        List<BigInteger> factors = factorize(phi); // Факторизация phi(p)

        for (BigInteger g = BigInteger.TWO; g.compareTo(p) < 0; g = g.add(BigInteger.ONE)) {
            boolean isRoot = true;
            for (BigInteger factor : factors) {
                BigInteger exponent = phi.divide(factor);
                if (g.modPow(exponent, p).equals(BigInteger.ONE)) {
                    isRoot = false;
                    break;
                }
            }
            if (isRoot) {
                roots.add(g);
                if (roots.size() >= 100) break;
            }
        }
        return roots;
    }

    // Факторизация числа (упрощённая версия)
    private static List<BigInteger> factorize(BigInteger n) {
        List<BigInteger> factors = new ArrayList<>();
        for (BigInteger i = BigInteger.TWO; i.multiply(i).compareTo(n) <= 0; i = i.add(BigInteger.ONE)) {
            while (n.mod(i).equals(BigInteger.ZERO)) {
                factors.add(i);
                n = n.divide(i);
            }
        }
        if (n.compareTo(BigInteger.ONE) > 0) factors.add(n);
        return factors;
    }

}