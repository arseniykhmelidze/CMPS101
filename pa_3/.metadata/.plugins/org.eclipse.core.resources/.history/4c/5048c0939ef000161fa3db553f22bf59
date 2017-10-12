/*
File: List.java
Class: CMPS 101
Assignment: PA3
Student: Arseniy Khmelidze (akhmelid)
Date created: 02/02/17 
*/ 

// Constructor
public class List 
{
	private class Node 
	{
        Node previous;
        Node next;
        Object data;

        Node(Object data) 
        {
            this.data = data;
            next = null;
            previous = null;
        }

        Node(Object data, Node nextNode, Node prevNode) 
        {
            this.data = data;
            next = nextNode;
            previous = prevNode;
        }

        public String toString() 
        {
            return String.valueOf(data);
        }
    }
	
	// Fields
    private int length;
    private int index; 
    private Node cursor;
 	private Node front;
    private Node back;

    // Constructor
    List() 
    {
    	length = 0;
		index = -1;
        cursor = null;
		front = null;
		back = null;
    }
    
    
//	boolean isEmpty() // Checking if the List is empty
//	{
//		return length == 0;
//	}
//	
//	
//	boolean isDefined() // Checking if the list is defined
//	{
//		if(index >= 0 && index < length) 
//		{
//			return true; 
//		}
//		
//		else 
//		{ 
//			return false; 
//		}
//	}
	
	
    int length() 
    {
        return length;
    }
    

    int index() 
    {
        return index;
    }
    

    Object front() 
    {	
        if (length > 0) 
        {
            return front.data;
        }
        
        else
        {
        	return -1;
        }
    }

    
    Object back() 
    {
        if (length > 0) 
        {
            return back.data;
        }
        
        else
        {
        	return -1;
        }
    }
    
    
    Object get() 
    {
    	// Checking precondition 1
    	if (length() == 0) 
    	{
            return null;
        } 
    	
    	// Checking precondition 2
    	else if (index == -1) 
        {
            return null;
        } 
    	
    	else
    	{
            return cursor.data;
        }
    }
    
    public boolean equals(Object o) 
    {
        List L;
        
        if (o instanceof List) 
        {
            L = (List) o;
            
            if (this.length == L.length) 
            {
                Node list_1 = this.front;
                Node list_2 = L.front;
                
                while (list_1 != null && list_2 != null) 
                {
                    if (list_1.data.equals(list_2.data)) 
                    {
                    	list_1 = list_1.next;
                    	list_2 = list_2.next;
                    } 
                    
                    else 
                    {
                    	return false;
                    }
                }
                
                return true;
            } 
            
            else 
            {
                return false;
            }
        } 
        
        else
        {
        	return false;
        }
    }


    
	// Manipulation procedures / Cursor Manipulation Procedures
    
    void clear() 
    {
        cursor = front;
        
        if (cursor != null) 
        {
            while (cursor.next != null) 
            {
                Node temp_node = cursor;
                cursor = cursor.next;
                
                temp_node.next = null;
                temp_node.previous = null;
            }
            
            cursor = null;
            length = 0;
            back = front = null;
            index = -1;
        }
    }


    void moveFront() 
    {
    	// Checking precondition
    	if (length > 0)
		{
    		cursor = front;
			index = 0;
		}
    }

    
    void moveBack() 
    {
    	// Checking precondition
    	if (length > 0)
		{
    		cursor = back;
			index = length - 1;
		}
    }


    void movePrev() 
    {
        if (cursor != null && !cursor.equals(front)) 
        {
            cursor = cursor.previous;
            index--;
        } 
        
        else if (cursor != null && cursor.equals(front)) 
        {
            cursor = null;
            index = -1;
        } 
        
        else
        {
            return;
        }

    }

    
    void moveNext() 
    {
        if (cursor != null && !cursor.equals(back)) 
        {
            cursor = cursor.next;
            index++;
        } 
        
        else if (cursor != null && cursor.equals(back)) 
        {
            cursor = null;
            index = -1;
        } 
        
        else
        {
            return;
        }
    }

    
    
    
	// Element Insertion Manipulation

    void prepend(Object data) 
    {
        if (length > 0) 
        {
            Node new_front = new Node(data, front, null);
            front.previous = new_front;
            front = new_front;
            
            length++;
            index++;
        } 
        
        else 
        {
            Node new_elem = new Node(data);
            front = new_elem;
            back = new_elem;
            length++;
            index++;
        }
    }

    
    void append(Object data) 
    {
        if (length > 0) 
        {
            Node new_front = new Node(data, null, back);
            back.next = new_front;
            back = new_front;
            length++;
        } 
        
        else 
        {
            Node new_elem = new Node(data);
            front = new_elem;
            back = new_elem;
            length++;
        }
    }
    
    
    void insertBefore(Object data) 
    {
    	// Checking precondition 1
    	if (length() <= 0) 
    	{
            return;
        } 
    	
    	// Checking precondition 2
    	else if (index() < 0) 
        {
            return;
        }
		
        Node new_elem = new Node(data);
        
        if (index() == 0) 
        {
            prepend(data);
        } 
        
        else 
        {
        	new_elem.next = cursor;
        	new_elem.previous = cursor.previous;
            cursor.previous.next = new_elem;
            cursor.previous = new_elem;
            
            index++;
            length++;
        }
    }


    void insertAfter(Object data) 
    {
    	// Checking precondition 1
    	if (length() <= 0) 
    	{
            return;
        } 
    	
    	// Checking precondition 2
    	else if (index() < 0) 
    	{
            return;
        }
        
        Node new_elem = new Node(data);
        
        if (index() == length() - 1) 
        {
            append(data);
        } 
        
        else 
        {
        	new_elem.previous = cursor;
        	new_elem.next = cursor.next;
            cursor.next.previous = new_elem;
            cursor.next = new_elem;
            
            length++;
        }
    }
    
    
    void advanceTo(int i) 
    {
        if (i == index) 
        {
        	return;
        }
        
        if (i >= length() || i < 0) 
        {
            cursor = null;
            index = -1;
            return;
        }
        
        if (i == 0)
        {
            cursor = front;
        }
        
        if (i == length() - 1)
        {
            cursor = back;
        }
        
        else 
        {
            int num1 = length() - i;
            int num2 = i;
            int num3 = Math.abs(index - i);
            int splitter = 0;
            
            int default_num = num1;
            
            if (default_num > num2)
            {
            	default_num = num2;
            }
            
            if (default_num > num3)
            {
            	default_num = num3;
            }
            
            if (default_num == num1) 
            {
                cursor = back;
                index = length() - 1;
                splitter = 0;
            }
            
            else if (default_num == num2) 
            {
                cursor = front;
                index = 0;
                splitter = 1;
            } 
            
            else if (default_num == num3) 
            {
                if (i > index) splitter = 1;
            }
            
            for (int j = 0; j < i; j++) 
            {
                if (splitter == 1) moveNext();
                else movePrev();
            }
        }
        
        index = i;
    }

    
    
    
	// Element deletion manipulation
    
    void deleteFront() 
    {
    	// Checking list size precondition
        if (length > 0) 
        {
            front = front.next;
            
            if (front != null) 
            {
                front.previous = null;
            }
            
            length--;
        } 
        
        else 
        {
            front = null;
        }
    }


    void deleteBack() 
    {
    	// Checking precondition list size precondition
        if (length > 0) 
        {
            back = back.previous;
            if (back != null) 
            {
                back.next = null;
            }
            
            length--;
        } 
        
        else 
        {
            back = null;
        }
    }


    void delete() 
    {
    	// Checking precondition list size and index definition preconditions
        if (length > 0 && index >= 0) 
        {
            cursor.next.previous = cursor.previous;
            cursor.previous.next = cursor.next;
            
            cursor = null;
            index = -1;
            
            length--;
        }
    }
    
	// Other methods
    
    // Rewriting the initial toString() f-n
    public String toString() 
    {
        String output = "";
        
        for (Node cursor = front; cursor != null; cursor = cursor.next) 
        {
        	output += cursor.toString() + " ";
        }
        return output;
    }
}
