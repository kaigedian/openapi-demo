package freemud;

import java.beans.BeanInfo;
import java.beans.Introspector;
import java.beans.PropertyDescriptor;
import java.lang.reflect.Method;
import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang3.StringUtils;
import org.springframework.util.CollectionUtils;

public class MapBeanConvertUtil {
	public final static char SIGN = '&';

	/**
     * Bean --> Map
     *
     * @param obj
     * @return
     */
    public static Map<String, Object> transBean2Map(Object obj) {

        if (obj == null) {
            return null;
        }
        Map<String, Object> map = new HashMap<String, Object>();
        try {
            BeanInfo beanInfo = Introspector.getBeanInfo(obj.getClass());
            PropertyDescriptor[] propertyDescriptors = beanInfo.getPropertyDescriptors();
            for (PropertyDescriptor property : propertyDescriptors) {
                String key = property.getName();
                // 过滤class属性
                if (!"class".equals(key)) {
                    // 得到property对应的getter方法
                    Method getter = property.getReadMethod();
                    Object value = getter.invoke(obj);
                    map.put(key, value);
                }
            }
        } catch (Exception e) {
            System.out.println("transBean2Map Error " + e);
        }
        return map;
    }

    /**
     * 按照ASCII 排序
     * @param obj 排序类
     * @param sign 拼接字符
     * @param containSymbols 是否拼接 =
     * @return
     */
    public static String sortObjWithoutSign(Object obj, char sign, boolean containSymbols) {
        Map<String, Object> stringObjectMap = transBean2Map(obj);
        return sortMapWithoutSign(stringObjectMap, sign, containSymbols);
    }
    /**
     * 按照ASCII 排序
     * @param obj 排序类
     * @param sign 拼接字符
     * @return
     */
    public static String sortObjWithoutSign(Object obj, char sign) {
        Map<String, Object> stringObjectMap = transBean2Map(obj);
        return sortMapWithoutSign(stringObjectMap, sign, true);
    }

    /**
     * 按照ASCII 排序
     * @param obj 排序类
     * @return
     */
    public static String sortObjWithoutSign(Object obj) {
        Map<String, Object> stringObjectMap = transBean2Map(obj);
        return sortMapWithoutSign(stringObjectMap, SIGN, true);
    }

    public static String sortMapWithoutSign(Map<String, Object> params, char sign, boolean containSymbols) {
        if (CollectionUtils.isEmpty(params)) {
            return null;
        }
        params.remove("sign");
        String buff = "";
        try {
            List<Map.Entry<String, Object>> infoIds = new ArrayList<Map.Entry<String, Object>>(params.entrySet());
            // 对所有传入参数按照字段名的 ASCII 码从小到大排序（字典序）
            infoIds.sort(Comparator.comparing(o -> (o.getKey())));
            // 构造URL 键值对的格式
            StringBuilder buf = new StringBuilder();
            for (Map.Entry<String, Object> item : infoIds) {
                if (!StringUtils.isEmpty(item.getKey())) {
                    String key = item.getKey();
                    String val = null;
                    if (item.getValue() == null) {
                        continue;
                    } else {
                        val = String.valueOf(item.getValue());
                    }
                    buf.append(key).append(containSymbols ? "=" : "").append(val);
                    buf.append(sign);
                }

            }
            buff = buf.toString();
            if (buff.isEmpty() == false && containSymbols) {
                buff = buff.substring(0, buff.length() - 1);
            }
        } catch (Exception e) {

            return null;
        }
        return buff;
    }
	
}
