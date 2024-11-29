package operator_dashboard.controller;

import operator_dashboard.communication.SerialCommChannel;
import operator_dashboard.view.OperatorDashboardSceneController;

public class OperatorDashboardControllerImpl implements OperatorDashboardController {

    private static final String PORT = "COM3";
    private static final int RATE = 115200;
    private static final long REBOOTING_TIME = 10000;

    private final OperatorDashboardSceneController view;
    private final SerialCommChannel channel;

    private boolean start = true;
    private float containerIntensity;
    private float wasteLevel;

    public OperatorDashboardControllerImpl(OperatorDashboardSceneController view) throws Exception {
        this.view = view;
        this.channel = new SerialCommChannel(PORT, RATE, this);

        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(REBOOTING_TIME);
        System.out.println("Ready.");
    }

    @Override
    public void receiveMessage(String message) {
        if (message.startsWith("temperature: ")) {
            this.getTemperature(message);
        } else if (message.startsWith("distance: ")) {
            if (start){
                this.start = false;
                this.containerIntensity = this.getDistance(message);
            } else {
                this.wasteLevel = this.getDistance(message);
            }
        } else {
            switch (message) {
                case "READY":
                    this.view.setEmptyButtonState(true);
                    this.view.setEmptyButtonState(true);
                    this.view.updateStatus("Ready for receive waste");
                    break;

                case "SPILLING":
                    this.view.fillContainer(this.wasteLevel, this.containerIntensity);
                    break;

                case "ALARM":
                    this.view.setRestoreButtonState(false);
                    this.view.updateStatus("Restore the system");
                    break;

                case "FULL":
                    this.view.setEmptyButtonState(false);
                    this.view.updateStatus("Empty the container");
                    break;

                default:
                    break;
            }
        }
    }

    @Override
    public void sendMessage() {
        System.out.println("Maintenance done!");
        this.channel.sendMsg("Maintenance done!");
    }

    private void getTemperature(String message) {
        final String[] data = message.split(": ");
        final float temperature = Float.parseFloat(data[1]);
        this.view.updateTemperature(temperature);
    }

    private float getDistance(String message) {
        final String[] data = message.split(": ");
        return Float.parseFloat(data[1]);
    }
}
