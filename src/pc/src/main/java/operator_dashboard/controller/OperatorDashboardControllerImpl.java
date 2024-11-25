package operator_dashboard.controller;

import operator_dashboard.communication.SerialCommChannel;
import operator_dashboard.view.OperatorDashboardView;

public class OperatorDashboardControllerImpl implements OperatorDashboardController{

    private static final String PORT = "COM3";
    private static final int RATE = 9600;
    private static final long REBOOTING_TIME = 4000;

    private OperatorDashboardView view;
    private SerialCommChannel channel;

    public OperatorDashboardControllerImpl(OperatorDashboardView view) throws Exception {
        this.view = view;
        channel = new SerialCommChannel(PORT, RATE);

        System.out.println("Waiting Arduino for rebooting...");
        Thread.sleep(REBOOTING_TIME);
        System.out.println("Ready.");
    }
}
