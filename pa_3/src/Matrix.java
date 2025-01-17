/*
File: Matrix.java
Class: CMPS 101
Assignment: PA3
Student: Arseniy Khmelidze (akhmelid)
Date created: 02/04/17 
*/

// Class declaration
public class Matrix 
{
    private class Entry 
    {
        int column;
        double value;

        Entry(double value, int column) 
        {
            this.value = value;
            this.column = column;
        }

        public boolean equals(Object x) 
        {
            Entry element;
            boolean equals = false;
            
            if (x instanceof Entry) 
            {
            	element = (Entry) x;
                equals = (this.column == element.column && this.value == element.value);
            }
            return equals;
        }

        public String toString() 
        {
            return ("(" + String.valueOf(column) + ", " + String.valueOf(value) + ")");
        }
    }


    
    
    // Constructor
    private List[] row;
    private int NNZ;
    private int matrix_size;

    // Makes a new n x n zero Matrix
    Matrix(int n) 
    {
    	matrix_size = n;
        row = new List[n];
        
        for (int i = 0; i < n; i++) 
        {
            row[i] = new List();
        }
    }
    
    
    // Returns n, the number of rows and columns of this Matrix
    int getSize() 
    {
    	int size = (matrix_size);
        return size;
    }
    
    
    // Returns the number of non-zero entries in this Matrix
    int getNNZ() 
    {
        return NNZ;
    }
    
    
    // Supporting function: Getting matrix elements (i x j matrix)
    private int getEntry(int i, int j) 
    {
        if (i <= 0 || i > matrix_size || j <= 0 || j > matrix_size) 
        {
            return -1;
        }
        
        int index = -1;
        
        if (row[i - 1].length() != 0) 
        {
            row[i - 1].moveFront();
            
            Entry compare;
            
            while (row[i - 1].index() != -1) 
            {
                compare = (Entry) row[i - 1].get();
                
                if (compare.column == j) 
                {
                	index = row[j - 1].index();
                    break;
                }
                
                row[i - 1].moveNext();
            }
        }
        return index;
    }
    
    
    // Checking matrix equality by going through every element
    public boolean equals(Object x) 
    {
        Matrix M;
        boolean equal_M = false; // boolean to check equal matrices
        
        if (x instanceof Matrix) 
        {
            M = (Matrix) x;
            
            if (M.getNNZ() == NNZ && M.getSize() == matrix_size) 
            {
                for (int i = 0; i < matrix_size; i++) 
                {
                    if (row[i].length() != M.row[i].length())
                    {
                        return false;
                    }

                    row[i].moveFront();
                    M.row[i].moveFront();
                    
                    while (row[i].index() != -1) 
                    {
                        if (!(row[i].get().equals(M.row[i].get()))) 
                        {
                            return false;
                        }
                        
                        row[i].moveNext();
                        M.row[i].moveNext();
                    }
                }
                equal_M = true;
            }
        }
        return equal_M;
    }

    
    
    
    // Manipulation procedures
    
    // Sets this Matrix to the zero state
    void makeZero() 
    {
        if (matrix_size > 1)
        {
            for (int i = 0; i < matrix_size; i++) 
            {
                row[i].clear();
            }
        }
        
        NNZ = 0;
    }

    
    // Returns a new Matrix having the same entries as this Matrix
    Matrix copy() 
    {
        Matrix temp_M = new Matrix(matrix_size);
        
        for (int i = 0; i < matrix_size; i++) 
        {
            row[i].moveFront();
            
            while (row[i].index() != -1) 
            {
                Entry new_elem = new Entry(((Entry) row[i].get()).value, ((Entry) row[i].get()).column);
                
                temp_M.row[i].append(new_elem);
                temp_M.NNZ++;
                
                if (temp_M.NNZ == this.NNZ)
                {
                    return temp_M;
                }
                
                row[i].moveNext();
            }
        }
        return temp_M;
    }

    
    // Changes ith row, jth column of this Matrix to x
    void changeEntry(int i, int j, double x) 
    {
        if (i <= 0 || j <= 0 || i > matrix_size || j > matrix_size || matrix_size == 0) 
        {
            throw new RuntimeException("Error occured while processing changeEntry() method.");
        }
        
        double spliter = ( j / matrix_size );
        
        if (spliter < 0.5) 
        {
            for (row[i - 1].moveFront(); row[i - 1].index() != -1; row[i - 1].moveNext()) 
            {
                if (((Entry) row[i - 1].get()).column == j) 
                {
                    if (x == 0) 
                    {
                        boolean delete = false;
                        NNZ--;
                        
                        if (row[i - 1].front() == row[i - 1].get()) 
                        {
                            (row[i - 1]).deleteFront();
                            delete = true;
                        }
                        
                        if (row[i - 1].back() == row[i - 1].get()) 
                        {
                            (row[i - 1]).deleteBack();
                            delete = true;
                        }
                        
                        if (!delete) 
                        {
                            (row[i - 1]).delete();
                        }
                        return;
                    }
                    
                    ((Entry) row[i - 1].get()).value = x;
                    return;
                } 
                
                else if (((Entry) row[i - 1].get()).column > j) 
                {
                    if (x != 0) 
                    {
                    	Entry new_elem = new Entry(x, j);
                        row[i - 1].insertBefore(new_elem);
                        NNZ++;
                    }
                    return;
                }
            }
            
            if (x != 0) 
            {
                Entry new_elem = new Entry(x, j);
                row[i - 1].append(new_elem);
                NNZ++;
            }
            return;
        } 
        
        else 
        {
            for (row[i - 1].moveBack(); row[i - 1].index() != -1; row[i - 1].movePrev()) 
            {
                if (((Entry) row[i - 1].get()).column == j) 
                {
                    if (x == 0) 
                    {
                        boolean delete = false;
                        NNZ--;
                        
                        if (row[i - 1].front() == row[i - 1].get()) 
                        {
                            (row[i - 1]).deleteFront();
                            delete = true;
                        }
                        
                        if (row[i - 1].back() == row[i - 1].get()) 
                        {
                            (row[i - 1]).deleteBack();
                            delete = true;
                        }
                        
                        if (!delete) 
                        {
                            (row[i - 1]).delete();
                        }
                        return;
                    }
                    
                    ((Entry) row[i - 1].get()).value = x;
                    return;
                } 
                
                else if (((Entry) row[i - 1].get()).column < j) 
                {
                    if (x != 0) 
                    {
                        Entry new_elem = new Entry(x, j);
                        NNZ++;

                        if ((row[i - 1].get()) == (row[i - 1].back())) 
                        {
                            row[i - 1].append(new_elem);
                        } 
                        
                        else 
                        {

                            row[i - 1].insertAfter(new_elem);
                        }
                    }
                    return;
                }
            }
            
            if (x != 0) 
            {
                Entry new_elem = new Entry(x, j);
                
                row[i - 1].prepend(new_elem);
                NNZ++;
            }
            return;
        }
    }

    
    // Returns a new Matrix that is the scalar product of this Matrix with x
    Matrix scalarMult(double x) 
    {
        Matrix temp_M = new Matrix(matrix_size);
        
        for (int i = 0; i < matrix_size; i++) 
        {
            for (row[i].moveFront(); row[i].index() != -1; row[i].moveNext()) 
            {
                Entry new_elem = (Entry) row[i].get();
                
                temp_M.changeEntry(i + 1, new_elem.column, new_elem.value * x);
                
                if (temp_M.NNZ == NNZ) 
                {
                	return temp_M;
                }
            }
        }
        return temp_M;
    }

    
    // Returns a new Matrix that is the sum of this Matrix with M
    Matrix add(Matrix M) 
    {
        if (getSize() != M.getSize())
        {
            throw new RuntimeException("Exception thrown in add: Matrices must have the same size.");
        }
        
        if (M == this)
        {
            return this.copy().scalarMult(2.0);
        }
        
        Matrix A = new Matrix(getSize());
        
        for (int i = 0; i < getSize(); ++i) 
        {
            List L = new List();
            row[i].moveFront();
            M.row[i].moveFront();
            
            while (row[i].index() >= 0 || M.row[i].index() >= 0) 
            {
                if (row[i].index() >= 0 && M.row[i].index() >= 0) 
                {
                    Entry a = (Entry) row[i].get();
                    Entry b = (Entry) M.row[i].get();
                    
                    if (a.column > b.column) 
                    {
                        L.append(new Entry(b.value, b.column));
                        M.row[i].moveNext();
                    } 
                    
                    else if (a.column < b.column) 
                    {
                        L.append(new Entry(a.value, a.column));
                        row[i].moveNext();
                    } 
                    
                    else if (a.column == b.column) 
                    {
                        if ((a.value + b.value != 0))
                        {
                            L.append(new Entry(a.value + b.value, a.column));
                        }
                        
                        row[i].moveNext();
                        M.row[i].moveNext();
                    }
                } 
                
                else if (row[i].index() >= 0) 
                {
                    Entry a = (Entry) row[i].get();
                    
                    L.append(new Entry(a.value, a.column));
                    row[i].moveNext();
                } 
                
                else 
                {
                    Entry b = (Entry) M.row[i].get();
                    
                    L.append(new Entry((b.value), b.column));
                    M.row[i].moveNext();
                }
            }
            
            A.row[i] = L;
        }
        return A;
    }

    
    // Returns a new Matrix that is the difference of this Matrix with M
    Matrix sub(Matrix M) 
    {
        if (getSize() != M.getSize())
        {
            throw new RuntimeException("Exception thrown in sub: Matrices must have the same size.");
        }
        
        if (M == this) 
        {
            return new Matrix(getSize());
        }
        
        Matrix A = new Matrix(getSize());
        
        for (int i = 0; i < getSize(); ++i) 
        {
            List L = new List();
            row[i].moveFront();
            M.row[i].moveFront();
            
            while (row[i].index() >= 0 || M.row[i].index() >= 0) 
            {
                if (row[i].index() >= 0 && M.row[i].index() >= 0) 
                {
                    Entry a = (Entry) row[i].get();
                    Entry b = (Entry) M.row[i].get();
                    
                    if (a.column > b.column) 
                    {
                        L.append(new Entry(-b.value, b.column));
                        M.row[i].moveNext();
                    } 
                    
                    else if (a.column < b.column) 
                    {
                        L.append(new Entry(a.value, a.column));
                        row[i].moveNext();
                    } 
                    
                    else if (a.column == b.column) 
                    {
                        if ((a.value - b.value != 0))
                        {
                            L.append(new Entry((a.value - b.value), a.column));
                        }
                        
                        row[i].moveNext();
                        M.row[i].moveNext();
                    }
                } 
                
                else if (row[i].index() >= 0) 
                {
                    Entry a = (Entry) row[i].get();
                    
                    L.append(new Entry(a.value, a.column));
                    row[i].moveNext();
                } 
                
                else 
                {
                    Entry b = (Entry) M.row[i].get();
                    
                    L.append(new Entry((-b.value), b.column));
                    M.row[i].moveNext();
                }
            }
            A.row[i] = L;
        }
        return A;
    }

    
    // Returns a new Matrix that is the transpose of this Matrix
    Matrix transpose() 
    {
        Matrix M = new Matrix(matrix_size);
        
        for (int i = 0; i < matrix_size; i++) 
        {
            for (row[i].moveFront(); row[i].index() != -1; row[i].moveNext()) 
            {
                Entry new_elem = (Entry) row[i].get();
                int new_column = new_elem.column;
                M.changeEntry(new_column, i + 1, new_elem.value);
            }
        }
        return M;
    }

    
    // Returns a new Matrix that is the product of this Matrix with M
    Matrix mult(Matrix M) 
    {
        if (getSize() != M.getSize())
        {
            throw new RuntimeException("Exception thrown in mult: Matrices can have different sizes.");
        }
        
        Matrix A = new Matrix(getSize());
        Matrix B = M.transpose();
        
        for (int i = 0; i < getSize(); i++) 
        {
            if (row[i].length() == 0) 
            {
            	continue;
            }
            
            for (int j = 0; j < getSize(); j++) 
            {
                if (B.row[j].length() == 0) continue;
                A.changeEntry(i + 1, j + 1, dot(row[i], B.row[j]));
            }
        }
        return A;
    }
    

    
    
    // Other functions
    
    // overrides Object's toString() method
    public String toString() 
    {
        String s = "";
        
        for (int i = 0; i < matrix_size; i++) 
        {
            if (row[i].length() == 0) 
            {
                continue;
            }
            
            s = s + (i + 1) + ":" + row[i].toString() + "\n";
        }
        return s;
    }
    
    
    
    
    // Suggested supporting functions
    
    // Dot product between the two matrices
    private static double dot(List P, List Q) 
    {
        double result = 0;
        
        for (P.moveFront(); P.index() != -1; P.moveNext()) 
        {
            Entry elem_P = (Entry) P.get();
            
            for (Q.moveFront(); Q.index() != -1; Q.moveNext()) 
            {
                Entry elem_Q = (Entry) Q.get();
                
                if (elem_P.column == elem_Q.column) 
                {
                	result += elem_P.value * elem_Q.value;
                    break;
                }
            }
        }
        return result;
    }
}
