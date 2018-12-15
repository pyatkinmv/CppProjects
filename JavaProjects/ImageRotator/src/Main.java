import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Main {
    public static void main(String[] args) {
        File fileImage = new File("image.jpg");
        try {
            BufferedImage image = ImageIO.read(fileImage);
            ImageRotator rotator = new ImageRotator();
            BufferedImage rotatedImage = rotator.rotate(image, true);
            File output = new File("result_image.jpg");
            ImageIO.write(rotatedImage, "jpg", output);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
