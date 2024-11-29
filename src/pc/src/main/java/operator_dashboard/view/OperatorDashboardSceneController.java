package operator_dashboard.view;

public interface OperatorDashboardSceneController {
    void fillContainer(float wasteLevel, float containerIntensity);

    void handledError() throws Exception;

    void setEmptyButtonState(boolean state);

    void setRestoreButtonState(boolean state);

    void updateStatus(String msg);

    void updateTemperature(float temperature);
}
