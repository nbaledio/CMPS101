import java.io.*;
import java.util.Scanner;

public class Sparse{
	public static void main (String[]args) throws IOException{
		//Creates Reader/Writes for File I/O
		Scanner reader = new Scanner(new File(args[0]));
		PrintWriter out = new PrintWriter(new FileWriter(args[1]));
		
		//Scan inputs for matrix size and Non-Zero Entries
		int size = reader.nextInt();
		int A_NNZ = reader.nextInt();
		int B_NNZ = reader.nextInt();
		Matrix A = new Matrix(size);
		Matrix B = new Matrix(size);
		
		//Add values to Matrix A
		for(int i = 0; i < A_NNZ; i++){
			int row = reader.nextInt();
			int column = reader.nextInt();
			double value = reader.nextDouble();
			A.changeEntry(row-1,column,value);
		}
		
		//Add values to Matrix B
		for(int i = 0; i < B_NNZ; i++){
			int row = reader.nextInt();
			int column = reader.nextInt();
			double value = reader.nextDouble();
			B.changeEntry(row-1,column,value);
		}
		
		//Performs set Matrix operations and writes them to the outfile
		out.println("A has " + A_NNZ + " non-zero entries: \n");
		out.println(A.toString());
		out.println("B has " + B_NNZ + " non-zero entries: \n");
		out.println(B.toString());
		out.println("(1.5)*A =\n");
		out.println(A.scalarMult(1.5).toString());
		out.println("A+B =\n");
		out.println(A.add(B).toString());
		out.println("A+A =\n");
		out.println(A.add(A).toString());
		out.println("B-A =\n");
		out.println(B.sub(A).toString());
		out.println("A-A =\n");
		out.print(A.sub(A).toString());
		out.println("Transpose(A) =\n");
		out.println(A.transpose().toString());
		out.println("A*B =\n");
		out.println(A.mult(B).toString());
		out.println("B*B =\n");
		out.println(B.mult(B).toString());
		
		//Closes files
		reader.close();
		out.close();
		
		
		
		
	}
}