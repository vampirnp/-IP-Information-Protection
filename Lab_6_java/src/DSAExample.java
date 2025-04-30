import java.security.*;
import java.util.Base64;

public class DSAExample {
    public static void main(String[] args) throws Exception {
        // Генерация ключей
        KeyPairGenerator keyGen = KeyPairGenerator.getInstance("DSA");
        keyGen.initialize(2048); // Размер ключа
        KeyPair keyPair = keyGen.generateKeyPair();
        PrivateKey privateKey = keyPair.getPrivate();
        PublicKey publicKey = keyPair.getPublic();

        // Сообщение для подписи
        String message = "MY Digital Signature!,715";
        byte[] messageBytes = message.getBytes();

        // Генерация подписи
        Signature dsa = Signature.getInstance("SHA256withDSA");
        dsa.initSign(privateKey);
        dsa.update(messageBytes);
        byte[] signature = dsa.sign();
        System.out.println("Подпись: " + Base64.getEncoder().encodeToString(signature));

        // Верификация подписи
        Signature verifier = Signature.getInstance("SHA256withDSA");
        verifier.initVerify(publicKey);
        verifier.update(messageBytes);
        boolean isValid = verifier.verify(signature);
        System.out.println("Подпись верна: " + isValid);
        System.out.println("Public Key: " + publicKey);
        System.out.println("Is valid: " + isValid);
    }
}