// FILE: IntSet.cpp - header file for IntSet class
//       Implementation file for the IntStore class
//       (See IntSet.h for documentation.)
// INVARIANT for the IntSet class:
// (1) Distinct int values of the IntSet are stored in a 1-D,
//     dynamic array whose size is stored in member variable
//     capacity; the member variable data references the array.
// (2) The distinct int value with earliest membership is stored
//     in data[0], the distinct int value with the 2nd-earliest
//     membership is stored in data[1], and so on.
//     Note: No "prior membership" information is tracked; i.e.,
//           if an int value that was previously a member (but its
//           earlier membership ended due to removal) becomes a
//           member again, the timing of its membership (relative
//           to other existing members) is the same as if that int
//           value was never a member before.
//     Note: Re-introduction of an int value that is already an
//           existing member (such as through the add operation)
//           has no effect on the "membership timing" of that int
//           value.
// (4) The # of distinct int values the IntSet currently contains
//     is stored in the member variable used.
// (5) Except when the IntSet is empty (used == 0), ALL elements
//     of data from data[0] until data[used - 1] contain relevant
//     distinct int values; i.e., all relevant distinct int values
//     appear together (no "holes" among them) starting from the
//     beginning of the data array.
// (6) We DON'T care what is stored in any of the array elements
//     from data[used] through data[capacity - 1].
//     Note: This applies also when the IntSet is empry (used == 0)
//           in which case we DON'T care what is stored in any of
//           the data array elements.
//     Note: A distinct int value in the IntSet can be any of the
//           values an int can represent (from the most negative
//           through 0 to the most positive), so there is no
//           particular int value that can be used to indicate an
//           irrelevant value. But there's no need for such an
//           "indicator value" since all relevant distinct int
//           values appear together starting from the beginning of
//           the data array and used (if properly initialized and
//           maintained) should tell which elements of the data
//           array are actually relevant.
//
// DOCUMENTATION for private member (helper) function:
//   void resize(int new_capacity)
//     Pre:  (none)
//           Note: Recall that one of the things a constructor
//                 has to do is to make sure that the object
//                 created BEGINS to be consistent with the
//                 class invariant. Thus, resize() should not
//                 be used within constructors unless it is at
//                 a point where the class invariant has already
//                 been made to hold true.
//     Post: The capacity (size of the dynamic array) of the
//           invoking IntSet is changed to new_capacity...
//           ...EXCEPT when new_capacity would not allow the
//           invoking IntSet to preserve current contents (i.e.,
//           value for new_capacity is invalid or too low for the
//           IntSet to represent the existing collection),...
//           ...IN WHICH CASE the capacity of the invoking IntSet
//           is set to "the minimum that is needed" (which is the
//           same as "exactly what is needed") to preserve current
//           contents...
//           ...BUT if "exactly what is needed" is 0 (i.e. existing
//           collection is empty) then the capacity should be
//           further adjusted to 1 or DEFAULT_CAPACITY (since we
//           don't want to request dynamic arrays of size 0).
//           The collection represented by the invoking IntSet
//           remains unchanged.
//           If reallocation of dynamic array is unsuccessful, an
//           error message to the effect is displayed and the
//           program unconditionally terminated.

#include "IntSet.h"
#include <iostream>
#include <cassert>
using namespace std;

void IntSet::resize(int new_capacity)
{
   //Check if the user specified new_capacity is valid 
   //for the IntSet to represent the existing collection
   //If not set it to the minimum that is needed.	
   if (new_capacity < used)
      new_capacity = used;
   if (new_capacity < 1)
      new_capacity = DEFAULT_CAPACITY;
   capacity = new_capacity;
   
   //dynamically allocate the memory with 
   //user specified capacity. 
   int * newData = new int[new_capacity];
   
   //Deep copy current data to new array
   for (int i = 0; i < used; ++i)
      newData[i] = data[i];
      
   //Deallocate the previously used memory  
   delete [] data;
   
   //make current data to be newData
   data = newData;
   	     
}

//Default constructor
IntSet::IntSet(int initial_capacity) : capacity(initial_capacity), used(0)
{
   //check validity of the user specified capacity
   //if it is invalid, set it to DEFAULT_CAPACITY
   if (capacity < 1)
      capacity = DEFAULT_CAPACITY;
   
   //allocate new dynamic data array to hold  
   //valid capacity provided by the user   
   data = new int[capacity];
}

//copy constructor
IntSet::IntSet(const IntSet& src) : capacity(src.capacity), used(src.used)
{
   //dynamically allocate the memory 
   //with the same size as src set
   data = new int[capacity];
   
   //Deep copy elements of src set into new dynamic array
   for (int i = 0; i < used; ++i)
      data[i] = src.data[i];
}

//Deconstructor
IntSet::~IntSet()
{
   //Deallocate all memory used by data array
   delete [] data;
}

IntSet& IntSet::operator=(const IntSet& rhs)
{
   //check if the invoking set is equal to rhs if not,
   //allocate a new array and copy rhs elements into it.
   if (this != &rhs)
   {
      //dynamically allocate the memory for newData 
	  //array with the same size as rhs set
	  int * newData = new int[rhs.capacity];
	  
	  //copy every data of rhs set into newData
	  for (int i = 0; i < rhs.used; ++i)
	     newData[i] = rhs.data[i];
	     
	  //Deallocate the previous dynamic array    
      delete [] data;
      
      //assign member variable from rhs to current member 
      data = newData;
	  capacity = rhs.capacity;
	  used = rhs.used;	
   }
   
   //the invoking set is unchanged
   return *this;
}

int IntSet::size() const
{
   //Number of elements in the invoking IntSet
   return used;
}

bool IntSet::isEmpty() const
{
   //Empty if the invoking IntSet has no relevant elements
   return used == 0;
}

bool IntSet::contains(int anInt) const
{
   //traverse IntSet looking for an anInt
   //return false if anInt is not found.
   if (used > 0)
   {
      
	  for(int i = 0; i < used; i++)
	     if (data[i] == anInt)
            return true;
   }
   return false; 
}

bool IntSet::isSubsetOf(const IntSet& otherIntSet) const
{
   //check if IntSet is empty and return true since
   //empty set is always a subset of another set.
   if (this->isEmpty())
       return true;
   else
   {
   	  //loop through and check if all elements of the invoking IntSet
      //are also elements of otherIntSet, otherwise return false.
      for(int i =0; i < this->size(); i++)
         if (!otherIntSet.contains(this->data[i]))
	        return false;
    		
      return true;
   }

}

void IntSet::DumpData(ostream& out) const
{  
   if (used > 0)
   {
      out << data[0];
      for (int i = 1; i < used; ++i)
         out << "  " << data[i];
   }
}

IntSet IntSet::unionWith(const IntSet& otherIntSet) const
{
   //make a copy of the invoking set
   IntSet myUnionset = *this;
	
   //loop through otherIntSet to find the elements that  
   //are not in the invoking set, if found addd them
   for (int i = 0; i < otherIntSet.size(); i++)
      if (!myUnionset.contains(otherIntSet.data[i]))
         myUnionset.add(otherIntSet.data[i]);

   return myUnionset; 
}

IntSet IntSet::intersect(const IntSet& otherIntSet) const
{
   //A copy of the invoking IntSet
   IntSet myIntersect = *this;

   //loop through to find elements of the invoking set that 
   //are not in the otherIntSet. If found, remove them
   for (int i = 0; i < size(); i++)
      if (!otherIntSet.contains(data[i]))
         myIntersect.remove(data[i]);
	   
   return myIntersect; 
}

IntSet IntSet::subtract(const IntSet& otherIntSet) const
{
   //Make a copy of the invoking IntSet
   IntSet mySubset = *this;
	
   //subtract otherIntSet from the invoking set
   for (int i = 0; i < otherIntSet.size(); i++)
      if (mySubset.contains(otherIntSet.data[i]))
         mySubset.remove(otherIntSet.data[i]);
		
   return mySubset;
}

void IntSet::reset()
{
   //empty the invoking IntSet
   used = 0;
}

bool IntSet::add(int anInt)
{
   //If not in a set, add new element into a set
   if (!contains(anInt))
   {
   	  //If used exceeds or equals the capacity
   	  //resize using a resizing formula.
   	  if (used >= capacity)
   	     resize(int(1.5 * capacity) + 1);
   	     
   	  //add a new element if IntSet have enough room.   
      data[used] = anInt;
      used++;
   	  return true;
   }
   //the invoking IntSet is unchanged
   return false; 
}
bool IntSet::remove(int anInt)
{
   //Shifting elements of array data with used items 
   //when removing a anInt-matching item
   if (contains(anInt))
   {
   	  for (int i = 0; i < used; i++)
         if (data[i] == anInt)
            for (int j = i + 1; j < used; j++)
               data[j-1] = data[j];
				
            used--;
			return true;
   }
			
   //the invoking IntSet is unchanged
   return false;
}

bool operator==(const IntSet& is1, const IntSet& is2)
{
   //Check if is1 is a subset of is2 and is2 is a subset of is1.
   //If true, then they are equal by the defintion of subset
   //also empty set is equal to another empty set
   if (is1.IntSet::isSubsetOf(is2) && is2.IntSet::isSubsetOf(is1))
      return true;
	
   return false;
}
