import java.math.BigInteger;
import java.security.SecureRandom;
import java.util.List;

public class    DiffieHellman {
    public static BigInteger[] keyExchange(int bits, int t) {
        final SecureRandom random = new SecureRandom();

        // Общие параметры
        BigInteger n = PrimeGenerator.generatePrime(bits, t); // Простое число
        List<BigInteger> roots = PrimitiveRootFinder.findPrimitiveRoots(n);
        BigInteger g = roots.isEmpty() ? BigInteger.valueOf(2) : roots.get(0); // Первообразный корень

        // Абонент A
        BigInteger xA = new BigInteger(n.bitLength() - 1, random); // Секретный ключ A
        BigInteger yA = g.modPow(xA, n); // Открытый ключ A

        // Абонент B
        BigInteger xB = new BigInteger(n.bitLength() - 1, random); // Секретный ключ B
        BigInteger yB = g.modPow(xB, n); // Открытый ключ B

        // Общий ключ
        BigInteger kA = yB.modPow(xA, n);
        BigInteger kB = yA.modPow(xB, n);
        return new BigInteger[]{kA, kB};
    }
}