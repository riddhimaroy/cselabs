package com.example.demo;

import javafx.application.*;
import javafx.scene.*;
import javafx.stage.*;
import javafx.scene.layout.*;
import javafx.scene.control.*;
import javafx.event.*;
import javafx.geometry.*;
import javafx.scene.shape.*;
import javafx.scene.canvas.*;
import javafx.scene.paint.*;
import javafx.scene.text.*;
import javafx.collections.*;
import javafx.beans.value.*;

public class hello extends Application
{

    GraphicsContext gc;
    ToggleButton tgl;
    CheckBox c1, c2, c3;
    Color[] colors = {Color.RED, Color.BLUE, Color.GREEN, Color.BLACK};
    int coloridx = 0;
    Label selected;
    TextField tf;
    ComboBox<String> c;
    public static void main(String[] args)
    {
        launch(args);
    }

    void showAll() 
    {
        String computers = "";
        if(c1.isSelected())
        computers = "Smartphone ";
        if(c2.isSelected())
        computers += "Tablet ";
        if(c3.isSelected())
        computers += "Notebook ";
        
        selected.setText("Computers selected: " + computers);
    }
        

    public void start(Stage myStage)
    {
        myStage.setTitle("lmao");

        FlowPane rootNode = new FlowPane(30, 30);
        Scene myScene = new Scene(rootNode, 400,400);
        rootNode.setAlignment(Pos.CENTER);
        myStage.setScene(myScene);

        Canvas myCanvas = new Canvas(100,100);
        gc = myCanvas.getGraphicsContext2D();
        Label myLabel = new Label("lolzies");
        Label response = new Label("press lol");
        selected = new Label("");

        myLabel.setTextFill(Color.MAGENTA);
        
        ObservableList<String> types = FXCollections.observableArrayList("c", "b", "no");

        c = new ComboBox<String>(types);
        c.setValue("pick me");

        //normal button

        Button x = new Button("lol");

        x.setOnAction(new EventHandler<ActionEvent>()
        {
            public void handle(ActionEvent ae)
            {
                gc.setStroke(colors[coloridx]);
                gc.setFill(colors[coloridx]);
                gc.fillRect(20,30, 10, 10);
                coloridx++;
                //gc.setFont(new Font(30));
                gc.fillText("lol", 10, 10);

                if(coloridx==colors.length)
                coloridx = 0;
            }
        }
        );

        //toggle button
        tgl = new ToggleButton("lol/no lol");
        tgl.setOnAction((new EventHandler <ActionEvent>()
        {
            public void handle(ActionEvent ae)
            {
                if(tgl.isSelected())
                    response.setText("lololololol");
                else
                    response.setText(":c");
            }
        }));

        //radio button

        RadioButton rad = new RadioButton("rad");
        RadioButton rad1 = new RadioButton("radiohead");
        ToggleGroup tg = new ToggleGroup();

        rad.setToggleGroup(tg);
        rad1.setToggleGroup(tg);

        rad.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent ae) {
            response.setText("Transport selected is train.");
            }
        });
        rad1.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent ae) {
            response.setText("Transport selected is car.");
            }
        });

        //checkbox

        c1 = new CheckBox("lol 1");
        c2 = new CheckBox("lol 2");
        c3 = new CheckBox("lol 3");

        c1.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent ae) {

                if(c1.isSelected())
                    response.setText("Smartphone was just selected.");
                else
                    response.setText("Smartphone was just cleared.");
                showAll();
                } });

        c2.setOnAction(new EventHandler<ActionEvent>() {
                public void handle(ActionEvent ae) {
                    if(c2.isSelected())
                         response.setText("Tablet was just selected.");
                    else
                         response.setText("Tablet was just cleared.");
                    showAll();
            }
        });
        c3.setOnAction(new EventHandler<ActionEvent>() {
        public void handle(ActionEvent ae) {
        if(c3.isSelected())
        response.setText("Notebook was just selected.");
        else
        response.setText("Notebook was just cleared.");
        showAll();
        }
        });

        tf = new TextField();

        tf.setPromptText(("enter lol"));
        tf.setPrefColumnCount(15);
        Label tff = new Label("");

        tf.setOnAction(new EventHandler<ActionEvent>() {
            public void handle(ActionEvent ae)
            {
                tff.setText("String: " + tf.getText());
            }
        });
        

        //listview

        ListView<String> li = new ListView<String>(types);

        li.setPrefSize(100, 70);

        MultipleSelectionModel<String>lvmod = li.getSelectionModel();

        lvmod.selectedItemProperty().addListener(new ChangeListener<String>()
        {
            public void changed(ObservableValue<? extends String> changed, String old, String newd)
            {
                tff.setText("yo " + newd);
            }
        });

        rootNode.getChildren().add(myCanvas);
            
        rootNode.getChildren().addAll(rad, rad1, c , x, tgl, myLabel, response, c1, c2, c3, selected, tf, tff, li);

        myStage.show();
        showAll();
    }
}

/*
 
ListView <String> li = new ListView<String> (types);

MultipleSelectionModel<String> lim = li.getSelectionModel();

lim.selectedItemProperty().addListener(new ChangeListener()
{
public void changed(ObservableValue<? extends String> changed, String old, String new)
{

}
})

 */