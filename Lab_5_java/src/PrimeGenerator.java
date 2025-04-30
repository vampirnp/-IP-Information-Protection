import java.math.BigInteger;
import java.security.SecureRandom;


public class PrimeGenerator {
    public static final SecureRandom random = new SecureRandom();

    // Генерация n-битного простого числа с t проверками Рабина-Миллера
    public static BigInteger generatePrime(int bits, int t) {
        BigInteger prime;
        long startTime = System.currentTimeMillis();
        int iterations = 0;

        do {
            iterations++;
            prime = new BigInteger(bits, random);
            prime = prime.setBit(0); // Установка младшего бита в 1 (нечётное)
            prime = prime.setBit(bits - 1); // Установка старшего бита в 1
        } while (!isPrime(prime, t));

        long time = System.currentTimeMillis() - startTime;
        System.out.println("Сгенерировано за " + iterations + " попыток, время: " + time + " мс");
        return prime;
    }

    // Тест Рабина-Миллера
    private static boolean isPrime(BigInteger n, int t) {
        if (n.compareTo(BigInteger.ONE) <= 0) return false;
        if (n.compareTo(BigInteger.valueOf(3)) <= 0) return true;

        // Проверка делимости на малые простые числа
        for (int p : new int[]{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}) {
            if (n.mod(BigInteger.valueOf(p)).equals(BigInteger.ZERO)) {
                return n.equals(BigInteger.valueOf(p));
            }
        }

        // Разложение n-1 = d * 2^s
        BigInteger d = n.subtract(BigInteger.ONE);
        int s = 0;
        while (d.mod(BigInteger.TWO).equals(BigInteger.ZERO)) {
            d = d.divide(BigInteger.TWO);
            s++;
        }

        // Выполнить t тестов
        for (int i = 0; i < t; i++) {
            BigInteger a = randomBigInteger(n.subtract(BigInteger.TWO));
            BigInteger x = a.modPow(d, n);
            if (x.equals(BigInteger.ONE) || x.equals(n.subtract(BigInteger.ONE))) continue;

            for (int j = 0; j < s - 1; j++) {
                x = x.modPow(BigInteger.TWO, n);
                if (x.equals(BigInteger.ONE)) return false;
                if (x.equals(n.subtract(BigInteger.ONE))) break;
            }
            if (!x.equals(n.subtract(BigInteger.ONE))) return false;
        }
        return true;
    }

    private static BigInteger randomBigInteger(BigInteger max) {
        BigInteger r;
        do {
            r = new BigInteger(max.bitLength(), random);
        } while (r.compareTo(max) >= 0);
        return r;
    }
}