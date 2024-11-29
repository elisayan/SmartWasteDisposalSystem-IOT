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

    private static final int EMPTY_SPEED = 1000;

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
    void emptyClicked() {
        Task<Void> task = new Task<>() {
            @Override
            protected Void call() throws Exception {
                //if (wasteProgress.getProgress() == 1) {
                    for (int i = (int) (wasteProgress.getProgress()*10); i >= 0; i--) {
                        double progress = (double) i / 10;
                        Platform.runLater(() -> {
                            wasteProgress.setProgress(progress);
                            fillingPercentageLabel.setText(String.format("%d%%", (int) (progress * 100)));
                        });
                        Thread.sleep(EMPTY_SPEED);
                    }
                    handledError();
                //}
                return null;
            }
        };
        Thread thread = new Thread(task);
        thread.setDaemon(true);
        thread.start();
    }

    @FXML
    void restoreClicked() throws Exception {
        this.wasteProgress.setProgress(0);
        this.fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100)));
        this.handledError();
    }

    @Override
    public void fillContainer(float wasteDistance, float containerHeight) {
        if (wasteDistance <= containerHeight){
            System.out.println("minore");
            float fillingQuantity = (containerHeight - wasteDistance);
            float fillingPercentage = fillingQuantity / containerHeight;
            this.wasteProgress.setProgress(fillingPercentage);
            Platform.runLater(() -> this.fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100))));
        } else{
            System.out.println("maggiore");
        }
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
        Platform.runLater(() -> this.stateLabel.setText(msg));
    }

    @Override
    public void updateTemperature(float temperature) {
        Platform.runLater(() -> this.temperatureLabel.setText(String.valueOf(temperature)));
    }
}
