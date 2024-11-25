package operator_dashboard.controller;

import operator_dashboard.communication.SerialCommChannel;
import operator_dashboard.view.OperatorDashboardView;

public class OperatorDashboardControllerImpl implements OperatorDashboardController{

    private OperatorDashboardView view;
    private SerialCommChannel channel;

    private OperatorDashboardControllerImpl(String port, OperatorDashboardView view) throws Exception {
        this.view = view;
        channel = new SerialCommChannel(port, 9600);


    }
}
