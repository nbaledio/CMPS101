import java.io.*;
import java.util.Scanner;

class Lex{
	public static void main (String[] args) throws IOException{
		
	  // check number of command line arguments is at least 2
      if(args.length < 2){
         System.err.println("Usage: java Lex <input file> <output file>");
         System.exit(1);
      }
	  
	  // open files
      BufferedReader reader = new BufferedReader(new FileReader(args[0]));
      PrintWriter out = new PrintWriter(new FileWriter(args[1]));
	  
	  //while loop to count number of lines within in file
	  int linecount = 0;
      while( reader.readLine() != null ){
         linecount++;
	  }
	  reader.close();
	  
	  //Second reader to read lines and add individual lines to array
	  BufferedReader reader2 = new BufferedReader(new FileReader(args[0]));
	  String[] array = new String[linecount];
	  int index_tracker = 0;
	  String line = "";
	  while( (line = reader2.readLine()) != null ){
		 array[index_tracker] = line;
		 index_tracker++;
	  }
	  //List creation and sorting (insertion sort)
	  List list = new List();
	  for(int i = 0; i < array.length; i++){
		  if(i == 0){
			  list.prepend(i);
		  }else{
			  list.moveBack();
			  boolean inserted = false;
			  while(inserted == false){
				  int check = array[i].compareTo(array[list.get()]);
				  if(check <= 0){
					  if(list.cursor == list.front){
						  list.prepend(i);
						  inserted = true;
					  }else{
						  list.movePrev();
				      }
				  }else{
					  if(list.cursor == list.back){
						  list.append(i);
						  inserted = true;
					  }else{
						  list.insertAfter(i);
						  inserted = true;
					  }
				  }
			  }
		  }
	  }
	  
	  list.moveFront();
	  while(list.cursor != null){
		  System.out.println(array[list.get()]);
		  list.moveNext();
	  }
	  
	  // close files
      reader2.close();
      out.close();
	}
}