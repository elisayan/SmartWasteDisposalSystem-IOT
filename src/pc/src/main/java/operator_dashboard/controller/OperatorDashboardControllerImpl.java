package src.main.java.operator_dashboard.controller;

import src.main.java.operator_dashboard.view.OperatorDashboardView;

public class OperatorDashboardControllerImpl implements OperatorDashboardController{

    private OperatorDashboardView view;

    @Override
    public void initializeView(OperatorDashboardView view) {
        this.view = view;
    }
}
