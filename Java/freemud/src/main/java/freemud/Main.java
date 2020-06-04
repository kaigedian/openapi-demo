package freemud;

import com.alibaba.fastjson.JSONObject;
import org.apache.http.Header;
import org.apache.http.HttpEntity;
import org.apache.http.client.entity.UrlEncodedFormEntity;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.entity.StringEntity;
import org.apache.http.entity.mime.MultipartEntityBuilder;
import org.apache.http.entity.mime.content.StringBody;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;

import java.util.*;

public class Main {

	public static void main(String[] args) {

	    String uri = "接口地址";

        BatchQueryRequest bqRequest = new BatchQueryRequest();

        bqRequest.setStartTimestamp(1591200000033L);
        bqRequest.setEndTimestamp(1591286399033L);
        bqRequest.setOrderClients(new Integer[]{1});
        bqRequest.setStoreId("your storeId");
        bqRequest.setOrderStatus(new Integer[]{1});
        bqRequest.setCount(10);

		PlatformBaseRequest  request = new PlatformBaseRequest();
        request.setAppId("your appId");
        request.setPartnerId("your partnerId");
        request.setRequestBody(JSONObject.toJSONString(bqRequest));
        request.setVer("1");

        String content = MapBeanConvertUtil.sortObjWithoutSign(request);


        try {

            String sign = RSASignUtil.getSign(content, "your secret key");
            request.setSign(sign);
            CloseableHttpClient client = null;
            CloseableHttpResponse response = null;
            try {
                StringEntity postingString = new StringEntity(JSONObject.toJSONString(request));

                HttpPost httpPost = new HttpPost(uri + "/order/batchQuery");
                httpPost.setEntity(postingString);

                httpPost.addHeader("Content-Type", "application/json;charset=utf-8");
                httpPost.addHeader("x-transaction-id", UUID.randomUUID().toString());
                httpPost.addHeader("Accept", "application/json;charset=utf-8");
                httpPost.addHeader("access_token", "your token");

                client = HttpClients.createDefault();
                response = client.execute(httpPost);
                HttpEntity entity = response.getEntity();
                String result = EntityUtils.toString(entity);
                System.out.println(result);
            } finally {
                if (response != null) {
                    response.close();
                }
                if (client != null) {
                    client.close();
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

    }
	
}
