package operator_dashboard.controller;

import operator_dashboard.view.OperatorDashboardView;

public class OperatorDashboardControllerImpl implements OperatorDashboardController{

    private OperatorDashboardView view;

    @Override
    public void initializeView(OperatorDashboardView view) {
        this.view = view;
    }
}
