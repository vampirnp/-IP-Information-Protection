import java.math.BigInteger;
import java.util.List;
public class Main {
    public static void main(String[] args) {
        BigInteger prime = PrimeGenerator.generatePrime(64, 5);//генерирем случайное n-битное число p
        System.out.println("Сгенерированное простое число: " + prime);

        BigInteger p = new BigInteger("41");
        List<BigInteger> roots = PrimitiveRootFinder.findPrimitiveRoots(p);
        System.out.println("Первые 100 первообразных корней модуля 41: " + roots);

        BigInteger[] keys = DiffieHellman.keyExchange(64, 5);
        BigInteger kA = keys[0];
        BigInteger kB = keys[1];

        System.out.println("Общий ключ A: " + kA);
        System.out.println("Общий ключ B: " + kB);
        System.out.println("Ключи совпадают: " + kA.equals(kB));
    }
}