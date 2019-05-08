public class Matrix{
	
	//Fields
	List[] matrix;
	int size = 0;
	int NNZ = 0;

	//Private Class for matrix_entry object. Holds column and data values to be passed to list
	private class matrix_entry{
		int column;
		double value;
		matrix_entry(int column, double value){
		  this.column = column;
		  this.value = value;
		}
	}

	// Constructor
	Matrix(int n){			// Makes a new n x n zero Matrix. pre: n>=1
		matrix = new List[n];
		for(int i = 0; i < n; i++){
			matrix[i] = new List();
		}
		this.size = n;
	}

	// Access functions
	int getSize(){ 			// Returns n, the number of rows and columns of this Matrix
		return size;
	}
	
	int getNNZ(){ 			// Returns the number of non-zero entries in this Matrix
		return NNZ;
	}
	
	public boolean equals(Object x){ // overrides Object's equals() method
		Matrix B = (Matrix) x;
		if(getSize() != B.getSize()){
			return false;
		}
		//Check if they are the same reference. This prevents a null pointer exception when value comparisons are run
		if(B.matrix == matrix){
			return true;
		}
		for(int i = 0; i < size; i++){
			if(matrix[i].length() != B.matrix[i].length()){
				return false;
			}
			matrix[i].moveFront();
			B.matrix[i].moveFront();
			for(int j = 0; j < matrix[i].length();j++){
				matrix_entry current = (matrix_entry) matrix[i].get();
				matrix_entry current2 = (matrix_entry) B.matrix[i].get();
				if(current.column != current2.column || current.value != current2.value){
					return false;
				}
				matrix[i].moveNext();
				B.matrix[i].moveNext();	
			}
		}
		return true;
	}

	// Manipulation procedures
	void makeZero(){ 			// sets this Matrix to the zero state
		for(int i = 0; i < size; i++){
			matrix[i].clear();
		}
	}

	Matrix copy(){				// returns a new Matrix having the same entries as this Matrix
		Matrix matrix_copy = new Matrix(size);
		for(int i = 0; i < size; i++){
			matrix[i].moveFront();
			for(int j = 0; j < matrix[i].length();j++){
				matrix_copy.matrix[i].append(matrix[i].get());
				matrix[i].moveNext();
			}
		}
		return matrix_copy;
	}

	void changeEntry(int i, int j, double x){ // changes ith row, jth column of this Matrix to x
		matrix[i].moveFront();
		for(int k = 0; k < matrix[i].length(); k++){
			matrix_entry current = (matrix_entry) matrix[i].get();
			if(current.column == j){
				//System.out.println("replace");
				current.value = x;
				matrix[i-1].insertBefore(current);
				matrix[i-1].delete();
				NNZ++;
				return;
			}
			matrix[i].moveNext();
		}
		matrix_entry new_element = new matrix_entry(j,x);
		if(matrix[i].length() == 0){
			//System.out.println("append");
			matrix[i].append(new_element);
			NNZ++;
			return;
		}
		matrix[i].moveFront();
		for(int k = 0; k < matrix[i].length(); k++){
			matrix_entry current = (matrix_entry) matrix[i].get();
			if(j < current.column){
				//System.out.println("insert");
				matrix[i].insertBefore(new_element);
				NNZ++;
				return;
			}
			matrix[i].moveNext();
		}
		NNZ++;
		matrix[i].append(new_element);
	}
	
	Matrix scalarMult(double x){ 				// returns a new Matrix that is the scalar product of this Matrix with x
		Matrix scalar_Mult = new Matrix(size);
		for(int i = 0; i < size; i++){
			matrix[i].moveFront();
			for(int j = 0; j < matrix[i].length();j++){
				matrix_entry current = (matrix_entry)matrix[i].get();
				if(current.value * x != 0){
					scalar_Mult.changeEntry(i,current.column,current.value*x);
				}
				matrix[i].moveNext();
			}
		}
		return scalar_Mult;
	}


	Matrix add(Matrix M){						// returns a new Matrix that is the sum of this Matrix with M
		Matrix addition = new Matrix(size);		// pre: getSize()==M.getSize()
		//Checks if M and this Matrix are the same reference and multiplies by 2 if true
		if(matrix == M.matrix){
			addition = scalarMult(2.0);
			return addition;
		}
		for(int i = 0; i < size; i++){
			matrix[i].moveFront();
			M.matrix[i].moveFront();
			while(matrix[i].index() != -1 && M.matrix[i].index() != -1){
				matrix_entry current = (matrix_entry)matrix[i].get();
				matrix_entry current2 = (matrix_entry)M.matrix[i].get();
				if(current.column > current2.column){
					addition.changeEntry(i,current2.column,current2.value);
					M.matrix[i].moveNext();
				}else if(current.column < current2.column){
					addition.changeEntry(i,current.column,current.value);
					matrix[i].moveNext();
				}else if(current.column == current2.column){
					if(current.value + current2.value != 0){
						addition.changeEntry(i,current.column,current.value + current2.value);
					}
					matrix[i].moveNext();
					M.matrix[i].moveNext();	
				}
			}
			if(matrix[i].index() == -1){
				add_fill(addition,M.matrix[i],i);
			}else{
				add_fill(addition,matrix[i],i);
			}
		}
		return addition;
	}
	//Helper function for add to fill in the rest of the row
	void add_fill(Matrix A, List B, int row){
		while(B.index() != -1){
			matrix_entry current = (matrix_entry)B.get();
			A.changeEntry(row,current.column,current.value);
			B.moveNext();
		}
	}
 

	Matrix sub(Matrix M){						// returns a new Matrix that is the difference of this Matrix with M
		Matrix subtraction = new Matrix(size);	// pre: getSize()==M.getSize()
		if(matrix == M.matrix){
			subtraction = scalarMult(0);
			return subtraction;
		}
		for(int i = 0; i < size; i++){
			matrix[i].moveFront();
			M.matrix[i].moveFront();
			while(matrix[i].index() != -1 && M.matrix[i].index() != -1){
				matrix_entry current = (matrix_entry)matrix[i].get();
				matrix_entry current2 = (matrix_entry)M.matrix[i].get();
				if(current.column > current2.column){
					subtraction.changeEntry(i,current2.column,-current2.value);
					M.matrix[i].moveNext();
				}else if(current.column < current2.column){
					subtraction.changeEntry(i,current.column,current.value);
					matrix[i].moveNext();
				}else if(current.column == current2.column){
					if(current.value - current2.value != 0){
						subtraction.changeEntry(i,current.column,current.value - current2.value);
					}
					matrix[i].moveNext();
					M.matrix[i].moveNext();	
				}
			}
			if(matrix[i].index() == -1){
				sub_fill(subtraction,M.matrix[i],i);
			}else{
				add_fill(subtraction,matrix[i],i);
			}
		}
		return subtraction;
	}
	//Helper function for subtract to fill in the rest of the row
	void sub_fill(Matrix A, List B, int row){
		while(B.index() != -1){
			matrix_entry current = (matrix_entry)B.get();
			A.changeEntry(row,current.column,-current.value);
			B.moveNext();
		}
	}
	

	Matrix transpose(){					// returns a new Matrix that is the transpose of this Matrix
		Matrix transposed_matrix = new Matrix(size);
		for(int i = 0; i < size; i++){
			matrix[i].moveFront();
			for(int j = 0; j < matrix[i].length();j++){
				matrix_entry current = (matrix_entry) matrix[i].get();
				transposed_matrix.changeEntry(current.column-1,i+1,current.value);
				matrix[i].moveNext();
			}
		}
		return transposed_matrix;
	}

	Matrix mult(Matrix M){				// returns a new Matrix that is the product of this Matrix with M 
		Matrix B = M.transpose();		// pre: getSize()==M.getSize()
		Matrix multiplied = new Matrix(size);
		for(int i = 0; i < size; i++){
			for(int j = 0; j < size; j++){
				double dot_product = dot(matrix[i],B.matrix[j]);
				if(dot_product != 0){
					multiplied.changeEntry(i,j+1,dot_product);
				}
			}
		}
		return multiplied;
	}
	
	//Helper function for mult method
	double dot(List A, List B){
		double sum = 0.0;
		A.moveFront();
		B.moveFront();
		while(A.index() != -1 && B.index() != -1){
			matrix_entry entry = (matrix_entry)A.get();
			matrix_entry entry2 = (matrix_entry)B.get();
			if(entry.column < entry2.column){
				A.moveNext();
			}else if(entry.column > entry2.column){
				B.moveNext();
			} else if(entry.column == entry2.column){
				sum += entry.value * entry2.value;
				A.moveNext();
				B.moveNext();
			}
		}
		return sum;
	}

	// Other functions
	public String toString(){ // overrides Object's toString() method
		String matrix_string = "";
		for(int i = 0; i < size; i++){
			matrix[i].moveFront();
			if(matrix[i].length() != 0){
				matrix_string += (i+1 + ": ");
			}
			for(int j = 0; j < matrix[i].length();j++){
				matrix_entry current = (matrix_entry) matrix[i].get();
				matrix_string += ("(" + current.column + ", " + current.value + ")");
				if(j + 1 != matrix[i].length()){
					matrix_string += " ";
				}
				matrix[i].moveNext();
			}
			if(matrix[i].length() != 0){
				matrix_string += "\n";
			}	
		}
		return matrix_string;
	}
}