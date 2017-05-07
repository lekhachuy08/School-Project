package cockroach;

import javax.imageio.ImageIO;
import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.*;
import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

class MainFrame extends JFrame {
    private static final int WIDTH = 640;
    private static final int HEIGHT = 480;

    private BufferedImage live, dead;

    private final List<Integer> xPos = new ArrayList<Integer>();
    private final List<Integer> yPos = new ArrayList<Integer>();

    private int x;
    private int y;

    MainFrame() {
        try {
            live = ImageIO.read(new File("live.jpg"));
            live = ImageToBufferedImage(transformGrayToTransparency(live), live.getWidth(), live.getHeight());
            dead = ImageIO.read(new File("dead.jpg"));
            dead = resize(dead, live.getWidth(), live.getHeight());
            dead = ImageToBufferedImage(transformGrayToTransparency(dead), dead.getWidth(), dead.getHeight());
        } catch (IOException e) {
            JOptionPane.showMessageDialog(this, "Image not found.");
            System.exit(-1);
        }

        setSize(WIDTH, HEIGHT);
        setResizable(false);
        setTitle("Cockroach");
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);

        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                xPos.add(x);
                yPos.add(y);
            }
        });
    }

    void showCockroach() {
        x = (int) (Math.random() * WIDTH);
        y = (int) (Math.random() * HEIGHT);
        repaint();
    }

    private Image transformGrayToTransparency(BufferedImage image)
    {
        ImageFilter filter = new RGBImageFilter()
        {
            @Override
            public final int filterRGB(int x, int y, int rgb)
            {
                //System.out.println(isWhite(0x00FaFbFc));
                if (isBackground(rgb)) {
                    return 0x00FFFFFF;
                } else {
                    return rgb;
                }
            }

            private boolean isBackground(int rgb) {
//                int r = (rgb & 0x00FF0000) >> 16;
//                int g = (rgb & 0x0000FF00) >> 8;
//                int b = (rgb & 0x000000FF);
//                return (r == g && g == b);
                return ((rgb & 0x00FF0000) >= 0x00FA0000);
            }
        };

        ImageProducer ip = new FilteredImageSource(image.getSource(), filter);
        return Toolkit.getDefaultToolkit().createImage(ip);
    }

    private BufferedImage ImageToBufferedImage(Image image, int width, int height)
    {
        BufferedImage dest = new BufferedImage(
                width, height, BufferedImage.TYPE_INT_ARGB);
        Graphics2D g2 = dest.createGraphics();
        g2.drawImage(image, 0, 0, null);
        g2.dispose();
        return dest;
    }

    public BufferedImage resize(BufferedImage img, int newW, int newH) {
        int w = img.getWidth();
        int h = img.getHeight();
        BufferedImage dimg = new BufferedImage(newW, newH, img.getType());
        Graphics2D g = dimg.createGraphics();
        g.setRenderingHint(RenderingHints.KEY_INTERPOLATION,
                RenderingHints.VALUE_INTERPOLATION_BILINEAR);
        g.drawImage(img, 0, 0, newW, newH, 0, 0, w, h, null);
        g.dispose();
        return dimg;
    }

    @Override
    synchronized public void paint(Graphics g) {
        g.clearRect(0, 0, WIDTH, HEIGHT);

        for (int i = 0; i < xPos.size() - 1; i++) {
            int x = xPos.get(i);
            int y = yPos.get(i);
            g.drawImage(dead, x, y, null);
        }

        g.drawImage(live, x, y, null);
    }
}
