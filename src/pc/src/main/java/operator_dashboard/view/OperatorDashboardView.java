package src.main.java.operator_dashboard.view;

import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.image.Image;
import javafx.stage.Screen;
import javafx.stage.Stage;
//import controller.OperatorDashboardController;

import java.io.IOException;

public class OperatorDashboardView extends Application {

    private static final String FXML_PATH = "operator_dashboard_scene.fxml";
    private Stage stage;
    //private OperatorDashboardController controller;

    @Override
    public void start(Stage stage) {
        this.stage = stage;

        // Configura la finestra principale (stage)
        this.stage.setHeight(Screen.getPrimary().getBounds().getHeight() / 2);
        this.stage.setWidth(Screen.getPrimary().getBounds().getWidth() / 2);
        this.stage.setTitle("Smart Waste Disposal System - Operator Dashboard");
        this.stage.getIcons().add(new Image("img/operatorDashboard_icon.png"));
        this.stage.setResizable(true);

        // Carica e imposta la scena principale
        try {
            FXMLLoader loader = new FXMLLoader(getClass().getResource(FXML_PATH));
            Parent root = loader.load();
//            this.controller = new OperatorDashboardController();
//            this.controller.initializeView(this); // Inizializza la vista

            this.stage.setScene(new Scene(root));
        } catch (IOException e) {
            throw new RuntimeException("Impossibile caricare la scena principale.", e);
        }

        this.stage.show();
    }
}
