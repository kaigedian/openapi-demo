package freemud;


/**
 * All rights Reserved, Designed By www.freemud.com
 *
 * @version V1.0
 * @Title:
 * @Package: cn.freemud.base.entity
 * @Descripttion:
 * @author: genyou.cui
 * @date: 2019/4/19 15:11
 * @Copyright: 2017 www.freemud.cn Inc. All rights reserved.
 * 娉ㄦ剰锛氭湰鍐呭浠呴檺浜庝笂娴烽潪鐮佺鎶�鍐呴儴浼犻槄锛岀姝㈠娉勪互鍙婄敤浜庡叾浠栫殑鍟嗕笟鐩�.
 */

public class PlatformBaseRequest {

   
    private String ver;
    
    private String partnerId;
    
    private String appId;
    
    private String requestBody;
    
    private String sign;

	public String getVer() {
		return ver;
	}

	public void setVer(String ver) {
		this.ver = ver;
	}

	public String getPartnerId() {
		return partnerId;
	}

	public void setPartnerId(String partnerId) {
		this.partnerId = partnerId;
	}

	public String getAppId() {
		return appId;
	}

	public void setAppId(String appId) {
		this.appId = appId;
	}

	public String getRequestBody() {
		return requestBody;
	}

	public void setRequestBody(String requestBody) {
		this.requestBody = requestBody;
	}

	public String getSign() {
		return sign;
	}

	public void setSign(String sign) {
		this.sign = sign;
	}

    

}
