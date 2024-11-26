package operator_dashboard.controller;

import operator_dashboard.communication.SerialCommChannel;
import operator_dashboard.view.OperatorDashboardSceneController;
import operator_dashboard.view.OperatorDashboardView;

public class OperatorDashboardControllerImpl implements OperatorDashboardController{

    private static final String PORT = "COM3";
    private static final int RATE = 9600;
    private static final long REBOOTING_TIME = 4000;

    private OperatorDashboardSceneController view;
    private SerialCommChannel channel;

    public OperatorDashboardControllerImpl(OperatorDashboardSceneController view) throws Exception {
        this.view = view;
        this.channel = new SerialCommChannel(PORT, RATE);

        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(REBOOTING_TIME);
        System.out.println("Ready.");
    }

    @Override
    public void receiveMessage(String message) {
        switch (message){
            case "ALARM":
                this.view.updateStatus("");
                break;

            case "MAINTENANCE":
                break;

            default:
                break;
        }
    }

    @Override
    public void sendMessage() {
        this.channel.sendMsg("Maintenance done!");
    }
}
