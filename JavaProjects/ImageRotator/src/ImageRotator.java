import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

import static java.awt.image.BufferedImage.TYPE_INT_RGB;

public class ImageRotator {

    private int[][] extendMtrx(int[][] matrix) {
        int height = matrix.length;
        int width = matrix[0].length;
        int maxDim = Math.max(height, width);
        int[][] extended = new int[maxDim][maxDim];

        for (int i = 0; i < height; ++i)
            for (int j = 0; j < width; ++j)
                extended[i][j] = matrix[i][j];

        return extended;
    }

    private int[][] cutMatrix(int[][] matrix, int height, int width) {
        int[][] cutted = new int[height][width];

        if (height > width) {
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    cutted[i][j] = matrix[i][j + matrix[0].length - width];
        }

        if (height < width) {
            for (int i = 0; i < height; ++i)
                for (int j = 0; j < width; ++j)
                    cutted[i][j] = matrix[i][j];
        }

        return cutted;
    }

    private int[][] intArrayFromImage(BufferedImage bufferedImage) {
        int width = bufferedImage.getWidth(null);
        int height = bufferedImage.getHeight(null);
        int[][] arrImage = new int[width][height];

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                arrImage[i][j] = bufferedImage.getRGB(i, j);
            }
        }

        return arrImage;
    }

    private BufferedImage imageFromIntArray(int[][] matrix) {
        BufferedImage image = new BufferedImage(matrix.length, matrix[0].length, TYPE_INT_RGB);
        for (int i = 0; i < matrix.length; i++) {
            for (int j = 0; j < matrix[0].length; j++) {
                int intColor = matrix[i][j];
                Color newColor = new Color(intColor, true);
                image.setRGB(i, j, newColor.getRGB());
            }
        }
        return image;
    }

    private void rotateSquareMatrix(int[][] matrix) {
        int N = matrix.length - 1;
        int k1 = N / 2;
        int k2 = (N % 2 == 0) ? N / 2 - 1 : N / 2;

        for (int i = 0; i <= k1; ++i) {
            for (int j = 0; j <= k2; ++j) {
                int topLeft = matrix[i][j];
                int topRight = matrix[j][N - i];
                int botRigth = matrix[N - i][N - j];
                int botLeft = matrix[N - j][i];

                matrix[j][N - i] = topLeft;
                matrix[N - i][N - j] = topRight;
                matrix[N - j][i] = botRigth;
                matrix[i][j] = botLeft;
            }
        }
    }

    private int[][] rotateMatrix(int[][] matrix) {
        int height = matrix.length;
        int width = matrix[0].length;
        int[][] squareMatrix = (height == width) ? matrix : extendMtrx(matrix);

        rotateSquareMatrix(squareMatrix);

        return (height == width) ? squareMatrix : cutMatrix(squareMatrix, width, height);
    }

    public BufferedImage rotate(BufferedImage image) {
        int[][] arrImage = intArrayFromImage(image);
        int[][] rotatedArray = rotateMatrix(arrImage);

        return imageFromIntArray(rotatedArray);
    }
}
