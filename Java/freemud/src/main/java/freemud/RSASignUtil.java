package freemud;


import org.bouncycastle.util.encoders.Base64;
import org.springframework.util.StringUtils;
import sun.misc.BASE64Encoder;

import java.security.*;
import java.security.spec.PKCS8EncodedKeySpec;
import java.security.spec.X509EncodedKeySpec;
import java.util.HashMap;
import java.util.Map;


/**
 * All rights Reserved, Designed By www.freemud.cn
 *
 * @version V1.0
 * @Title: RSASignUtil 鏁版嵁绛惧悕宸ュ叿绫�
 * @Package com.freemud.base.exception
 * @Description: 鏁版嵁绛惧悕宸ュ叿绫�
 * @author: aiqi.gong
 * @date: 2017/5/13 09:00
 * @Copyright: 2017 www.freemud.cn Inc. All rights reserved.
 * 娉ㄦ剰锛氭湰鍐呭浠呴檺浜庝笂娴烽潪鐮佺鎶�鍐呴儴浼犻槄锛岀姝㈠娉勪互鍙婄敤浜庡叾浠栫殑鍟嗕笟鐩�
 */
public class RSASignUtil {

    /**
     * 绛惧悕绠楁硶
     */
    public static final String ALGO_RSA256 = "SHA256withRSA";

    public static final String ALGORITHM = "RSA";

    /**
     * RSA绛惧悕
     *
     * @param content          寰呯鍚嶆暟鎹�
     * @param privateKeyBase64 瀵嗛挜
     * @param encode           瀛楃闆嗙紪鐮�
     * @return 绛惧悕鍊�
     */
    public static byte[] sign(String content, byte[] privateKeyBase64, String encode) {
        try {
            PKCS8EncodedKeySpec priPKCS8 = new PKCS8EncodedKeySpec(privateKeyBase64);
            KeyFactory keyf = KeyFactory.getInstance(ALGORITHM);
            PrivateKey priKey = keyf.generatePrivate(priPKCS8);
            Signature signature = Signature.getInstance(ALGO_RSA256);
            signature.initSign(priKey);
            signature.update(content.getBytes(encode));
            return signature.sign();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    public static byte[] sign(String content, String privateKey) {
        return sign(content, Base64.decode(privateKey));
    }

    public static byte[] sign(String content, byte[] privateKey) {
        return sign(content, privateKey, "UTF-8");
    }

    /**
     * RSA楠岀鍚嶆鏌�
     *
     * @param content   寰呯鍚嶆暟鎹�
     * @param sign      绛惧悕鍊�
     * @param publicKey 鍒嗛厤缁欏紑鍙戝晢鍏挜
     * @param encode    瀛楃闆嗙紪鐮�
     * @return 甯冨皵鍊�
     */
    public static boolean doCheck(String content, String sign, byte[] publicKey, String encode) {
        if (StringUtils.isEmpty(sign)) {
            return false;
        }
        try {
            KeyFactory keyFactory = KeyFactory.getInstance(ALGORITHM);
            PublicKey pubKey = keyFactory.generatePublic(new X509EncodedKeySpec(publicKey));
            Signature signature = Signature.getInstance(ALGO_RSA256);
            signature.initVerify(pubKey);
            signature.update(content.getBytes(encode));
            return signature.verify(Base64.decode(sign));
        } catch (Exception e) {
            e.printStackTrace();
        }
        return false;
    }

    public static boolean doCheck(String content, String sign, String publicKey) {
        return doCheck(content, sign, Base64.decode(publicKey));
    }

    public static boolean doCheck(String content, String sign, byte[] publicKey) {
        return doCheck(content, sign, publicKey, "UTF-8");
    }

    private static final String PUBLIC_KEY = "RSAPublicKey";
    private static final String PRIVATE_KEY = "RSAPrivateKey";

    public static Map<String, String> createKeys(int keySize) {
        //涓篟SA绠楁硶鍒涘缓涓�涓狵eyPairGenerator瀵硅薄
        KeyPairGenerator kpg;
        try {
            kpg = KeyPairGenerator.getInstance(ALGORITHM);
        } catch (NoSuchAlgorithmException e) {
            throw new IllegalArgumentException("No such algorithm-->[" + ALGORITHM + "]");
        }

        //鍒濆鍖朘eyPairGenerator瀵硅薄,瀵嗛挜闀垮害
        kpg.initialize(keySize);
        //鐢熸垚瀵嗗寵瀵�
        KeyPair keyPair = kpg.generateKeyPair();
        //寰楀埌鍏挜
        Key publicKey = keyPair.getPublic();
        String publicKeyStr = (new BASE64Encoder()).encodeBuffer(publicKey.getEncoded());
        //寰楀埌绉侀挜
        Key privateKey = keyPair.getPrivate();
        String privateKeyStr = (new BASE64Encoder()).encodeBuffer(privateKey.getEncoded());
        Map<String, String> keyPairMap = new HashMap<String, String>(2);
        keyPairMap.put(PUBLIC_KEY, publicKeyStr);
        keyPairMap.put(PRIVATE_KEY, privateKeyStr);

        return keyPairMap;
    }

    /**
     * map瀵硅薄涓瓨鏀惧叕绉侀挜
     */
    public static Map<String, String> initKey() throws Exception {
        return createKeys(2048);
    }

    /**
     * 瀵硅繑鍥炲弬鏁拌繘琛屽姞绛�
     * @param content
     * @param privateKey
     * @return
     * @throws Exception
     */
    public static String  getSign(String content,String privateKey) throws Exception {
        return Base64.toBase64String(RSASignUtil.sign(content, privateKey));
    }


}
