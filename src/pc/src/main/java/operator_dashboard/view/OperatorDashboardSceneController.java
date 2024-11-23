package src.main.java.operator_dashboard.view;

import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;

public class OperatorDashboardSceneController {

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

    @FXML
    void initialize() {
        fillingPercentageLabel.setText("");
        restoreButton.setDisable(true);
        emptyButton.setDisable(true);
        wasteProgress.setProgress(0);
    }

    @FXML
    void emptyClicked() throws InterruptedException {
        for (int i = 0; i < 10; i++) {
            wasteProgress.setProgress((double) i /20);
            fillingPercentageLabel.setText(String.format("%d%%", (int) (wasteProgress.getProgress() * 100)));
            Thread.sleep(1000);
        }
    }

    @FXML
    void restoreClicked() {
        wasteProgress.setProgress(0);
    }

}
