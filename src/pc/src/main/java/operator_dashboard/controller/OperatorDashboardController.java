package operator_dashboard.controller;

public interface OperatorDashboardController {

    void receiveMessage(String message);

    void sendDoneMessage();

    void sendEmptyMessage();
}
