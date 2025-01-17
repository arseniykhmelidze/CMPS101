/*
File: Sparse.java
Class: CMPS 101
Assignment: PA3
Student: Arseniy Khmelidze (akhmelid)
Date created: 02/04/17 
*/

import java.io.*;
import java.util.Scanner;

public class Sparse 
{

    public static void main(String[] args) throws IOException 
    {

        if (args.length != 2)
        {
            System.err.println("Two arguments are required in order to proceed. Provide an input and an output filename");
        }

        String inFileName = String.format("%s",args[0]);
        String outFileName = String.format("%s",args[1]);

        Scanner inFile = new Scanner(new File(inFileName));

        int matrix_size = inFile.nextInt();
        Matrix A = new Matrix(matrix_size);
        Matrix B = new Matrix(matrix_size);
        int NNZ_A = inFile.nextInt();
        int NNZ_B = inFile.nextInt();

        while (inFile.hasNext())
        {
            for(int i = 0; i < NNZ_A; i++)
            {
                int row = inFile.nextInt();
                int col = inFile.nextInt();
                double val = inFile.nextDouble();
                A.changeEntry(row,col,val);
            }

            for(int i = 0; i < NNZ_B; i++)
            {
                int row = inFile.nextInt();
                int col = inFile.nextInt();
                double val = inFile.nextDouble();
                B.changeEntry(row,col,val);
            }

        }

        PrintWriter outFile = new PrintWriter(outFileName);
        
        outFile.println("Received data");
        outFile.println();
        
        outFile.println("Total # of elements in Matrix A: " + NNZ_A);
        outFile.println(A);
        
        outFile.println("Total # of elements in Matrix B: " + NNZ_B);
        outFile.println(B);
        
        outFile.println("A + A =");
        outFile.println(A.add(A));
        
        outFile.println("A - A =");
        outFile.println(A.sub(A));
        
        outFile.println("1.5 * A =");
        outFile.println(A.scalarMult(1.5));
        
        outFile.println("Transpose of Matrix A =");
        outFile.println(A.transpose());
        
        outFile.println("A + B =");
        outFile.println(A.add(B));

        outFile.println("B - A =");
        outFile.println(B.sub(A));

        outFile.println("A * B =");
        outFile.println(A.mult(B));
        
        outFile.println("B * B =");
        outFile.println(B.mult(B));
        
        outFile.close();
    }
}
