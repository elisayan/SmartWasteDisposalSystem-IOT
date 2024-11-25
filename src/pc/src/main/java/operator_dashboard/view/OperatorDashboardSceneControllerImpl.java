package operator_dashboard.view;

import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import operator_dashboard.controller.OperatorDashboardController;
import operator_dashboard.controller.OperatorDashboardControllerImpl;

public class OperatorDashboardSceneControllerImpl extends OperatorDashboardView implements OperatorDashboardSceneController{

    @FXML
    private Button emptyButton;

    @FXML
    private Label fillingPercentageLabel;

    @FXML
    private Button restoreButton;

    @FXML
    private Label temperatureLabel;

    @FXML
    private ProgressBar wasteProgress;

    private OperatorDashboardController controller;

    @FXML
    void initialize() throws Exception {
        this.controller = new OperatorDashboardControllerImpl(this);
        //restoreButton.setDisable(true);
        //emptyButton.setDisable(true);
        wasteProgress.setProgress(0);
        fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100)));
    }

    @FXML
    void emptyClicked() {
        Task<Void> task = new Task<>() {
            @Override
            protected Void call() throws InterruptedException {
                if (wasteProgress.getProgress() == 1) {
                    for (int i = 10; i >= 0; i--) {
                        double progress = (double) i / 10;
                        Platform.runLater(() -> {
                            wasteProgress.setProgress(progress);
                            fillingPercentageLabel.setText(String.format("%d%%", (int) (progress * 100)));
                        });
                        Thread.sleep(1000);
                    }
                }
                return null;
            }
        };

        Thread thread = new Thread(task);
        thread.setDaemon(true);
        thread.start();
    }


    @FXML
    void restoreClicked() {
        wasteProgress.setProgress(0);
        fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100)));
    }



}
