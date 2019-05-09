//Nathan Baledio
//ID: 1574354
//CMPS101 Spring 2019

public class MatrixTest{
	public static void main (String[]args){
		
		Matrix test = new Matrix(4);
		
		test.changeEntry(1,1,1.0);
		test.changeEntry(1,2,2.0);
		test.changeEntry(1,3,3.0);
		test.changeEntry(1,4,4.0);
		
		test.changeEntry(2,1,5.0);
		test.changeEntry(2,2,6.0);
		test.changeEntry(2,3,7.0);
		test.changeEntry(2,4,8.0);
		
		test.changeEntry(3,1,9.0);
		test.changeEntry(3,2,10.0);
		test.changeEntry(3,3,11.0);
		test.changeEntry(3,4,12.0);
		
		test.changeEntry(4,1,13.0);
		test.changeEntry(4,2,14.0);
		test.changeEntry(4,3,15.0);
		test.changeEntry(4,4,16.0);
		
		System.out.println(test.getNNZ());
		System.out.println(test.toString());
		test.makeZero();
		test.changeEntry(2,1,0);
		test.changeEntry(1,3,0);
		test.changeEntry(3,2,1);
		System.out.println(test.getNNZ());
		
		Matrix test2 = test.transpose();
		Matrix test3 = test.add(test2);
		Matrix test4 = test.sub(test2);
		Matrix test5 = test.mult(test2);
		Matrix test6 = test.copy();
		Matrix test7 = test.scalarMult(-1);
		Matrix test8 = test2.scalarMult(2.3);
		
		System.out.println(test2.toString());
		System.out.println(test3.toString());
		System.out.println(test4.toString());
		System.out.println(test5.toString());
		System.out.println(test6.toString());
		System.out.println(test7.toString());
		System.out.println(test8.toString());
		System.out.println(test7.add(test));
		System.out.println(test7.sub(test));
		System.out.println(test.equals(test));
		System.out.println(test.equals(test2));
		System.out.println(test.equals(test3));
		System.out.println(test.equals(test4));
		System.out.println(test.equals(test5));
		System.out.println(test.equals(test6));
		System.out.println(test.equals(test7));
		System.out.println(test.equals(test8));
		
		
	}
}
	