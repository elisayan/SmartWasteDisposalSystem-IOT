package operator_dashboard.controller;

import operator_dashboard.communication.SerialCommChannel;
import operator_dashboard.view.OperatorDashboardSceneController;
import operator_dashboard.view.OperatorDashboardView;

public class OperatorDashboardControllerImpl implements OperatorDashboardController {

    private static final String PORT = "COM3";
    private static final int RATE = 9600;
    private static final long REBOOTING_TIME = 4000;

    private final OperatorDashboardSceneController view;
    private final SerialCommChannel channel;

    public OperatorDashboardControllerImpl(OperatorDashboardSceneController view) throws Exception {
        this.view = view;
        this.channel = new SerialCommChannel(PORT, RATE, this);

        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(REBOOTING_TIME);
        System.out.println("Ready.");
    }

    @Override
    public void receiveMessage(String message) {
        switch (message) {
            case "SPILLING":
                this.view.fillContainer();
                break;

            case "ALARM":
                this.view.enableRestoreButton();
                this.view.updateStatus("");
                break;

            case "MAINTENANCE":
                this.view.enableEmptyButton();
                this.view.updateStatus("");
                break;

            default:
                break;
        }
    }

    @Override
    public void sendMessage() {
        this.channel.sendMsg("Maintenance done!");
    }

    private void getTemperature(String message) {
        final String[] data = message.split(": ");
        final float temperature = Float.parseFloat(data[1]);
        this.view.updateTemperature(temperature);
    }
}
