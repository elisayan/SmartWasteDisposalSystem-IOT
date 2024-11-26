package operator_dashboard.view;

public interface OperatorDashboardSceneController {
    void fillContainer();
    void handleMaintenance() throws Exception;
    void enableEmptyButton();
    void enableRestoreButton();
    void updateStatus(String msg);
}
