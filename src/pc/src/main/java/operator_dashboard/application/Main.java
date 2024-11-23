package src.main.java.operator_dashboard.application;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.stage.Stage;

import java.util.Objects;

public class Main extends Application{

    @Override
    public void start(Stage stage) throws Exception {
        Parent root = FXMLLoader.load(Objects.requireNonNull(getClass().getResource("/operator_dashboard_scene.fxml")));
        Scene scene = new Scene(root);

        stage.setTitle("Smart Waste Disposal System");
        stage.setScene(scene);
        stage.setWidth(600);
        stage.setHeight(400);
        stage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}
