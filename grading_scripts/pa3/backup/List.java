public class List{
	
   //Private Node class for doubly linked list
   private class node{
	  Object data;
      node next;
      node prev;
	  node(){}
	  node(Object data){
		  this.data = data;
	  }
   }
   
   //List Fields
   int size = 0;
   node cursor = null; 
   node front = new node();
   node back = new node();
	
   // Constructor
   List(){	   // Creates a new empty list.
	   front.next = back;
	   front.prev = null;
	   back.next = null;
	   back.prev = front;
	   size = 0;
   }
   
   // Access functions
   int length(){ // Returns the number of elements in this List.
       return size;
   }
   int index(){ // If cursor is defined, returns the index of the cursor element, otherwise returns -1.
       if(cursor == null){
		   return -1;
	   }
       node iter = front;
	   int index_counter = 0;
	   while(iter != cursor){
		   index_counter++;
		   iter = iter.next;
	   }
	   return index_counter;
   }
   Object front(){ // Returns front element. Pre: length()>0
       return front.data;
   }
   Object back(){ // Returns back element. Pre: length()>0
       return back.data;
   }
   Object get(){ // Returns cursor element. Pre: length()>0, index()>=0
	   return cursor.data;
   }
   public boolean equals(Object x) {			// Returns true if and only if this List and L are the same integer sequence. 
		List B = (List) x;						// The states of the cursors in the two Lists are not used in determining equality.
		if(size != B.length()){			
			return false;
		}
		node iter = front;
		node iter2 = B.front;
		for(int i = 0; i < size;i++){
			if(iter.data != iter2.data){
				return false;
			}
			iter = iter.next;
			iter2 = iter2.next;
		}
		return true;
   }
 
  // Manipulation procedures
  void clear(){ 	// Resets this List to its original empty state.
		front.data = null;
		back.data = null;
		front.next = back;
		front.prev = null;
		back.next = null;
		back.prev = front;
		size = 0;
        cursor = null;
  }

  void moveFront(){ 	// If List is non-empty, places the cursor under the front element,
	   if(size != 0){	// otherwise does nothing.
		   cursor = front;
	   }
  }
  void moveBack(){ 		// If List is non-empty, places the cursor under the back element,
		if(size != 0){	// otherwise does nothing.
		   cursor = back;
	   }
  }
  void movePrev(){ 					// If cursor is defined and not at front, moves cursor one step toward
		if(cursor != null){			// front of this List, if cursor is defined and at front, cursor becomes
			cursor = cursor.prev;	// undefined, if cursor is undefined does nothing.
		}
  }
  void moveNext(){ 					// If cursor is defined and not at back, moves cursor one step toward
		if(cursor != null){			// back of this List, if cursor is defined and at back, cursor becomes
			cursor = cursor.next;	// undefined, if cursor is undefined does nothing.
		}
  }
  void prepend(Object data){ 			// Insert new element into this List. If List is non-empty,
		if(size == 0){					// insertion takes place before front element.
			node new_element = new node(data);
			front = new_element;
			back = new_element;
			size++;
		}else
		if(size == 1){
			node new_element = new node(data);
			new_element.next = back;
			back.prev = new_element;
			front = new_element;
			size++;
		}else{
			node new_element = new node(data);
			front.prev = new_element;
			new_element.next = front;
			new_element.prev = null;
			front = new_element;
			size++;
		}
		
  }
  void append(Object data){ 		// Insert new element into this List. If List is non-empty,
		if(size == 0){			// insertion takes place after back element.
			node new_element = new node(data);
			front = new_element;
			back = new_element;
			size++;
		}else
		if(size == 1){
			node new_element = new node(data);
			new_element.prev = front;
			front.next=new_element;
			back = new_element;
			size++;
		}else{
			node new_element = new node(data);
			back.next = new_element;
			new_element.next = null;
			new_element.prev = back;
			back = new_element;
			size++;
		}
  }
  void insertBefore(Object data){ 							// Insert new element before cursor.
		if(cursor == front || size == 1){				// Pre: length()>0, index()>=0
			prepend(data);
		}else{
			node new_element = new node(data);
			new_element.next = cursor;
			new_element.prev = cursor.prev;
			cursor.prev.next = new_element;
			cursor.prev = new_element;
			size++;
		}
  }
  void insertAfter(Object data){ 				// Inserts new element after cursor.
		if(cursor == back || size == 1){	  	// Pre: length()>0, index()>=0
			append(data);
		}else{
			node new_element = new node(data);
			new_element.next = cursor.next;
			new_element.prev = cursor;
			cursor.next.prev = new_element;
			cursor.next = new_element;
			size++;
		}
  }
  void deleteFront(){ 			// Deletes the front element. Pre: length()>0
		if(cursor == front){	// Pre: length()>0, index()>=0
			cursor = null;
		}
		if(size == 1){		
			front.data = null;
			back.data = null;
			front.next = back;
			front.prev = null;
			back.next = null;
			back.prev = front;
			size = 0;	
		}else{
			front = front.next;	
			size--;
		}
  }
  void deleteBack(){ 		// Deletes the back element. Pre: length()>0
		if(cursor == back){	// Pre: length()>0, index()>=0
			cursor = null;
		}
		if(size == 1){		
			front.data = null;
			back.data = null;
			front.next = back;
			front.prev = null;
			back.next = null;
			back.prev = front;
			size = 0;
		}else{
			back = back.prev;	
			back.next = null;
			size--;
		}
  }
  
  void delete(){ 			// Deletes cursor element, making cursor undefined.
	   if(cursor == back){
		   deleteBack();
		   cursor = null;
	   }
	   else if(cursor == front){
		   deleteFront();
		   cursor = null;
	   }else{
			cursor.prev.next = cursor.next;
			cursor.next.prev = cursor.prev;
			cursor = null;
			size--;
	   }
  }
	
  // Other methods
  public String toString(){ 		// Overrides Object's toString method. Returns a String
		String sequence = "";		// representation of this List consisting of a space
		node iter = front;			// separated sequence of integers, with front on left.
		for(int i = 0; i < size; i++){
			sequence += iter.data;
			if(i + 1 != size){
				sequence += " ";
			}
			iter = iter.next;
		}
		return sequence;
  }                              
}
