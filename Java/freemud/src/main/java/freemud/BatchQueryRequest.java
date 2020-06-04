package freemud;

public class BatchQueryRequest {

    private Long startTimestamp;

    private Long endTimestamp;

    private Integer[] orderClients;

    private String storeId;

    private Integer[] orderStatus;

    private Integer count;


    public Long getStartTimestamp() {
        return startTimestamp;
    }

    public void setStartTimestamp(Long startTimestamp) {
        this.startTimestamp = startTimestamp;
    }

    public Long getEndTimestamp() {
        return endTimestamp;
    }

    public void setEndTimestamp(Long endTimestamp) {
        this.endTimestamp = endTimestamp;
    }

    public Integer[] getOrderClients() {
        return orderClients;
    }

    public void setOrderClients(Integer[] orderClients) {
        this.orderClients = orderClients;
    }

    public String getStoreId() {
        return storeId;
    }

    public void setStoreId(String storeId) {
        this.storeId = storeId;
    }

    public Integer[] getOrderStatus() {
        return orderStatus;
    }

    public void setOrderStatus(Integer[] orderStatus) {
        this.orderStatus = orderStatus;
    }

    public Integer getCount() {
        return count;
    }

    public void setCount(Integer count) {
        this.count = count;
    }
}
