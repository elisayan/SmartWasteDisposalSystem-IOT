package operator_dashboard.view;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.util.Objects;

public class OperatorDashboardView extends Application {

    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(Objects.requireNonNull(ClassLoader.getSystemResource("layouts/operator_dashboard_scene.fxml")));
        //Parent root = FXMLLoader.load(ClassLoader.getSystemResource("layouts/operator_dashboard_scene.fxml"));
        Scene scene = new Scene(root);

        stage.setTitle("Smart Waste Disposal System - Operator Dashboard");
        stage.setScene(scene);
        stage.setWidth(650);
        stage.setHeight(500);
        stage.show();
    }
}
