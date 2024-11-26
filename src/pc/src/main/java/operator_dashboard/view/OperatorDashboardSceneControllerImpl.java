package operator_dashboard.view;

import javafx.application.Platform;
import javafx.concurrent.Task;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import operator_dashboard.controller.OperatorDashboardController;
import operator_dashboard.controller.OperatorDashboardControllerImpl;

public class OperatorDashboardSceneControllerImpl implements OperatorDashboardSceneController {

    @FXML
    private Button emptyButton;

    @FXML
    private Label fillingPercentageLabel;

    @FXML
    private Button restoreButton;

    @FXML
    private Label stateLabel;

    @FXML
    private Label temperatureLabel;

    @FXML
    private ProgressBar wasteProgress;

    private OperatorDashboardController controller;

    @FXML
    void initialize() throws Exception {
        this.controller = new OperatorDashboardControllerImpl(this);
        this.restoreButton.setDisable(true);
        this.emptyButton.setDisable(true);
        this.temperatureLabel.setText("");
        this.stateLabel.setText("");
        this.wasteProgress.setProgress(0);
        this.fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100)));
    }

    @FXML
    void emptyClicked() throws Exception {
        if (this.wasteProgress.getProgress() == 1) {
            animateProgress(1, 0, -0.1);
            handledError();
        }
    }

    @FXML
    void restoreClicked() throws Exception {
        this.wasteProgress.setProgress(0);
        this.fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100)));
        handledError();
    }

    @Override
    public void fillContainer() {
        //TODO: interrompere il riempimento nel momento in cui chiude la porta
        animateProgress(0, 1, 0.1);
    }

    @Override
    public void handledError() throws Exception {
        if (this.wasteProgress.getProgress() == 0) {
            this.controller.sendMessage();
            this.initialize();
        }
    }

    @Override
    public void enableEmptyButton() {
        this.emptyButton.setDisable(false);
    }

    @Override
    public void enableRestoreButton() {
        this.restoreButton.setDisable(false);
    }

    @Override
    public void updateStatus(String msg) {
        this.stateLabel.setText(msg);
    }

    @Override
    public void updateTemperature(float temperature) {
        this.temperatureLabel.setText(String.valueOf(temperature));
    }

    private void animateProgress(double start, double end, double step) {
        Task<Void> task = new Task<>() {
            @Override
            protected Void call() throws InterruptedException {
                double progress = start;
                while ((step > 0 && progress <= end) || (step < 0 && progress >= end)) {
                    double currentProgress = progress;
                    Platform.runLater(() -> {
                        wasteProgress.setProgress(currentProgress);
                        fillingPercentageLabel.setText(String.format("%d%%", (int) (currentProgress * 100)));
                    });
                    Thread.sleep(1000);
                    progress += step;
                }
                return null;
            }
        };

        Thread thread = new Thread(task);
        thread.setDaemon(true);
        thread.start();
    }

}
