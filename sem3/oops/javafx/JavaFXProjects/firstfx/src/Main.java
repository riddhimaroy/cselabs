import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import java.util.*;

public class Main extends Application {
    private Farmer currentFarmer;
    private Map<String, Farmer> farmerDatabase = new HashMap<>();

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        primaryStage.setTitle("Cattle Management System");

        // Farmer Registration/Login
        GridPane loginPane = new GridPane();
        loginPane.setHgap(10);
        loginPane.setVgap(10);
        Label loginLabel = new Label("Farmer Login");
        TextField usernameField = new TextField();
        usernameField.setPromptText("Username");
        Button loginButton = new Button("Login/Register");

        loginPane.add(loginLabel, 0, 0);
        loginPane.add(usernameField, 0, 1);
        loginPane.add(loginButton, 0, 2);

        Scene loginScene = new Scene(loginPane, 300, 200);
        primaryStage.setScene(loginScene);
        primaryStage.show();

        loginButton.setOnAction(e -> {
            String username = usernameField.getText();
            if (!username.isEmpty()) {
                currentFarmer = farmerDatabase.getOrDefault(username, new Farmer(username));
                farmerDatabase.put(username, currentFarmer);
                showMainMenu(primaryStage);
            }
        });
    }

    // Main Menu after login
    private void showMainMenu(Stage stage) {
        GridPane mainMenuPane = new GridPane();
        mainMenuPane.setHgap(10);
        mainMenuPane.setVgap(10);

        Label welcomeLabel = new Label("Welcome, " + currentFarmer.getName());
        Button registerCattleButton = new Button("Register Cattle");
        Button viewPoliciesButton = new Button("View Insurance Policies");
        Button fileClaimButton = new Button("File Insurance Claim");
        Button auditLogsButton = new Button("View Audit Logs");

        mainMenuPane.add(welcomeLabel, 0, 0);
        mainMenuPane.add(registerCattleButton, 0, 1);
        mainMenuPane.add(viewPoliciesButton, 0, 2);
        mainMenuPane.add(fileClaimButton, 0, 3);
        mainMenuPane.add(auditLogsButton, 0, 4);

        Scene mainMenuScene = new Scene(mainMenuPane, 400, 300);
        stage.setScene(mainMenuScene);

        registerCattleButton.setOnAction(e -> showCattleRegistration(stage));
        viewPoliciesButton.setOnAction(e -> showInsurancePolicies(stage));
        fileClaimButton.setOnAction(e -> showClaimForm(stage));
        auditLogsButton.setOnAction(e -> showAuditLogs(stage));
    }

    // Cattle Registration
    private void showCattleRegistration(Stage stage) {
        GridPane cattlePane = new GridPane();
        cattlePane.setHgap(10);
        cattlePane.setVgap(10);

        Label cattleLabel = new Label("Register Cattle");
        TextField breedField = new TextField();
        breedField.setPromptText("Breed");
        TextField ageField = new TextField();
        ageField.setPromptText("Age");
        TextField weightField = new TextField();
        weightField.setPromptText("Weight");
        TextField vaccinationField = new TextField();
        vaccinationField.setPromptText("Vaccination Status");
        Button registerButton = new Button("Register Cattle");

        cattlePane.add(cattleLabel, 0, 0);
        cattlePane.add(breedField, 0, 1);
        cattlePane.add(ageField, 0, 2);
        cattlePane.add(weightField, 0, 3);
        cattlePane.add(vaccinationField, 0, 4);
        cattlePane.add(registerButton, 0, 5);

        Scene cattleScene = new Scene(cattlePane, 400, 300);
        stage.setScene(cattleScene);

        registerButton.setOnAction(e -> {
            String breed = breedField.getText();
            int age = Integer.parseInt(ageField.getText());
            double weight = Double.parseDouble(weightField.getText());
            String vaccination = vaccinationField.getText();

            Cattle cattle = new Cattle(breed, age, weight, vaccination);
            currentFarmer.registerCattle(cattle);

            showMainMenu(stage);
        });
    }

    // View Insurance Policies
    private void showInsurancePolicies(Stage stage) {
        GridPane policyPane = new GridPane();
        policyPane.setHgap(10);
        policyPane.setVgap(10);

        Label policyLabel = new Label("Available Insurance Policies");
        Label premiumLabel = new Label("Premium: " + calculatePremium());

        Button backButton = new Button("Back");
        policyPane.add(policyLabel, 0, 0);
        policyPane.add(premiumLabel, 0, 1);
        policyPane.add(backButton, 0, 2);

        Scene policyScene = new Scene(policyPane, 400, 300);
        stage.setScene(policyScene);

        backButton.setOnAction(e -> showMainMenu(stage));
    }

    // File Insurance Claim
    private void showClaimForm(Stage stage) {
        GridPane claimPane = new GridPane();
        claimPane.setHgap(10);
        claimPane.setVgap(10);

        Label claimLabel = new Label("File Insurance Claim");
        TextField reasonField = new TextField();
        reasonField.setPromptText("Reason for Claim");
        Button submitClaimButton = new Button("Submit Claim");

        claimPane.add(claimLabel, 0, 0);
        claimPane.add(reasonField, 0, 1);
        claimPane.add(submitClaimButton, 0, 2);

        Scene claimScene = new Scene(claimPane, 400, 300);
        stage.setScene(claimScene);

        submitClaimButton.setOnAction(e -> {
            String reason = reasonField.getText();
            currentFarmer.fileClaim(reason);
            showMainMenu(stage);
        });
    }

    // View Audit Logs
    private void showAuditLogs(Stage stage) {
        GridPane auditPane = new GridPane();
        auditPane.setHgap(10);
        auditPane.setVgap(10);

        Label auditLabel = new Label("Audit Logs:");
        TextArea auditLogArea = new TextArea();
        auditLogArea.setText(currentFarmer.getAuditLogs());

        Button backButton = new Button("Back");

        auditPane.add(auditLabel, 0, 0);
        auditPane.add(auditLogArea, 0, 1);
        auditPane.add(backButton, 0, 2);

        Scene auditScene = new Scene(auditPane, 400, 300);
        stage.setScene(auditScene);

        backButton.setOnAction(e -> showMainMenu(stage));
    }

    // Premium calculation simulation
    private double calculatePremium() {
        return currentFarmer.getCattleList().stream().mapToDouble(cattle -> cattle.getWeight() * 10).sum();
    }
}
