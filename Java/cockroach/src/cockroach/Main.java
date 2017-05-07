package cockroach;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Main {
    public static void main(String[] args) {
        final MainFrame mainFrame = new MainFrame();

        Timer timer = new Timer(1500, new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                mainFrame.showCockroach();
            }
        });
        timer.start();
    }
}
