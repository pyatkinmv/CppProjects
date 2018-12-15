import java.awt.*;
import java.awt.image.BufferedImage;

import static java.awt.image.BufferedImage.TYPE_INT_RGB;

public class ImageRotator {

    private int[][] intArrayFromImage(BufferedImage bufferedImage) {
        int width = bufferedImage.getWidth();
        int height = bufferedImage.getHeight();
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

    private void rotateSquareMatrix(int[][] matrix, boolean clockwise) {
        int N = matrix.length - 1;
        int k1 = N / 2;
        int k2 = (N % 2 == 0) ? N / 2 - 1 : N / 2;

        for (int i = 0; i <= k1; ++i) {
            for (int j = 0; j <= k2; ++j) {
                shift(matrix, i, j, clockwise);
            }
        }
    }

    private void shift(int[][] matrix, int i, int j, boolean clockwise) {
        int N = matrix.length - 1;

        int topLeft = matrix[i][j];
        int topRight = matrix[j][N - i];
        int botRigth = matrix[N - i][N - j];
        int botLeft = matrix[N - j][i];

        matrix[j][N - i] = clockwise ? topLeft : botRigth;
        matrix[N - i][N - j] = clockwise ? topRight : botLeft;
        matrix[N - j][i] = clockwise ? botRigth : topLeft;
        matrix[i][j] = clockwise ? botLeft : topRight;
    }

    private int[][] rotateMatrix(int[][] matrix, boolean clockwise) {
        int height = matrix.length;
        int width = matrix[0].length;
        int[][] rotated = new int[width][height];

        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) {
                if (clockwise) {
                    rotated[width - j - 1][i] = matrix[i][j];
                } else {
                    rotated[j][height - i - 1] = matrix[i][j];
                }
            }
        }
        return rotated;
    }

    public BufferedImage rotate(BufferedImage image, boolean clockwise) {
        int[][] arrImage = intArrayFromImage(image);

        int[][] rotatedArray;
        if (arrImage.length == arrImage[0].length) {
            rotateSquareMatrix(arrImage, clockwise);
            rotatedArray = arrImage;
        } else {
            rotatedArray = rotateMatrix(arrImage, clockwise);
        }
        return imageFromIntArray(rotatedArray);
    }
}

