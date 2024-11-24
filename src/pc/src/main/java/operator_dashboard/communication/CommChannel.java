package operator_dashboard.communication;

public interface CommChannel {

    void sendMsg(String msg);

    String receiveMsg() throws InterruptedException;

    boolean isMsgAvailable();
}
