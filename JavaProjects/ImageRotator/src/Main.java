import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class Main {

    public static void print(int[][] matrix) {
        int height = matrix.length;
        int width = matrix[0].length;

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                System.out.print(String.format("%3d ", matrix[i][j]));
            }
            System.out.println();
        }
    }

    public static int[][] createMatrix(int height, int width) {
        int[][] matrix = new int[height][width];
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                matrix[i][j] = i * height + j;
            }
        }
        return matrix;
    }

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
