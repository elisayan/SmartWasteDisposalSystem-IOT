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
    private static final float MAX_WASTE_LIMIT = 0.05F;

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

    private final OperatorDashboardController controller;

    public OperatorDashboardSceneControllerImpl() throws Exception {
        this.controller = new OperatorDashboardControllerImpl(this);
    }

    @FXML
    void initialize() {
        this.restoreButton.setDisable(true);
        this.emptyButton.setDisable(true);
        Platform.runLater(() -> {
            this.temperatureLabel.setText("");
            this.stateLabel.setText("");
        });
        this.wasteProgress.setProgress(0);
        this.fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100)));
    }

    @FXML
    void emptyClicked() {
        this.controller.sendEmptyMessage();
        Task<Void> task = new Task<>() {
            @Override
            protected Void call() throws Exception {
                for (int i = (int) (wasteProgress.getProgress() * 10); i >= 0; i--) {
                    double progress = (double) i / 10;
                    Platform.runLater(() -> {
                        wasteProgress.setProgress(progress);
                        fillingPercentageLabel.setText(String.format("%d%%", (int) (progress * 100)));
                    });
                    Thread.sleep(EMPTY_SPEED);
                }
                handledError();
                return null;
            }
        };
        Thread thread = new Thread(task);
        thread.setDaemon(true);
        thread.start();
    }

    @FXML
    void restoreClicked() {
        this.wasteProgress.setProgress(0);
        this.fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100)));
        this.handledError();
    }

    @Override
    public void fillContainer(float wasteDistance, float containerHeight) {
        if (wasteDistance <= containerHeight) {
            float maxContainerHeight = containerHeight - MAX_WASTE_LIMIT;
            float maxWasteDistance = wasteDistance - MAX_WASTE_LIMIT;
            float fillingQuantity = (maxContainerHeight - maxWasteDistance);
            float fillingPercentage = fillingQuantity / maxContainerHeight;
            this.wasteProgress.setProgress(fillingPercentage);
            Platform.runLater(() -> this.fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100))));
        }
    }

    @Override
    public void handledError() {
        if (this.wasteProgress.getProgress() == 0) {
            this.controller.sendRestoreMessage();
            this.initialize();
        }
    }

    @Override
    public void setEmptyButtonState(boolean state) {
        this.emptyButton.setDisable(state);
    }

    @Override
    public void setRestoreButtonState(boolean state) {
        this.restoreButton.setDisable(state);
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
