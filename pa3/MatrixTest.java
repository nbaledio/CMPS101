public class MatrixTest{
	public static void main (String[]args){
		Matrix test = new Matrix(4);
		Matrix test6 = new Matrix(4);
		
		test.changeEntry(0,1,1.0);
		test.changeEntry(0,2,2.0);
		test.changeEntry(0,3,3.0);
		test.changeEntry(0,4,4.0);
		
		test.changeEntry(1,1,5.0);
		test.changeEntry(1,2,6.0);
		test.changeEntry(1,3,7.0);
		test.changeEntry(1,4,8.0);
		
		test.changeEntry(2,1,9.0);
		test.changeEntry(2,2,10.0);
		test.changeEntry(2,3,11.0);
		test.changeEntry(2,4,12.0);
		
		test.changeEntry(3,1,13.0);
		test.changeEntry(3,2,14.0);
		test.changeEntry(3,3,15.0);
		test.changeEntry(3,4,16.0);
		
		test6.changeEntry(0,1,1.0);
		test6.changeEntry(0,2,2.0);
		test6.changeEntry(0,3,3.0);
		test6.changeEntry(0,4,4.0);
		
		test6.changeEntry(1,1,5.0);
		test6.changeEntry(1,2,6.0);
		test6.changeEntry(1,3,7.0);
		test6.changeEntry(1,4,8.0);
		
		test6.changeEntry(2,1,9.0);
		test6.changeEntry(2,2,10.0);
		test6.changeEntry(2,3,11.0);
		test6.changeEntry(2,4,12.0);
		
		test6.changeEntry(3,1,13.0);
		test6.changeEntry(3,2,14.0);
		test6.changeEntry(3,3,15.0);
		test6.changeEntry(3,4,16.0);
		
		Matrix test2 = test.transpose();
		Matrix test3 = test.add(test2);
		Matrix test4 = test.sub(test2);
		Matrix test5 = test.mult(test2);
		
		//System.out.println(test.getNNZ());
		System.out.println(test.toString());
		System.out.println(test2.toString());
		System.out.println(test3.toString());
		System.out.println(test4.toString());
		System.out.println(test5.toString());
		System.out.println(test.equals(test));
		System.out.println(test.equals(test2));
		System.out.println(test.equals(test3));
		System.out.println(test.equals(test4));
		System.out.println(test.equals(test5));
		System.out.println(test.equals(test6));
		
		
	}
}
	