package com.example.demo;


import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class FarmerSystemFX extends Application 
{

    // Farmer registry (in-memory storage)
    private Map<String, Admin> adminRegistry = new HashMap<>();
    private static Map<String, Farmer> farmerRegistry = new HashMap<>();

    // JavaFX controls
    private TextField tfFarmerId, tfName, tfFarmLocation;
    private PasswordField pfPassword, pfLoginPassword;
    private Button btnRegister, btnLogin;
    private Label lblStatus;

    public static void main(String[] args) {
        launch(args);
    }

    @Override

    public void start(Stage primaryStage) {
        primaryStage.setTitle("Cattle Management System");
    
        // Welcome Page
        GridPane welcomeGrid = new GridPane();
        welcomeGrid.setHgap(10);
        welcomeGrid.setVgap(10);
    
        Label lblWelcome = new Label("Welcome! Please select your role:");
        welcomeGrid.add(lblWelcome, 0, 0);
    
        Button btnUserLogin = new Button("User Login");
        welcomeGrid.add(btnUserLogin, 0, 1);
    
        Button btnAdminLogin = new Button("Admin Login");
        welcomeGrid.add(btnAdminLogin, 0, 2);
    
        Scene welcomeScene = new Scene(welcomeGrid, 300, 150);
        primaryStage.setScene(welcomeScene);
        primaryStage.show();
    
        // User Login setup
        btnUserLogin.setOnAction(e -> showUserLogin(primaryStage));
    
        // Admin Login setup
        btnAdminLogin.setOnAction(e -> showAdminLogin(primaryStage));
    }
    public void showUserLogin(Stage primaryStage) {
        primaryStage.setTitle("Farmer System");

        // Create the grid layout
        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);

        // Registration form
        Label lblRegister = new Label("Register Farmer");
        grid.add(lblRegister, 0, 0);

        grid.add(new Label("Farmer ID:"), 0, 1);
        tfFarmerId = new TextField();
        grid.add(tfFarmerId, 1, 1);

        grid.add(new Label("Name:"), 0, 2);
        tfName = new TextField();
        grid.add(tfName, 1, 2);

        grid.add(new Label("Farm Location:"), 0, 3);
        tfFarmLocation = new TextField();
        grid.add(tfFarmLocation, 1, 3);

        grid.add(new Label("Password:"), 0, 4);
        pfPassword = new PasswordField();
        grid.add(pfPassword, 1, 4);

        btnRegister = new Button("Register");
        grid.add(btnRegister, 1, 5);

        // Login form
        Label lblLogin = new Label("Farmer Login");
        grid.add(lblLogin, 0, 6);

        grid.add(new Label("Farmer ID:"), 0, 7);
        TextField tfLoginFarmerId = new TextField();
        grid.add(tfLoginFarmerId, 1, 7);

        grid.add(new Label("Password:"), 0, 8);
        pfLoginPassword = new PasswordField();
        grid.add(pfLoginPassword, 1, 8);

        btnLogin = new Button("Login");
        grid.add(btnLogin, 1, 9);

        lblStatus = new Label();
        grid.add(lblStatus, 1, 10);

        // Set up event handling for buttons
        btnRegister.setOnAction(e -> registerFarmer());
        btnLogin.setOnAction(e -> loginFarmer(tfLoginFarmerId.getText(), pfLoginPassword.getText(), primaryStage));

        // Set the scene and display it
        Scene scene = new Scene(grid, 400, 300);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void showAdminLogin(Stage primaryStage) {
        primaryStage.setTitle("Admin System");
    
        // Create the grid layout
        GridPane grid = new GridPane();
        grid.setHgap(10);
        grid.setVgap(10);
    
        // Registration form
        Label lblRegister = new Label("Register Admin");
        grid.add(lblRegister, 0, 0);
    
        grid.add(new Label("Admin ID:"), 0, 1);
        TextField tfAdminId = new TextField(); // Use a distinct field for Admin ID
        grid.add(tfAdminId, 1, 1);
    
        grid.add(new Label("Name:"), 0, 2);
        TextField tfAdminName = new TextField(); // Use a distinct field for Admin Name
        grid.add(tfAdminName, 1, 2);
    
        grid.add(new Label("Password:"), 0, 3);
        PasswordField pfAdminPassword = new PasswordField(); // Use a distinct field for Admin Password
        grid.add(pfAdminPassword, 1, 3);
    
        Button btnRegisterAdmin = new Button("Register");
        grid.add(btnRegisterAdmin, 1, 4);
    
        // Login form
        Label lblLogin = new Label("Admin Login");
        grid.add(lblLogin, 0, 5);
    
        grid.add(new Label("Admin ID:"), 0, 6);
        TextField tfLoginAdminId = new TextField();
        grid.add(tfLoginAdminId, 1, 6);
    
        grid.add(new Label("Password:"), 0, 7);
        PasswordField pfLoginAdminPassword = new PasswordField();
        grid.add(pfLoginAdminPassword, 1, 7);
    
        Button btnAdminLogin = new Button("Login");
        grid.add(btnAdminLogin, 1, 8);
    
        Label lblAdminStatus = new Label();
        grid.add(lblAdminStatus, 1, 9);
    
        // Set up event handling for buttons
        btnRegisterAdmin.setOnAction(e -> registerAdmin(tfAdminId, tfAdminName, pfAdminPassword, lblAdminStatus));
        btnAdminLogin.setOnAction(e -> loginAdmin(tfLoginAdminId.getText(), pfLoginAdminPassword.getText(), lblAdminStatus, primaryStage));
    
        // Set the scene and display it
        Scene scene = new Scene(grid, 400, 300);
        primaryStage.setScene(scene);
        primaryStage.show();
    }
    
    // Register Admin method
    private void registerAdmin(TextField tfAdminId, TextField tfAdminName, PasswordField pfAdminPassword, Label lblAdminStatus) {
        String adminId = tfAdminId.getText();
        String name = tfAdminName.getText();
        String password = pfAdminPassword.getText();
    
        if (adminId.isEmpty() || name.isEmpty() || password.isEmpty()) {
            lblAdminStatus.setText("All fields must be filled.");
            return;
        }
    
        if (adminRegistry.containsKey(adminId)) { // Use a separate registry for admins
            lblAdminStatus.setText("Admin ID already exists.");
        } else {
            Admin admin = new Admin(adminId, name, password); // Use an Admin class
            adminRegistry.put(adminId, admin);
            lblAdminStatus.setText("Admin registered successfully.");
            tfAdminId.clear();
            tfAdminName.clear();
            pfAdminPassword.clear();
        }
    }
    
    // Admin Login method
    private void loginAdmin(String adminId, String password, Label lblAdminStatus, Stage primaryStage) {
        if (adminId.isEmpty() || password.isEmpty()) {
            lblAdminStatus.setText("Please enter Admin ID and Password.");
            return;
        }
    
        Admin admin = adminRegistry.get(adminId); // Retrieve from the admin registry
        if (admin != null && admin.getPassword().equals(password)) {
            lblAdminStatus.setText("Login successful!");
            showAdminDashboard(primaryStage); // Navigate to Admin Dashboard
        } else {
            lblAdminStatus.setText("Invalid Admin ID or Password.");
        }
    }
    
    
    private void showAdminDashboard(Stage primaryStage) {
        Stage adminStage = new Stage();
        adminStage.setTitle("Admin Dashboard");
    
        GridPane adminGrid = new GridPane();
        adminGrid.setHgap(10);
        adminGrid.setVgap(10);
    
        Label lblAdmin = new Label("Admin Dashboard");
        adminGrid.add(lblAdmin, 0, 0);
    
        Button btnManageFarmers = new Button("Manage Farmers");
        adminGrid.add(btnManageFarmers, 0, 1);
    
        Button btnViewReports = new Button("View Reports");
        adminGrid.add(btnViewReports, 0, 2);
    
        Scene adminScene = new Scene(adminGrid, 300, 150);
        adminStage.setScene(adminScene);
        adminStage.show();
        primaryStage.hide(); // Hide the primary stage
    }

    private void clearFields() {
        tfFarmerId.clear();
        tfName.clear();
        tfFarmLocation.clear();
        pfPassword.clear();
    }

    // Register Farmer method
    private void registerFarmer() {
        String farmerId = tfFarmerId.getText();
        String name = tfName.getText();
        String farmLocation = tfFarmLocation.getText();
        String password = pfPassword.getText();

        if (farmerId.isEmpty() || name.isEmpty() || farmLocation.isEmpty() || password.isEmpty()) {
            lblStatus.setText("All fields must be filled.");
            return;
        }

        if (farmerRegistry.containsKey(farmerId)) {
            lblStatus.setText("Farmer ID already exists.");
        } else {
            Farmer farmer = new Farmer(farmerId, name, farmLocation, password);
            farmerRegistry.put(farmerId, farmer);
            lblStatus.setText("Farmer registered successfully.");
            clearFields();
        }
    }

    // Farmer Login method
    private void loginFarmer(String farmerId, String password, Stage primaryStage) {
        if (farmerId.isEmpty() || password.isEmpty()) {
            lblStatus.setText("Please enter Farmer ID and Password.");
            return;
        }

        Farmer farmer = farmerRegistry.get(farmerId);
        if (farmer != null && farmer.getPassword().equals(password)) {
            lblStatus.setText("Login successful!");
            showPostLoginMenu(farmer, primaryStage);
        } else {
            lblStatus.setText("Invalid Farmer ID or Password.");
        }
    }

    private void showPostLoginMenu(Farmer farmer, Stage primaryStage) {
        Stage postLoginStage = new Stage();  // Declare and instantiate the postLoginStage
        postLoginStage.setTitle("Welcome, " + farmer.getName());

        GridPane postLoginGrid = new GridPane();
        postLoginGrid.setHgap(10);
        postLoginGrid.setVgap( 10);

        Label lblWelcome = new Label("Welcome, " + farmer.getName());
        postLoginGrid.add(lblWelcome, 0, 0);

        Button btnManageCattle = new Button("Manage Cattle");
        postLoginGrid.add(btnManageCattle, 0, 1);

        Button btnViewInsurance = new Button("View Insurance Policies");
        postLoginGrid.add(btnViewInsurance, 0, 2);

        Button btnFileClaim = new Button("File Insurance Claim");
        postLoginGrid.add(btnFileClaim, 0, 3);

        Button btnViewClaimStatus = new Button("View Claim Status"); // New button for viewing claim status
        postLoginGrid.add(btnViewClaimStatus, 0, 4); // Adjusted row index for correct placement

        Button btnManageInsurance = new Button("Add Insurance Policies");
        postLoginGrid.add(btnManageInsurance, 0, 5);

        // Actions for managing cattle
        btnManageCattle.setOnAction(e -> showCattleManagement(farmer));

        btnViewInsurance.setOnAction(e -> showInsurancePolicies(farmer));

        btnFileClaim.setOnAction(e -> showClaimFiling(farmer));

        btnViewClaimStatus.setOnAction(e -> showClaimStatus(farmer)); // Action for viewing claim status

        btnManageInsurance.setOnAction(e -> showInsurancePolicyManagement(farmer));

        Scene postLoginScene = new Scene(postLoginGrid, 300, 200);
        postLoginStage.setScene(postLoginScene);
        postLoginStage.show();
        primaryStage.hide(); // Hide the primary stage instead of closing it
    }

    // Cattle Management
    private void showCattleManagement(Farmer farmer) {
        Stage cattleStage = new Stage();
        cattleStage.setTitle("Manage Cattle");

        GridPane cattleGrid = new GridPane();
        cattleGrid.setHgap(10);
        cattleGrid.setVgap(10);

        // Cattle input fields
        cattleGrid.add(new Label("Breed:"), 0, 0);
        TextField tfBreed = new TextField();
        cattleGrid.add(tfBreed, 1, 0);

        cattleGrid.add(new Label("Age:"), 0, 1);
        TextField tfAge = new TextField();
        cattleGrid.add(tfAge, 1, 1);

        cattleGrid.add(new Label("Weight:"), 0, 2);
        TextField tfWeight = new TextField();
        cattleGrid.add(tfWeight, 1, 2);

        cattleGrid.add(new Label("Vaccination Status:"), 0, 3);
        TextField tfVaccination = new TextField();
        cattleGrid.add(tfVaccination, 1, 3);

        Button btnAddCattle = new Button("Add Cattle");
        cattleGrid.add(btnAddCattle, 1, 4);

        Button btnViewCattle = new Button("View Cattle");
        cattleGrid.add(btnViewCattle, 1, 5);

        // Add cattle to the farmer's cattle list
        btnAddCattle.setOnAction(e -> {
            try {
                String breed = tfBreed.getText();
                int age = Integer.parseInt(tfAge.getText());
                double weight = Double.parseDouble(tfWeight.getText());
                String vaccinationStatus = tfVaccination.getText();

                Cattle cattle = new Cattle(breed, age, weight, vaccinationStatus);
                farmer.addCattle(cattle);

                showAlert("Cattle Added", "Cattle has been added successfully.");
                clearCattleFields(tfBreed, tfAge, tfWeight, tfVaccination);
            } catch (NumberFormatException ex) {
                showAlert("Input Error", "Please enter valid numbers for age and weight.");
            }
        });

        // Display cattle details
        btnViewCattle.setOnAction(e -> displayCattleDetails(farmer));

        Scene cattleScene = new Scene(cattleGrid, 400, 300);
        cattleStage.setScene(cattleScene);
        cattleStage.show();
    }

    // Clear cattle input fields
    private void clearCattleFields(TextField tfBreed, TextField tfAge, TextField tfWeight, TextField tfVaccination) {
        tfBreed.clear();
        tfAge.clear();
        tfWeight.clear();
        tfVaccination.clear();
    }

    // Display the farmer's cattle details
    private void displayCattleDetails(Farmer farmer) {
        Stage viewStage = new Stage();
        viewStage.setTitle("Cattle Details");
    
        GridPane viewGrid = new GridPane();
        viewGrid.setHgap(10);
        viewGrid.setVgap(10);
    
        // Add header labels
        viewGrid.add(new Label("UID"), 0, 0);  // Adding UID column
        viewGrid.add(new Label("Breed"), 1, 0);
        viewGrid.add(new Label("Age"), 2, 0);
        viewGrid.add(new Label("Weight"), 3, 0);
        viewGrid.add(new Label("Vaccination Status"), 4, 0);
    
        int row = 1;  // Start from the second row
        for (Cattle cattle : farmer.getCattleList()) {
            viewGrid.add(new Label(String.valueOf(cattle.getUid())), 0, row);  // Displaying UID
            viewGrid.add(new Label(cattle.getBreed()), 1, row);
            viewGrid.add(new Label(String.valueOf(cattle.getAge())), 2, row);
            viewGrid.add(new Label(String.valueOf(cattle.getWeight())), 3, row);
            viewGrid.add(new Label(cattle.getVaccinationStatus()), 4, row);
            row++;
        }
    
        Scene viewScene = new Scene(viewGrid, 600, 300);  // Adjust width for the new column
        viewStage.setScene(viewScene);
        viewStage.show();
    }

    private String generateChecksum(String input) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hash = md.digest(input.getBytes());
            StringBuilder hexString = new StringBuilder();
    
            for (byte b : hash) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            return hexString.toString();
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
    
    

    // Show alert dialog
    private void showAlert(String title, String message) {
        Alert alert = new Alert(Alert.AlertType.INFORMATION);
        alert.setTitle(title);
        alert.setHeaderText(null);
        alert.setContentText(message);
        alert.showAndWait();
    }

    // Insurance Policy Management
    private void showInsurancePolicyManagement(Farmer farmer) {
        Stage insuranceStage = new Stage();
        insuranceStage.setTitle("Add Insurance Policies");
    
        GridPane insuranceGrid = new GridPane();
        insuranceGrid.setHgap(10);
        insuranceGrid.setVgap(10);
    
        // Input fields for insurance policy
        insuranceGrid.add(new Label("Breed:"), 0, 0);
        TextField tfInsuranceBreed = new TextField();
        insuranceGrid.add(tfInsuranceBreed, 1, 0);
    
        insuranceGrid.add(new Label("Age:"), 0, 1);
        TextField tfInsuranceAge = new TextField();
        insuranceGrid.add(tfInsuranceAge, 1, 1);
    
        insuranceGrid.add(new Label("Weight:"), 0, 2); // Adding weight for premium calculation
        TextField tfInsuranceWeight = new TextField();
        insuranceGrid.add(tfInsuranceWeight, 1, 2);
    
        insuranceGrid.add(new Label("Vaccination Status:"), 0, 3); // Additional cattle detail
        TextField tfVaccinationStatus = new TextField();
        insuranceGrid.add(tfVaccinationStatus, 1, 3);
    
        Button btnAddPolicy = new Button("Add Policy");
        insuranceGrid.add(btnAddPolicy, 1, 4);
    
        // Add policy button action
        btnAddPolicy.setOnAction(e -> {
            try {
                String breed = tfInsuranceBreed.getText();
                int age = Integer.parseInt(tfInsuranceAge.getText());
                double weight = Double.parseDouble(tfInsuranceWeight.getText());
                String vaccinationStatus = tfVaccinationStatus.getText();
    
                // Create Cattle object to calculate premium
                Cattle cattle = new Cattle(breed, age, weight, vaccinationStatus);
                double premium = InsurancePolicy.calculatePremium(cattle);
    
                InsurancePolicy policy = new InsurancePolicy(breed, age, premium);
                farmer.addInsurancePolicy(policy);
    
                showAlert("Policy Added", "Insurance policy added successfully with premium: " + premium);
                clearFields(tfInsuranceBreed, tfInsuranceAge, tfInsuranceWeight, tfVaccinationStatus);
            } catch (NumberFormatException ex) {
                showAlert("Input Error", "Please enter valid numbers for age and weight.");
            }
        });
    
        Scene insuranceScene = new Scene(insuranceGrid, 400, 250);
        insuranceStage.setScene(insuranceScene);
        insuranceStage.show();
    }

    private void clearFields(TextField... fields) {
        for (TextField field : fields) {
            field.clear();
        }
    }

    //claim status showing

    private void showClaimStatus(Farmer farmer) {
        Stage claimStatusStage = new Stage();
        claimStatusStage.setTitle("View Claim Status");
    
        GridPane claimGrid = new GridPane();
        claimGrid.setHgap(10);
        claimGrid.setVgap(10);
    
        // Add header labels
        claimGrid.add(new Label("Claim ID"), 0, 0);
        claimGrid.add(new Label("Cattle UID"), 1, 0);
        claimGrid.add(new Label("Claim Type"), 2, 0);
        claimGrid.add(new Label("Date of Occurrence"), 3, 0);
        claimGrid.add(new Label("Description"), 4, 0);
        claimGrid.add(new Label("Status"), 5, 0);
    
        int row = 1;
        for (Claim claim : farmer.getClaimsList()) {
            claimGrid.add(new Label(String.valueOf(claim.getClaimId())), 0, row);
            claimGrid.add(new Label(claim.getCattleUid()), 1, row);
            claimGrid.add(new Label(claim.getClaimType()), 2, row);
            claimGrid.add(new Label(claim.getDateOfOccurrence()), 3, row);
            claimGrid.add(new Label(claim.getDescription()), 4, row);
            claimGrid.add(new Label(claim.getStatus()), 5, row);
            row++;
        }
    
        Scene claimScene = new Scene(claimGrid, 600, 400);
        claimStatusStage.setScene(claimScene);
        claimStatusStage.show();
    }
    
    

    // Insurance Claim Process
    private void showClaimFiling(Farmer farmer) {
        Stage claimStage = new Stage();
        claimStage.setTitle("File Insurance Claim");
    
        GridPane claimGrid = new GridPane();
        claimGrid.setHgap(10);
        claimGrid.setVgap(10);
    
        // Input fields for filing a claim
        claimGrid.add(new Label("Cattle UID:"), 0, 0);
        TextField tfCattleUid = new TextField();
        claimGrid.add(tfCattleUid, 1, 0);
    
        claimGrid.add(new Label("Claim Type:"), 0, 1);
        TextField tfClaimType = new TextField();
        claimGrid.add(tfClaimType, 1, 1);
    
        claimGrid.add(new Label("Date of Occurrence:"), 0, 2);
        TextField tfDate = new TextField();
        claimGrid.add(tfDate, 1, 2);
    
        claimGrid.add(new Label("Description:"), 0, 3);
        TextField tfDescription = new TextField();
        claimGrid.add(tfDescription, 1, 3);
    
        Button btnSubmitClaim = new Button("Submit Claim");
        claimGrid.add(btnSubmitClaim, 1, 4);
    
        // Submit claim action
        btnSubmitClaim.setOnAction(e -> {
            try {
                String cattleUid = tfCattleUid.getText();
                String claimType = tfClaimType.getText();
                String dateOfOccurrence = tfDate.getText();
                String description = tfDescription.getText();
    
                int claimId = farmer.getClaimsList().size() + 1;
                Claim claim = new Claim(claimId, cattleUid, claimType, dateOfOccurrence, description);
                farmer.addClaim(claim);
    
                showAlert("Claim Submitted", "Your claim has been submitted for review.");
                claimStage.close();
            } catch (Exception ex) {
                showAlert("Error", "An error occurred while submitting your claim. Please check your inputs.");
            }
        });
    
        Scene claimScene = new Scene(claimGrid, 400, 250);
        claimStage.setScene(claimScene);
        claimStage.show();
    }    

    // View Insurance Policies
    // View Insurance Policies and Pay Premium
    private void showInsurancePolicies(Farmer farmer) {
        Stage policyStage = new Stage();
        policyStage.setTitle("View and Pay Insurance Policies");

        GridPane policyGrid = new GridPane();
        policyGrid.setHgap(10);
        policyGrid.setVgap(10);

        // Add header labels
        policyGrid.add(new Label("Breed"), 0, 0);
        policyGrid.add(new Label("Age"), 1, 0);
        policyGrid.add(new Label("Premium"), 2, 0);
        policyGrid.add(new Label("Status"), 3, 0);
        policyGrid.add(new Label("Action"), 4, 0);

        int row = 1;
        for (InsurancePolicy policy : farmer.getInsurancePolicies()) {
            policyGrid.add(new Label(policy.getBreed()), 0, row);
            policyGrid.add(new Label(String.valueOf(policy.getAge())), 1, row);
            policyGrid.add(new Label(String.valueOf(policy.getPremium())), 2, row);
            policyGrid.add(new Label(policy.getStatus()), 3, row);

            Button payButton = new Button("Pay");
            if (policy.getStatus().equals("Paid")) {
                payButton.setDisable(true);
            }
            payButton.setOnAction(e -> {
                // Logic to handle premium payment
                policy.setStatus("Paid");
                showAlert("Payment Successful", "The premium for the selected policy has been paid.");
                policyStage.close();
                showInsurancePolicies(farmer); // Refresh the view
            });
            policyGrid.add(payButton, 4, row);
            row++;
        }

        Scene policyScene = new Scene(policyGrid, 600, 400);
        policyStage.setScene(policyScene);
        policyStage.show();
    }
    


    // Farmer class
    public static class Farmer {
        private String farmerId;
        private String name;
        private String farmLocation;
        private String password;
        // private List<Cattle> cattleList;
        // private List<InsurancePolicy> insurancePolicies;
        // private List<InsuranceClaim> claims;

        private List<Cattle> cattleList = new ArrayList<>();
        private List<InsurancePolicy> insurancePolicies = new ArrayList<>();
        private List<Claim> claimsList = new ArrayList<>();

        public Farmer(String farmerId, String name, String farmLocation, String password) {
            this.farmerId = farmerId;
            this.name = name;
            this.farmLocation = farmLocation;
            this.password = password;
            this.cattleList = new ArrayList<>();
            this.insurancePolicies = new ArrayList<>();
            this.claimsList = new ArrayList<>();
        }

        public void addClaim(Claim claim) {
            claimsList.add(claim);
        }
    
        public List<Claim> getClaimsList() {
            return claimsList;
        }

        public String getFarmerId() {
            return farmerId;
        }

        public String getName() {
            return name;
        }

        public String getFarmLocation() {
            return farmLocation;
        }

        public String getPassword() {
            return password;
        }

        public List<Cattle> getCattleList() {
            return cattleList;
        }

        public void addCattle(Cattle cattle) {
            cattleList.add(cattle);
        }

        public List<InsurancePolicy> getInsurancePolicies() {
            return insurancePolicies;
        }

        public void addInsurancePolicy(InsurancePolicy policy) {
            insurancePolicies.add(policy);
        }
    }

    public class Admin {
        private String adminId;
        private String name;
        private String password;
    
        // Constructor
        public Admin(String adminId, String name, String password) {
            this.adminId = adminId;
            this.name = name;
            this.password = password;
        }
    
        // Getter for adminId
        public String getAdminId() {
            return adminId;
        }
    
        // Getter for name
        public String getName() {
            return name;
        }
    
        // Getter for password
        public String getPassword() {
            return password;
        }
    
        // Setter for password (optional, if admins can change their password)
        public void setPassword(String password) {
            this.password = password;
        }
    }
    

    // Cattle class
    public static class Cattle {

        private static int uidCounter = 0; // Static counter for generating UIDs
        private int uid;
        private String breed;
        private int age;
        private double weight;
        private String vaccinationStatus;

        public Cattle(String breed, int age, double weight, String vaccinationStatus) {
            this.uid = ++uidCounter;
            this.breed = breed;
            this.age = age;
            this.weight = weight;
            this.vaccinationStatus = vaccinationStatus;
        }

        public int getUid() {
            return uid;
        }

        public String getBreed() {
            return breed;
        }

        public int getAge() {
            return age;
        }

        public double getWeight() {
            return weight;
        }

        public String getVaccinationStatus() {
            return vaccinationStatus;
        }
    }

    // Insurance Policy class
    public class InsurancePolicy {
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
    
        // Premium calculation logic based on breed, age, etc.
        public static double calculatePremium(Cattle cattle) {
            double basePremium = 100.0; // Example base premium
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

    // Insurance Claim class
    public static class InsuranceClaim 
    {
        private String farmerId;
        private String details;
        private boolean approved;

        public InsuranceClaim(String farmerId, String details) {
            this.farmerId = farmerId;
            this.details = details;
            this.approved = false; // Default to not approved
        }

        public String getFarmerId() {
            return farmerId;
        }

        public String getDetails() {
            return details;
        }

        public boolean isApproved() {
            return approved;
        }

        public void approve() {
            this.approved = true;
        }
    }

    public class Claim {
        private int claimId;
        private String cattleUid;
        private String claimType;
        private String dateOfOccurrence;
        private String description;
        private String status;
    
        public Claim(int claimId, String cattleUid, String claimType, String dateOfOccurrence, String description) {
            this.claimId = claimId;
            this.cattleUid = cattleUid;
            this.claimType = claimType;
            this.dateOfOccurrence = dateOfOccurrence;
            this.description = description;
            this.status = "Pending Review";
        }
    
        // Getters and Setters
        public int getClaimId() { return claimId; }
        public String getCattleUid() { return cattleUid; }
        public String getClaimType() { return claimType; }
        public String getDateOfOccurrence() { return dateOfOccurrence; }
        public String getDescription() { return description; }
        public String getStatus() { return status; }
        public void setStatus(String status) { this.status = status; }
    }
    

    public void addInsurancePolicy(Farmer farmer, Cattle cattle) {
        double premium = InsurancePolicy.calculatePremium(cattle);
        InsurancePolicy policy = new InsurancePolicy(cattle.getBreed(), cattle.getAge(), premium);
        farmer.getInsurancePolicies().add(policy); // Assuming farmer has a method getInsurancePolicies()
    }
}
