package com.example.demo;

import javafx.application.Application;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.*;
import javafx.stage.Stage;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;

import java.time.LocalDate;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;
import java.util.concurrent.*;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.stream.Collectors;
import javafx.beans.property.*;

import java.util.concurrent.locks.ReentrantLock;

public class CattleManagementSystem extends Application {
    
    private Scene adminScene; 
    private boolean isAdmin = false;
    private static final DataManager dataManager = DataManager.getInstance();
    private Stage primaryStage;
    private Scene loginScene;
    private Scene mainScene;
    private String currentFarmerId;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        this.primaryStage = primaryStage;
        primaryStage.setTitle("Cattle Management System");

        dataManager.createAdminAccount("user", "123");

        loginScene = createLoginScene();
        primaryStage.setScene(loginScene);
        primaryStage.show();
    }

    private Scene createLoginScene() {
        VBox loginLayout = new VBox(10);
        loginLayout.setPadding(new Insets(20));
        loginLayout.setAlignment(Pos.CENTER);

        TabPane tabPane = new TabPane();
        Tab farmerLoginTab = new Tab("Farmer Login");
        Tab adminLoginTab = new Tab("Admin Login");
        Tab registerTab = new Tab("Register Farmer");

        farmerLoginTab.setClosable(false);
        adminLoginTab.setClosable(false);
        registerTab.setClosable(false);

        VBox farmerLoginContent = createFarmerLoginContent();
        farmerLoginTab.setContent(farmerLoginContent);

        VBox adminLoginContent = createAdminLoginContent();
        adminLoginTab.setContent(adminLoginContent);

        VBox registerContent = createRegisterContent();
        registerTab.setContent(registerContent);

        tabPane.getTabs().addAll(farmerLoginTab, adminLoginTab, registerTab);
        loginLayout.getChildren().add(tabPane);

        return new Scene(loginLayout, 400, 500);
    }

    private VBox createFarmerLoginContent() {
        VBox loginContent = new VBox(10);
        loginContent.setPadding(new Insets(20));
        loginContent.setAlignment(Pos.CENTER);

        TextField usernameField = new TextField();
        usernameField.setPromptText("Username");
        PasswordField passwordField = new PasswordField();
        passwordField.setPromptText("Password");
        Button loginButton = new Button("Login");
        Label messageLabel = new Label();
        messageLabel.setWrapText(true);

        loginButton.setOnAction(e -> {
            String username = usernameField.getText();
            String password = passwordField.getText();

            if (username.isEmpty() || password.isEmpty()) {
                messageLabel.setText("Please enter both username and password");
                return;
            }

            if (dataManager.authenticateFarmer(username, password)) {
                currentFarmerId = username;
                isAdmin = false;
                mainScene = createMainScene();
                primaryStage.setScene(mainScene);
                messageLabel.setText("");
                usernameField.clear();
                passwordField.clear();
            } else {
                messageLabel.setText("Invalid username or password");
            }
        });

        loginContent.getChildren().addAll(
                new Label("Farmer Login"),
                usernameField,
                passwordField,
                loginButton,
                messageLabel
        );

        return loginContent;
    }

    private VBox createAdminLoginContent() {
        VBox loginContent = new VBox(10);
        loginContent.setPadding(new Insets(20));
        loginContent.setAlignment(Pos.CENTER);

        TextField usernameField = new TextField();
        usernameField.setPromptText("Admin Username");
        PasswordField passwordField = new PasswordField();
        passwordField.setPromptText("Admin Password");
        Button loginButton = new Button("Login as Admin");
        Label messageLabel = new Label();
        messageLabel.setWrapText(true);

        loginButton.setOnAction(e -> {
            String username = usernameField.getText();
            String password = passwordField.getText();

            if (username.isEmpty() || password.isEmpty()) {
                messageLabel.setText("Please enter both username and password");
                return;
            }

            if (dataManager.authenticateAdmin(username, password)) {
                isAdmin = true;
                adminScene = createAdminScene();
                primaryStage.setScene(adminScene);
                messageLabel.setText("");
                usernameField.clear();
                passwordField.clear();
            } else {
                messageLabel.setText("Invalid admin credentials");
            }
        });

        loginContent.getChildren().addAll(
                new Label("Admin Login"),
                usernameField,
                passwordField,
                loginButton,
                messageLabel
        );

        return loginContent;
    }

    private VBox createRegisterContent() {
        VBox registerContent = new VBox(10);
        registerContent.setPadding(new Insets(20));
        registerContent.setAlignment(Pos.CENTER);

        TextField usernameField = new TextField();
        usernameField.setPromptText("Username");
        TextField nameField = new TextField();
        nameField.setPromptText("Full Name");
        TextField locationField = new TextField();
        locationField.setPromptText("Location");
        PasswordField passwordField = new PasswordField();
        passwordField.setPromptText("Password");
        PasswordField confirmPasswordField = new PasswordField();
        confirmPasswordField.setPromptText("Confirm Password");
        Button registerButton = new Button("Register");
        Label messageLabel = new Label();
        messageLabel.setWrapText(true);

        registerButton.setOnAction(e -> {
            String username = usernameField.getText();
            String name = nameField.getText();
            String location = locationField.getText();
            String password = passwordField.getText();
            String confirmPassword = confirmPasswordField.getText();

            if (username.isEmpty() || name.isEmpty() || location.isEmpty() ||
                    password.isEmpty() || confirmPassword.isEmpty()) {
                messageLabel.setText("Please fill in all fields");
                return;
            }

            if (!password.equals(confirmPassword)) {
                messageLabel.setText("Passwords do not match");
                return;
            }

            if (dataManager.usernameExists(username)) {
                messageLabel.setText("Username already exists");
                return;
            }

            if (dataManager.registerFarmer(username, name, location, password)) {
                messageLabel.setText("Registration successful! Please login.");
                usernameField.clear();
                nameField.clear();
                locationField.clear();
                passwordField.clear();
                confirmPasswordField.clear();
            } else {
                messageLabel.setText("Registration failed. Please try again.");
            }
        });

        registerContent.getChildren().addAll(
                new Label("Register New Farmer"),
                usernameField,
                nameField,
                locationField,
                passwordField,
                confirmPasswordField,
                registerButton,
                messageLabel
        );

        return registerContent;
    }

    private Scene createMainScene() {
        TabPane mainTabPane = new TabPane();
    
        Tab cattleTab = new Tab("Cattle Management");
        Tab claimsTab = new Tab("Insurance Claims");
        Tab auditTab = new Tab("Audit Log");
        Tab policiesTab = new Tab("Insurance Policies"); 
        Tab policyManagementTab = new Tab("Policy Management"); 
    
        cattleTab.setClosable(false);
        claimsTab.setClosable(false);
        auditTab.setClosable(false);
        policiesTab.setClosable(false);
        policyManagementTab.setClosable(false);
    
        cattleTab.setContent(createCattleManagementContent());
    
        claimsTab.setContent(createClaimsContent());
    
        auditTab.setContent(createAuditLogContent());
    
        policiesTab.setContent(createInsurancePoliciesContent());
    
        policyManagementTab.setContent(createPolicyManagementContent());
    
        Button logoutButton = new Button("Logout");
        logoutButton.setOnAction(e -> {
            currentFarmerId = null;
            primaryStage.setScene(loginScene);
        });
    
        VBox mainLayout = new VBox(10);
        mainLayout.setPadding(new Insets(10));
    
        mainTabPane.getTabs().addAll(cattleTab, claimsTab, auditTab, policiesTab, policyManagementTab);
        mainLayout.getChildren().addAll(logoutButton, mainTabPane);
    
        return new Scene(mainLayout, 800, 600);
    }
    
private final ObservableList<Policy> policyList = FXCollections.observableArrayList();

private VBox createInsurancePoliciesContent() {
    VBox policiesLayout = new VBox(10);
    policiesLayout.setPadding(new Insets(10));
    
    TextField breedField = new TextField();
    breedField.setPromptText("Breed");
    
    TextField ageField = new TextField();
    ageField.setPromptText("Age (years)");
    
    TextField weightField = new TextField();
    weightField.setPromptText("Weight (kg)");
    
    CheckBox vaccinatedCheckBox = new CheckBox("Vaccinated");
    
    Button addPolicyButton = new Button("Add Policy and Calculate Premium");
    Label premiumLabel = new Label();
    
    addPolicyButton.setOnAction(e -> {
        try 
        {
            String breed = breedField.getText();
            int age = Integer.parseInt(ageField.getText());
            double weight = Double.parseDouble(weightField.getText());
            boolean vaccinated = vaccinatedCheckBox.isSelected();
            
            double premium = calculatePremium(breed, age, weight, vaccinated);
            premiumLabel.setText("Calculated Premium: ₹" + premium);
            
            Policy newPolicy = new Policy(breed, age, weight, vaccinated, premium);
            policyList.add(newPolicy);
            
            breedField.clear();
            ageField.clear();
            weightField.clear();
            vaccinatedCheckBox.setSelected(false);

            dataManager.updateAL(currentFarmerId);
            
        } catch (NumberFormatException ex) {
            premiumLabel.setText("Please enter valid numbers for age and weight");
        }
    });
    
    policiesLayout.getChildren().addAll(
        new Label("Enter Policy Details:"),
        breedField, ageField, weightField, vaccinatedCheckBox,
        addPolicyButton, premiumLabel
    );
    
    return policiesLayout;
}

private VBox createPolicyManagementContent() {
    VBox policyManagementLayout = new VBox(10);
    policyManagementLayout.setPadding(new Insets(10));

    TableView<Policy> policyTable = new TableView<>(policyList);

    TableColumn<Policy, String> breedColumn = new TableColumn<>("Breed");
    breedColumn.setCellValueFactory(cellData -> cellData.getValue().breedProperty());

    TableColumn<Policy, Number> ageColumn = new TableColumn<>("Age");
    ageColumn.setCellValueFactory(cellData -> cellData.getValue().ageProperty());

    TableColumn<Policy, Number> weightColumn = new TableColumn<>("Weight");
    weightColumn.setCellValueFactory(cellData -> cellData.getValue().weightProperty());

    TableColumn<Policy, Boolean> vaccinatedColumn = new TableColumn<>("Vaccinated");
    vaccinatedColumn.setCellValueFactory(cellData -> cellData.getValue().vaccinatedProperty());

    TableColumn<Policy, Number> premiumColumn = new TableColumn<>("Premium");
    premiumColumn.setCellValueFactory(cellData -> cellData.getValue().premiumProperty());

    TableColumn<Policy, String> statusColumn = new TableColumn<>("Status");
    statusColumn.setCellValueFactory(cellData -> cellData.getValue().statusProperty());

    policyTable.getColumns().addAll(breedColumn, ageColumn, weightColumn, 
                                  vaccinatedColumn, premiumColumn, statusColumn);
    Button payButton = new Button("Pay Selected Policy");
    payButton.setOnAction(e -> {
        Policy selectedPolicy = policyTable.getSelectionModel().getSelectedItem();
        if (selectedPolicy != null && "Unpaid".equals(selectedPolicy.getStatus())) {
            dataManager.updatePay(currentFarmerId);
            selectedPolicy.setStatus("Paid");
            updatePolicyTable(policyTable);
        }
    });

    Button refreshButton = new Button("Refresh");
    refreshButton.setOnAction(e -> {
        updatePolicyTable(policyTable);
    });

    HBox buttonLayout = new HBox(10, payButton, refreshButton);
    policyManagementLayout.getChildren().addAll(buttonLayout, policyTable);

    return policyManagementLayout;
}
    
    private double calculatePremium(String breed, int age, double weight, boolean vaccinated) {
        double basePremium = 100;
        if ("SpecialBreed".equalsIgnoreCase(breed)) {
            basePremium += 50;
        }
        basePremium += age * 10;
        basePremium += weight * 2;
        if (vaccinated) {
            basePremium -= 20;
        }
        return basePremium;
    }

    private VBox createCattleManagementContent() {
        VBox content = new VBox(10);
        content.setPadding(new Insets(20));
    
        GridPane registrationForm = new GridPane();
        registrationForm.setHgap(10);
        registrationForm.setVgap(10);
        registrationForm.setPadding(new Insets(10));
    
        TextField breedField = new TextField();
        TextField ageField = new TextField();
        TextField weightField = new TextField();
        Button registerButton = new Button("Register Cattle");
        Button editButton = new Button("Edit Cattle");
        
        Label messageLabel = new Label();
        
        final String[] editingCattleId = {null};
    
        registrationForm.addRow(0, new Label("Breed:"), breedField);
        registrationForm.addRow(1, new Label("Age:"), ageField);
        registrationForm.addRow(2, new Label("Weight:"), weightField);
        registrationForm.addRow(3, new Label(""), registerButton);
        registrationForm.addRow(4, new Label(""), editButton);
        registrationForm.addRow(5, new Label(""), messageLabel);
    
        TableView<Cattle> cattleTable = new TableView<>();
    
        TableColumn<Cattle, String> uidCol = new TableColumn<>("UID");
        TableColumn<Cattle, String> breedCol = new TableColumn<>("Breed");
        TableColumn<Cattle, Integer> ageCol = new TableColumn<>("Age");
        TableColumn<Cattle, Double> weightCol = new TableColumn<>("Weight");
        TableColumn<Cattle, String> policyCol = new TableColumn<>("Insurance Policy");
    
        uidCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getUid()));
        breedCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getBreed()));
        ageCol.setCellValueFactory(data -> new SimpleIntegerProperty(data.getValue().getAge()).asObject());
        weightCol.setCellValueFactory(data -> new SimpleDoubleProperty(data.getValue().getWeight()).asObject());
        policyCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getInsurancePolicyId()));
    
        cattleTable.getColumns().addAll(uidCol, breedCol, ageCol, weightCol, policyCol);
    
        registerButton.setOnAction(e -> {
            try {
                String breed = breedField.getText();
                int age = Integer.parseInt(ageField.getText());
                double weight = Double.parseDouble(weightField.getText());
    
                if (editingCattleId[0] != null) {
                    dataManager.removeCattle(editingCattleId[0]);
                }
    
                String cattleId = dataManager.registerCattle(currentFarmerId, breed, age, weight);
                double premium = dataManager.calculatePremium(cattleId);
    
                messageLabel.setText("Cattle " + (editingCattleId[0] != null ? "updated" : "registered") + 
                                   " successfully! ID: " + cattleId +
                                   "\nEstimated premium: $" + String.format("%.2f", premium));
    
                breedField.clear();
                ageField.clear();
                weightField.clear();
                editingCattleId[0] = null;
                registerButton.setText("Register Cattle");  
                updateCattleTable(cattleTable);
    
            } catch (NumberFormatException ex) {
                messageLabel.setText("Please enter valid numbers for age and weight");
            } catch (Exception ex) {
                messageLabel.setText("Error registering cattle: " + ex.getMessage());
            }
        });
    
        editButton.setOnAction(e -> {
            Cattle selectedCattle = cattleTable.getSelectionModel().getSelectedItem();
            if (selectedCattle != null) {
                breedField.setText(selectedCattle.getBreed());
                ageField.setText(String.valueOf(selectedCattle.getAge()));
                weightField.setText(String.valueOf(selectedCattle.getWeight()));
                editingCattleId[0] = selectedCattle.getUid(); 
                registerButton.setText("Update Cattle"); 
                messageLabel.setText("Editing cattle with ID: " + selectedCattle.getUid());
            } else {
                messageLabel.setText("Please select a cattle to edit.");
            }
        });
    
        updateCattleTable(cattleTable);
    
        content.getChildren().addAll(
                new Label("Register New Cattle"),
                registrationForm,
                new Label("Your Registered Cattle"),
                cattleTable
        );
    
        return content;
    }

    private VBox createClaimsContent() {
        VBox content = new VBox(10);
        content.setPadding(new Insets(20));

        GridPane claimForm = new GridPane();
        claimForm.setHgap(10);
        claimForm.setVgap(10);
        claimForm.setPadding(new Insets(10));

        TextArea cattleIdArea = new TextArea();
        cattleIdArea.setPrefRowCount(3);
        TextArea reasonArea = new TextArea();
        reasonArea.setPrefRowCount(3);
        Button submitClaimButton = new Button("Submit Claim");
        Label claimMessageLabel = new Label();

        claimForm.addRow(0, new Label("Cattle Breed:"), cattleIdArea);
        claimForm.addRow(1, new Label("Reason:"), reasonArea);
        claimForm.addRow(2, new Label(""), submitClaimButton);
        claimForm.addRow(3, new Label(""), claimMessageLabel);

        TableView<InsuranceClaim> claimsTable = new TableView<>();

        TableColumn<InsuranceClaim, String> claimIdCol = new TableColumn<>("Claim ID");
        TableColumn<InsuranceClaim, String> cattleIdCol = new TableColumn<>("Cattle ID");
        TableColumn<InsuranceClaim, String> dateCol = new TableColumn<>("Date Submitted");
        TableColumn<InsuranceClaim, String> reasonCol = new TableColumn<>("Reason");
        TableColumn<InsuranceClaim, String> statusCol = new TableColumn<>("Status");

        claimIdCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getId()));
        cattleIdCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getCattleUid()));
        dateCol.setCellValueFactory(data -> new SimpleStringProperty(
                data.getValue().getDateSubmitted().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm"))
        ));
        reasonCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getReason()));
        statusCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getStatus().toString()));

        claimsTable.getColumns().addAll(claimIdCol, cattleIdCol, dateCol, reasonCol, statusCol);

        submitClaimButton.setOnAction(e -> {
            String cattleDetails = cattleIdArea.getText();
            String reason = reasonArea.getText();
    
            if (cattleDetails.isEmpty() || reason.isEmpty()) {
                claimMessageLabel.setText("Please enter cattle details and provide a reason");
                return;
            }
    
            Cattle matchedCattle = findMatchingCattle(cattleDetails);
            if (matchedCattle == null) {
                claimMessageLabel.setText("No cattle found matching the provided details.");
                return;
            }
    
            String claimId = dataManager.submitClaim(matchedCattle.getUid(), currentFarmerId, reason);
            if (claimId != null) {
                claimMessageLabel.setText("Claim submitted successfully! ID: " + claimId);
                cattleIdArea.clear();
                reasonArea.clear();
                updateClaimsTable(claimsTable);
            } else {
                claimMessageLabel.setText("Error submitting claim");
            }
        });

        updateClaimsTable(claimsTable);

        content.getChildren().addAll(
                new Label("Submit New Claim"),
                claimForm,
                new Label("Your Claims"),
                claimsTable
        );

        return content;
    }

    private VBox createAuditLogContent() {
        VBox content = new VBox(10);
        content.setPadding(new Insets(20));

        TableView<AuditLog> auditTable = new TableView<>();

        TableColumn<AuditLog, String> timeCol = new TableColumn<>("Timestamp");
        TableColumn<AuditLog, String> actionCol = new TableColumn<>("Action");
        TableColumn<AuditLog, String> descriptionCol = new TableColumn<>("Description");

        timeCol.setCellValueFactory(data -> new SimpleStringProperty(
                data.getValue().getTimestamp().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"))
        ));
        actionCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getAction()));
        descriptionCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getDescription()));

        auditTable.getColumns().addAll(timeCol, actionCol, descriptionCol);

        updateAuditTable(auditTable);

        Button refreshButton = new Button("Refresh");
        refreshButton.setOnAction(e -> updateAuditTable(auditTable));

        content.getChildren().addAll(
                new HBox(10, new Label("Audit Log"), refreshButton),
                auditTable
        );

        return content;
    }

    private void updateCattleTable(TableView<Cattle> table) {
        List<Cattle> cattleList = dataManager.getCattleByFarmer(currentFarmerId);
        table.setItems(FXCollections.observableArrayList(cattleList));
    }

    private void updatePolicyTable(TableView<Policy> policyTable) {
        ObservableList<Policy> tempList = FXCollections.observableArrayList(policyList);
        policyList.clear();
        policyList.addAll(tempList);
        policyTable.refresh();
    }

    private Cattle findMatchingCattle(String details) {
        List<Cattle> registeredCattle = dataManager.getCattleList(currentFarmerId);
    
        for (Cattle cattle : registeredCattle) {
            if (cattle.getUid().equalsIgnoreCase(details) ||
                    cattle.getBreed().equalsIgnoreCase(details) ||
                    String.valueOf(cattle.getAge()).equals(details) ||
                    String.valueOf(cattle.getWeight()).equals(details)) {
                return cattle;
            }
        }
        return null;
    }

    

     private void updateClaimsTable(TableView<InsuranceClaim> table) {
        List<InsuranceClaim> claims = dataManager.getClaimsByFarmer(currentFarmerId);
        table.setItems(FXCollections.observableArrayList(claims));
    }

    private void updateAuditTable(TableView<AuditLog> table) {
        List<AuditLog> logs = dataManager.getAuditLogsByFarmer(currentFarmerId);
        table.setItems(FXCollections.observableArrayList(logs));
    }

    private Scene createAdminScene() {
        TabPane adminTabPane = new TabPane();

        Tab claimsManagementTab = new Tab("Claims Management");
        Tab farmerManagementTab = new Tab("Farmer Management");
        Tab systemAuditTab = new Tab("System Audit");

        claimsManagementTab.setClosable(false);
        farmerManagementTab.setClosable(false);
        systemAuditTab.setClosable(false);

        claimsManagementTab.setContent(createClaimsManagementContent());
        farmerManagementTab.setContent(createFarmerManagementContent());
        systemAuditTab.setContent(createSystemAuditContent());

        Button logoutButton = new Button("Logout");
        logoutButton.setOnAction(e -> {
            isAdmin = false;
            primaryStage.setScene(loginScene);
        });

        VBox adminLayout = new VBox(10);
        adminLayout.setPadding(new Insets(10));

        adminTabPane.getTabs().addAll(claimsManagementTab, farmerManagementTab, systemAuditTab);
        adminLayout.getChildren().addAll(logoutButton, adminTabPane);

        return new Scene(adminLayout, 800, 600);
    }

    private VBox createClaimsManagementContent() {
        VBox content = new VBox(10);
        content.setPadding(new Insets(20));

        TableView<InsuranceClaim> claimsTable = new TableView<>();

        TableColumn<InsuranceClaim, String> claimIdCol = new TableColumn<>("Claim ID");
        TableColumn<InsuranceClaim, String> cattleIdCol = new TableColumn<>("Cattle ID");
        TableColumn<InsuranceClaim, String> farmerIdCol = new TableColumn<>("Farmer ID");
        TableColumn<InsuranceClaim, String> dateCol = new TableColumn<>("Date Submitted");
        TableColumn<InsuranceClaim, String> reasonCol = new TableColumn<>("Reason");
        TableColumn<InsuranceClaim, String> statusCol = new TableColumn<>("Status");

        claimIdCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getId()));
        cattleIdCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getCattleUid()));
        farmerIdCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getFarmerId()));
        dateCol.setCellValueFactory(data -> new SimpleStringProperty(
                data.getValue().getDateSubmitted().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm"))
        ));
        reasonCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getReason()));
        statusCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getStatus().toString()));

        claimsTable.getColumns().addAll(claimIdCol, cattleIdCol, farmerIdCol, dateCol, reasonCol, statusCol);

        HBox controlsBox = new HBox(10);
        controlsBox.setAlignment(Pos.CENTER_LEFT);

        ComboBox<String> statusComboBox = new ComboBox<>(
                FXCollections.observableArrayList("APPROVED", "REJECTED")
        );
        Button updateStatusButton = new Button("Update Status");
        Label messageLabel = new Label();
        messageLabel.setWrapText(true);

        updateStatusButton.setOnAction(e -> {
            InsuranceClaim selectedClaim = claimsTable.getSelectionModel().getSelectedItem();
            String newStatus = statusComboBox.getValue();

            if (selectedClaim == null) {
                messageLabel.setText("Please select a claim to update");
                return;
            }

            if (newStatus == null) {
                messageLabel.setText("Please select a status");
                return;
            }

            if (dataManager.updateClaimStatus(selectedClaim.getId(),
                    InsuranceClaim.ClaimStatus.valueOf(newStatus))) {
                messageLabel.setText("Claim status updated successfully");
                refreshClaimsTable(claimsTable);
            } else {
                messageLabel.setText("Failed to update claim status");
            }
        });

        Button refreshButton = new Button("Refresh");
        refreshButton.setOnAction(e -> refreshClaimsTable(claimsTable));

        controlsBox.getChildren().addAll(
                new Label("Update Status:"),
                statusComboBox,
                updateStatusButton,
                refreshButton,
                messageLabel
        );

        refreshClaimsTable(claimsTable);

        content.getChildren().addAll(
                new Label("Insurance Claims Management"),
                controlsBox,
                claimsTable
        );

        return content;
    }

    private void refreshClaimsTable(TableView<InsuranceClaim> table) {
        table.setItems(FXCollections.observableArrayList(dataManager.getAllClaims()));
    }

    private VBox createFarmerManagementContent() {
        VBox content = new VBox(10);
        content.setPadding(new Insets(20));

        ListView<String> farmerListView = new ListView<>();
        farmerListView.setItems(FXCollections.observableArrayList(dataManager.getAllFarmerIds()));

        TableView<Cattle> cattleTable = new TableView<>();

        TableColumn<Cattle, String> uidCol = new TableColumn<>("Cattle ID");
        TableColumn<Cattle, String> breedCol = new TableColumn<>("Breed");
        TableColumn<Cattle, Integer> ageCol = new TableColumn<>("Age");
        TableColumn<Cattle, Double> weightCol = new TableColumn<>("Weight");
        TableColumn<Cattle, String> ownerCol = new TableColumn<>("Owner ID");

        uidCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getUid()));
        breedCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getBreed()));
        ageCol.setCellValueFactory(data -> new SimpleIntegerProperty(data.getValue().getAge()).asObject());
        weightCol.setCellValueFactory(data -> new SimpleDoubleProperty(data.getValue().getWeight()).asObject());
        ownerCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getFarmerId()));

        cattleTable.getColumns().addAll(uidCol, breedCol, ageCol, weightCol, ownerCol);

        HBox transferControls = new HBox(10);
        transferControls.setAlignment(Pos.CENTER_LEFT);

        ComboBox<String> newOwnerComboBox = new ComboBox<>();
        Button transferButton = new Button("Transfer Ownership");
        Label messageLabel = new Label();
        messageLabel.setWrapText(true);

        transferButton.setOnAction(e -> {
            Cattle selectedCattle = cattleTable.getSelectionModel().getSelectedItem();
            String newOwner = newOwnerComboBox.getValue();

            if (selectedCattle == null) {
                messageLabel.setText("Please select cattle to transfer");
                return;
            }

            if (newOwner == null) {
                messageLabel.setText("Please select new owner");
                return;
            }

            if (dataManager.transferCattleOwnership(selectedCattle.getUid(), newOwner)) {
                messageLabel.setText("Ownership transferred successfully");
                String selectedFarmer = farmerListView.getSelectionModel().getSelectedItem();
                if (selectedFarmer != null) {
                    updateCattleTable(cattleTable, selectedFarmer);
                }
            } else {
                messageLabel.setText("Failed to transfer ownership");
            }
        });

        transferControls.getChildren().addAll(
                new Label("Transfer to:"),
                newOwnerComboBox,
                transferButton,
                messageLabel
        );

        farmerListView.getSelectionModel().selectedItemProperty().addListener(
                (observable, oldValue, newValue) -> {
                    if (newValue != null) {
                        updateCattleTable(cattleTable, newValue);
                        newOwnerComboBox.setItems(
                                FXCollections.observableArrayList(
                                        dataManager.getAllFarmerIds().stream()
                                                .filter(id -> !id.equals(newValue))
                                                .collect(Collectors.toList())
                                )
                        );
                    }
                }
        );

        content.getChildren().addAll(
                new Label("Farmer Management"),
                new HBox(10,
                        new VBox(10,
                                new Label("Farmers"),
                                farmerListView
                        ),
                        new VBox(10,
                                new Label("Cattle Owned"),
                                cattleTable,
                                transferControls
                        )
                )
        );

        return content;
    }

    private void updateCattleTable(TableView<Cattle> table, String farmerId) {
        table.setItems(FXCollections.observableArrayList(
                dataManager.getCattleByFarmer(farmerId)
        ));
    }

    private VBox createSystemAuditContent() {
        VBox content = new VBox(10);
        content.setPadding(new Insets(20));

        TableView<AuditLog> auditTable = new TableView<>();

        TableColumn<AuditLog, String> timeCol = new TableColumn<>("Timestamp");
        TableColumn<AuditLog, String> userCol = new TableColumn<>("User ID");
        TableColumn<AuditLog, String> actionCol = new TableColumn<>("Action");
        TableColumn<AuditLog, String> descriptionCol = new TableColumn<>("Description");

        timeCol.setCellValueFactory(data -> new SimpleStringProperty(
                data.getValue().getTimestamp().format(DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss"))
        ));
        userCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getUserId()));
        actionCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getAction()));
        descriptionCol.setCellValueFactory(data -> new SimpleStringProperty(data.getValue().getDescription()));

        timeCol.setPrefWidth(150);
        userCol.setPrefWidth(100);
        actionCol.setPrefWidth(150);
        descriptionCol.setPrefWidth(300);

        auditTable.getColumns().addAll(timeCol, userCol, actionCol, descriptionCol);

        HBox filterControls = new HBox(10);
        filterControls.setAlignment(Pos.CENTER_LEFT);

        ComboBox<String> userFilter = new ComboBox<>();
        userFilter.setPromptText("Filter by User");
        userFilter.getItems().add("All Users");
        userFilter.getItems().addAll(dataManager.getAllFarmerIds());
        userFilter.setValue("All Users");

        DatePicker datePicker = new DatePicker();
        datePicker.setPromptText("Filter by Date");

        Button applyFiltersButton = new Button("Apply Filters");
        Button refreshButton = new Button("Refresh");

        filterControls.getChildren().addAll(
                new Label("Filters:"),
                userFilter,
                datePicker,
                applyFiltersButton,
                refreshButton
        );

        applyFiltersButton.setOnAction(e -> {
            String selectedUser = userFilter.getValue();
            LocalDate selectedDate = datePicker.getValue();

            List<AuditLog> filteredLogs = dataManager.getAllAuditLogs().stream()
                    .filter(log -> {
                        boolean userMatch = selectedUser.equals("All Users") ||
                                log.getUserId().equals(selectedUser);
                        boolean dateMatch = selectedDate == null ||
                                log.getTimestamp().toLocalDate().equals(selectedDate);
                        return userMatch && dateMatch;
                    })
                    .collect(Collectors.toList());

            auditTable.setItems(FXCollections.observableArrayList(filteredLogs));
        });

        refreshButton.setOnAction(e -> {
            userFilter.setValue("All Users");
            datePicker.setValue(null);
            refreshAuditTable(auditTable);
        });

        refreshAuditTable(auditTable);

        content.getChildren().addAll(
                new Label("System Audit Log"),
                filterControls,
                auditTable
        );

        return content;
    }

    private void refreshAuditTable(TableView<AuditLog> table) {
        table.setItems(FXCollections.observableArrayList(dataManager.getAllAuditLogs()));
    }
}

class DataManager {
    private Map<String, Admin> admins = new ConcurrentHashMap<>();
    private Map<String, Farmer> farmers = new ConcurrentHashMap<>();
    private Map<String, Cattle> cattle = new ConcurrentHashMap<>();
    private Map<String, InsuranceClaim> claims = new ConcurrentHashMap<>();
    private List<AuditLog> auditLogs = new CopyOnWriteArrayList<>();

    private static DataManager instance;

    private DataManager() {}

    public static DataManager getInstance() {
        if (instance == null) {
            instance = new DataManager();
            instance.addDemoData();
        }
        return instance;
    }

    public void removeCattle(String cattleId) {

    }

    public List<Cattle> getCattleList(String farmerId) {
        return getCattleByFarmer(farmerId);
    }

    public List<AuditLog> getAllAuditLogs() {
        return new ArrayList<>(auditLogs);
    }

    

    private void addDemoData() {
        registerFarmer("demo", "demofarmer", "demolocation", "password");

        registerCattle("demo", "ab", 3, 500.0);
        registerCattle("demo", "cd", 2, 450.0);
    }


    public boolean registerFarmer(String username, String name, String location, String password) {
        if (farmers.containsKey(username)) {
            return false;
        }
        Farmer farmer = new Farmer(username, name, location, password);
        farmers.put(username, farmer);
        logAction("FARMER_REGISTRATION", username, "New Farmer Registered");
        return true;
    }

    public void updateAL(String user)
    {
        logAction("POLICY_SUBMISSION", user, "New Policy Submitted");
    }

    public void updatePay(String user)
    {
        logAction("POLICY_PAID", user, "Policy Payment Successful");
    }

    public boolean usernameExists(String username) {
        return farmers.containsKey(username);
    }

    public boolean authenticateFarmer(String username, String password) {
        Farmer farmer = farmers.get(username);
        if (farmer != null && farmer.verifyIntegrity()) {
            return farmer.getPassword().equals(password);
        }
        return false;
    }
    public String registerCattle(String farmerId, String breed, int age, double weight) {
        Cattle newCattle = new Cattle(farmerId, breed, age, weight);
        cattle.put(newCattle.getUid(), newCattle);
        logAction("CATTLE_REGISTRATION", farmerId, "New Cattle Registered: " + newCattle.getUid());
        return newCattle.getUid();
    }

    public List<Cattle> getCattleByFarmer(String farmerId) {
        return cattle.values().stream()
                .filter(c -> c.getFarmerId().equals(farmerId) && c.verifyIntegrity())
                .collect(Collectors.toList());
    }

    public String submitClaim(String cattleUid, String farmerId, String reason) {
        Cattle claimedCattle = cattle.get(cattleUid);
        if (claimedCattle != null && claimedCattle.verifyIntegrity() &&
                claimedCattle.getFarmerId().equals(farmerId)) {

            InsuranceClaim claim = new InsuranceClaim(cattleUid, farmerId, reason);
            claims.put(claim.getId(), claim);
            logAction("CLAIM_SUBMISSION", farmerId, "New Claim Submitted for Cattle: " + cattleUid);
            return claim.getId();
        }
        return null;
    }

    public List<InsuranceClaim> getClaimsByFarmer(String farmerId) {
        return claims.values().stream()
                .filter(c -> c.getFarmerId().equals(farmerId))
                .collect(Collectors.toList());
    }

    public double calculatePremium(String cattleUid) {
        Cattle cattle = this.cattle.get(cattleUid);
        if (cattle != null && cattle.verifyIntegrity()) {
            double basePremium = 1000.0;
            double ageMultiplier = Math.max(0.5, 1.0 - (cattle.getAge() * 0.05));
            double weightMultiplier = cattle.getWeight() / 500.0;
            return basePremium * ageMultiplier * weightMultiplier;
        }
        return 0.0;
    }

    private void logAction(String action, String userId, String description) {
        AuditLog log = new AuditLog(action, userId, description);
        auditLogs.add(log);
    }

    public List<AuditLog> getAuditLogsByFarmer(String farmerId) {
        return auditLogs.stream()
                .filter(log -> log.getUserId().equals(farmerId))
                .collect(Collectors.toList());
    }

    public static String generateChecksum(String input) {
        try {
            MessageDigest digest = MessageDigest.getInstance("SHA-256");
            byte[] hash = digest.digest(input.getBytes(StandardCharsets.UTF_8));
            return Base64.getEncoder().encodeToString(hash);
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException("Failed to generate checksum", e);
        }
    }
    public void createAdminAccount(String username, String password) {
        Admin admin = new Admin(username, password);
        admins.put(username, admin);
    }

    public boolean authenticateAdmin(String username, String password) {
        Admin admin = admins.get(username);
        return admin != null && admin.getPassword().equals(password);
    }

    public boolean updateClaimStatus(String claimId, InsuranceClaim.ClaimStatus status) {
        InsuranceClaim claim = claims.get(claimId);
        if (claim != null) {
            claim.setStatus(status);
            logAction("CLAIM_STATUS_UPDATE", "ADMIN",
                    "Updated Claim " + claimId + " Status to " + status);
            return true;
        }
        return false;
    }

    public List<InsuranceClaim> getAllClaims() {
        return new ArrayList<>(claims.values());
    }

    public List<String> getAllFarmerIds() {
        return new ArrayList<>(farmers.keySet());
    }

    public boolean transferCattleOwnership(String cattleId, String newOwnerId) {
        Cattle cattleToTransfer = cattle.get(cattleId);
        if (cattleToTransfer != null && farmers.containsKey(newOwnerId)) {
            String oldOwnerId = cattleToTransfer.getFarmerId();
            cattleToTransfer.setFarmerId(newOwnerId);
            logAction("CATTLE_TRANSFER", "ADMIN",
                    "Transferred Cattle " + cattleId + " from " + oldOwnerId + " to " + newOwnerId);
            return true;
        }
        return false;
    }
}

class Admin {
    private String username;
    private String password;
    private String checksum;

    public Admin(String username, String password) {
        this.username = username;
        this.password = password;
        updateChecksum();
    }

    private void updateChecksum() {
        this.checksum = DataManager.generateChecksum(username + password);
    }

    public String getUsername() { return username; }
    public String getPassword() { return password; }
}

class Farmer {
    private String username;  
    private String name;
    private String location;
    private String password;
    private String checksum;
    private List<InsurancePolicy> insurancePolicies = new ArrayList<>();

    public Farmer(String username, String name, String location, String password) {
        this.username = username; 
        this.name = name;
        this.location = location;
        this.password = password;
        insurancePolicies = new ArrayList<>();

        updateChecksum();
    }

    private void updateChecksum() {
        this.checksum = DataManager.generateChecksum(username + name + location + password);
    }

    public boolean verifyIntegrity() {
        return checksum.equals(DataManager.generateChecksum(username + name + location + password));
    }

    public String getId() { return username; }  
    public String getUsername() { return username; }
    public String getName() { return name; }
    public String getLocation() { return location; }
    public String getPassword() { return password; }
    public List<InsurancePolicy> getInsurancePolicies() {
        return insurancePolicies;
    }
}

class Cattle<T> {
    private final String uid;
    private String farmerId;
    private String breed;
    private int age;
    private double weight;
    private List<T> vaccinationRecords;
    private String insurancePolicyId;
    private volatile String checksum;
    private final ReentrantLock lock = new ReentrantLock();
    private static final ExecutorService executorService = Executors.newCachedThreadPool();

    public Cattle(String farmerId, String breed, int age, double weight) {
        this.uid = UUID.randomUUID().toString();
        this.farmerId = farmerId;
        this.breed = breed;
        this.age = age;
        this.weight = weight;
        this.vaccinationRecords = new ArrayList<>();
        updateChecksum();
    }

    private void updateChecksum() {
        executorService.submit(() -> {
            lock.lock();
            try {
                this.checksum = DataManager.generateChecksum(
                        uid + farmerId + breed + age + weight +
                        vaccinationRecords.toString() + insurancePolicyId);
            } finally {
                lock.unlock();
            }
        });
    }

    public boolean verifyIntegrity() {
        lock.lock();
        try {
            return checksum.equals(DataManager.generateChecksum(
                    uid + farmerId + breed + age + weight +
                    vaccinationRecords.toString() + insurancePolicyId));
        } finally {
            lock.unlock();
        }
    }

    public String getUid() { return uid; }

    public String getFarmerId() { return farmerId; }

    public void setFarmerId(String farmerId) {
        this.farmerId = farmerId;
        updateChecksum();
    }

    public String getBreed() { return breed; }
    public int getAge() { return age; }
    public double getWeight() { return weight; }
    public String getInsurancePolicyId() { return insurancePolicyId; }
    public List<T> getVaccinationRecords() { return vaccinationRecords; }

    public void addVaccinationRecord(T record) {
        lock.lock();
        try {
            vaccinationRecords.add(record);
            updateChecksum();
        } finally {
            lock.unlock();
        }
    }

    public void setInsurancePolicyId(String insurancePolicyId) {
        this.insurancePolicyId = insurancePolicyId;
        updateChecksum();
    }

    public static void shutdown() {
        executorService.shutdown();
    }
}

class Policy {
    private StringProperty breed;
    private IntegerProperty age;
    private DoubleProperty weight;
    private BooleanProperty vaccinated;
    private DoubleProperty premium;
    private StringProperty status;

    public Policy(String breed, int age, double weight, boolean vaccinated, double premium) {
        this.breed = new SimpleStringProperty(breed);
        this.age = new SimpleIntegerProperty(age);
        this.weight = new SimpleDoubleProperty(weight);
        this.vaccinated = new SimpleBooleanProperty(vaccinated);
        this.premium = new SimpleDoubleProperty(premium);
        this.status = new SimpleStringProperty("Unpaid");
    }

    public StringProperty breedProperty() { return breed; }
    public IntegerProperty ageProperty() { return age; }
    public DoubleProperty weightProperty() { return weight; }
    public BooleanProperty vaccinatedProperty() { return vaccinated; }
    public DoubleProperty premiumProperty() { return premium; }
    public StringProperty statusProperty() { return status; }

    public String getBreed() { return breed.get(); }
    public int getAge() { return age.get(); }
    public double getWeight() { return weight.get(); }
    public boolean isVaccinated() { return vaccinated.get(); }
    public double getPremium() { return premium.get(); }
    public String getStatus() { return status.get(); }

    public void setBreed(String value) { breed.set(value); }
    public void setAge(int value) { age.set(value); }
    public void setWeight(double value) { weight.set(value); }
    public void setVaccinated(boolean value) { vaccinated.set(value); }
    public void setPremium(double value) { premium.set(value); }
    public void setStatus(String value) { status.set(value); }
}

class InsurancePolicy {
    private String breed;
    private int age;
    private double premium;
    private String status; // e.g., "Unpaid", "Paid", "Expired"

    public InsurancePolicy(String breed, int age, double premium) {
        this.breed = breed;
        this.age = age;
        this.premium = premium;
        this.status = "Unpaid";
    }

    public static double scalculatePremium(Cattle cattle) {
        double basePremium = 100.0; 
        double ageFactor = cattle.getAge() * 10.0;
        double weightFactor = cattle.getWeight() * 5.0;
        return basePremium + ageFactor + weightFactor;
    }

    public String getBreed() {
        return breed;
    }

    public int getAge() {
        return age;
    }

    public double getPremium() {
        return premium;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }
} 

class InsuranceClaim {
    private String id;
    private String cattleUid;
    private String farmerId;
    private LocalDateTime dateSubmitted;
    private String reason;
    private ClaimStatus status;
    private String checksum;

    public enum ClaimStatus {
        PENDING, APPROVED, REJECTED
    }

    public InsuranceClaim(String cattleUid, String farmerId, String reason) {
        this.id = UUID.randomUUID().toString();
        this.cattleUid = cattleUid;
        this.farmerId = farmerId;
        this.dateSubmitted = LocalDateTime.now();
        this.reason = reason;
        this.status = ClaimStatus.PENDING;
        updateChecksum();
    }

    private void updateChecksum() {
        this.checksum = DataManager.generateChecksum(id + cattleUid + farmerId +
                dateSubmitted.toString() + reason + status);
    }

    public void setStatus(ClaimStatus status) {
        this.status = status;
        updateChecksum();
    }

    public String getId() { return id; }
    public String getCattleUid() { return cattleUid; }
    public String getFarmerId() { return farmerId; }
    public LocalDateTime getDateSubmitted() { return dateSubmitted; }
    public String getReason() { return reason; }
    public ClaimStatus getStatus() { return status; }
}

class AuditLog {
    private String id;
    private String action;
    private String userId;
    private String description;
    private LocalDateTime timestamp;
    private String checksum;

    public AuditLog(String action, String userId, String description) {
        this.id = UUID.randomUUID().toString();
        this.action = action;
        this.userId = userId;
        this.description = description;
        this.timestamp = LocalDateTime.now();
        updateChecksum();
    }

    private void updateChecksum() {
        this.checksum = DataManager.generateChecksum(
                id + action + userId + description + timestamp.toString()
        );
    }

    public String getId() { return id; }
    public String getAction() { return action; }
    public String getUserId() { return userId; }
    public String getDescription() { return description; }
    public LocalDateTime getTimestamp() { return timestamp; }
}

