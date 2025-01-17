/*
File: MatrixTest.java
Class: CMPS 101
Assignment: PA3
Student: Arseniy Khmelidze (akhmelid)
Date created: 02/04/17 
*/

public class MatrixTest 
{
    public static void main(String[] args) 
    {
        int matrix_size = 20;
        Matrix A = new Matrix(matrix_size);
        Matrix B = new Matrix(matrix_size);

        for(int i = 1; i <= matrix_size; i++)
        {
            for(int j = 1; j <= matrix_size; j++)
            {
                A.changeEntry(i, j, matrix_size - j);
                B.changeEntry(i, j, j);
            }
        }
        
        
        System.out.println("Testing the results based on the algorithm: ");
        System.out.println();
        System.out.println("Total # of elements in Matrix A: " + A.getNNZ());
        System.out.println(A);
        
        System.out.println("Total # of elements in Matrix B: " + B.getNNZ());
        System.out.println(B);
        
        System.out.println("A + A =");
        System.out.println(A.add(A));
        
        System.out.println("A - A =");
        System.out.print(A.sub(A));
        System.out.println("(If there is nothing, then the results is correct - it has zero elements)");
        System.out.println();
        
        System.out.println("1.5 * A =");
        System.out.println(A.scalarMult(1.5));
        
        System.out.println("Transpose of Matrix A =");
        System.out.println(A.transpose());
        
        System.out.println("A + B =");
        System.out.println(A.add(B));
        
        System.out.println("B - A =");
        System.out.println(B.sub(A));
        
        System.out.println("A * B =");
        System.out.println(A.mult(B));
        
        System.out.println("B * B =");
        System.out.println(B.mult(B));

        System.out.println("Assume Matrix C is a copy of A. ");
        Matrix C = A.copy();
        
        System.out.println("Total # of elements in Matrix C: " + C.getNNZ());
        System.out.println(C);
        
        System.out.print("A = C? ");
        System.out.println(A.equals(C));
        
        System.out.print("A = B? ");
        System.out.println(A.equals(B));
        
        System.out.print("A = A? ");
        System.out.println(A.equals(A));
        System.out.println();
        
        System.out.println("-------------------------- Clearing Matrix C --------------------------");
        C.makeZero();
        System.out.println("Total # of elements in cleared Matrix C: " + C.getNNZ());
        System.out.println("Matrix C looks as the following: " + C);
    }
}
