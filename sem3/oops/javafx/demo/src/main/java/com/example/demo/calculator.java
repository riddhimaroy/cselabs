package com.example.demo;

import javafx.application.*;
import javafx.stage.*;
import javafx.scene.*;
import javafx.scene.layout.*;
import javafx.event.*;
import javafx.geometry.*;
import javafx.scene.control.*;

public class calculator extends Application {

    Label n1, n2;
    TextField t1, t2;
    Button b1, b2, b3, b4;
    Label l1;
    public static void main(String[] args)
    {
        launch(args);
    }

    public void start (Stage myStage)
    {
        myStage.setTitle("calculator");
        GridPane grid = new GridPane();
        Scene myScene = new Scene(grid, 300, 200);
        myStage.setScene(myScene);
        grid.setHgap(10);
        grid.setVgap(10);

        n1 = new Label("Enter first number:");
        n2 = new Label("Enter second number:");
        t1 = new TextField();
        t2 = new TextField();

        t1.setPromptText("first number");
        t2.setPromptText("second number");

        b1 = new Button("+");
        b2 = new Button("-");
        b3 = new Button("*");
        b4 = new Button("/");

        l1 = new Label("");

        grid.add(n1, 2, 0);
        grid.add(n2, 2, 1);
        grid.add(t1, 3, 0);
        grid.add(t2, 3, 1);
        grid.add(b1, 1, 3);
        grid.add(b2, 2, 3);
        grid.add(b3, 3, 3);
        grid.add(b4, 4, 3);
        grid.add(l1, 1, 4);

        b1.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent ae)
            {
                int a = Integer.parseInt(t1.getText());
                int b = Integer.parseInt(t2.getText());

                int n = a+b;

                l1.setText("Sum: " + n);

            }
        });

        b3.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent ae)
            {
                int a = Integer.parseInt(t1.getText());
                int b = Integer.parseInt(t2.getText());

                int n = a*b;

                l1.setText("Product: " + n);

            }
        });

        myStage.show();
    }
}
