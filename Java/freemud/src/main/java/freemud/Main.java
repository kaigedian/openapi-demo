package freemud;

import java.util.HashMap;
import java.util.Map;

public class Main {

	public static void main(String[] args) {

		PlatformBaseRequest  request = new PlatformBaseRequest();
        request.setAppId("2038");
        request.setPartnerId("2018");
        request.setRequestBody("{\"orderCode\":\"1023987523084\",\"operator\":\"xxxx\"}");

        request.setVer("1");


        String content = MapBeanConvertUtil.sortObjWithoutSign(request);

        try {
            System.out.println(RSASignUtil.getSign(content, "your client private key"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
	
}
