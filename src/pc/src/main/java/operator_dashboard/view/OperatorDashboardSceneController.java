package operator_dashboard.view;

public interface OperatorDashboardSceneController {
    void fillContainer(float wasteLevel, float containerIntensity);

    void handledError() throws Exception;

    void enableEmptyButton();

    void enableRestoreButton();

    void updateStatus(String msg);

    void updateTemperature(float temperature);
}
