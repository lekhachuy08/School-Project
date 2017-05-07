package pingpong;

import javax.swing.*;
import java.awt.*;
import java.awt.geom.AffineTransform;
import java.awt.image.*;
import java.io.File;
import java.io.IOException;
import java.util.*;
import javax.imageio.ImageIO;

class Mainframe extends JFrame {

    private static final int WIDTH = 640;
    private static final int HEIGHT = 480;

    private int x = 1;
    private int y = 1;

    private int a = 1;
    private int b = 1;

    private final java.util.List<Integer> xPos = new ArrayList<Integer>();
    private final java.util.List<Integer> yPos = new ArrayList<Integer>();

    private BufferedImage ball;

    Mainframe() {
        try {
            ball = ImageIO.read(new File("puck.jpeg"));
            ball = resize(ball, 80, 80);
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Image not found.");
            System.exit(-1);
        }

        setSize(WIDTH, HEIGHT);
        setResizable(false);
        setTitle("Ping Pong");
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
    }

    void showPuck() {
        x += a;
        y += b;
        repaint();
        if (x < WIDTH) {
            x = -x;
        }
        if (y < HEIGHT) {
            y = -x;
        }
    }


    public static BufferedImage resize(BufferedImage ball, int width, int height) {
        int w = ball.getWidth();
        int h = ball.getHeight();
        BufferedImage dimg = new BufferedImage(width, height, ball.getType());
        Graphics2D g =  dimg.createGraphics();
        g.addRenderingHints(new RenderingHints(RenderingHints.KEY_RENDERING, RenderingHints.VALUE_RENDER_QUALITY));
        g.drawImage(ball, 0, 0, width, height, null);
        g.dispose();
        return dimg;
    }

    @Override
    synchronized public void paint(Graphics g) {
        g.clearRect(0, 0, WIDTH, HEIGHT);

        g.drawImage(ball, x, y, null);
    }
}
