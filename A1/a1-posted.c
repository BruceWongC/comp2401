#include <stdio.h>          // Including stdio gives us access to printf() and scanf()

#define MAX_SIZE  16        // Maximum number of elements in any array

#define C_OK             0	// Success flag
#define C_ERR_ARR_FULL  -1	// Error code for array is full
#define C_ERR_BAD_EMF   -2	// Error code for an invalid emf_values value
#define C_ERR_BAD_RID   -3	// Error code for an invalid Room ID value

// Tip: You should likely include some more definitions to avoid "magic numbers"

// Note: These are "Forward Declarations". They tell the compiler that these functions exist, 
// but that they will be defined later. You can **not** change any of these lines, but you 
// may add additional "helper" functions if you wish and change the parameter names (not types).
// You MAY remove all of the comments you were provided with.



// Function takes input and checks if it's within range
// It takes in an input which is the input given from user
int is_valid_room_id(int room_ids){
    if (room_ids >= 350000 && room_ids <= 400000){//are inputs within range
        return C_OK;
    }

    printf("Invalid Room ID: %i \n", room_ids);
    return C_ERR_BAD_RID;
}

// Function takes input and checks if it's within range
// It takes in an input which is the input given from user
int is_valid_emf_values(float emf_values){
    if (emf_values >= 0 && emf_values <= 5){//are inputs within range
        return C_OK;
    }

    printf("Invalid EMF value: %0.2f \n", emf_values);
    return C_ERR_BAD_EMF;
}

// Function asks the user to input values and stores them if they are valid
// It takes in the arrays used to store the users input if valid
int get_data(int room_ids[], float emf_values[]){ 
  int ID = 0, i = 0;
  float EMF = 0;

  while (i != MAX_SIZE){//when array is full, end loop
      printf("Enter Room ID and EMF value (enter -1 -1 to quit): ");
      scanf("%i %f", &ID, &EMF);

      if(EMF == -1 && ID == -1){
        printf("Quitting program\n\n");
        break;
      }
      else if (is_valid_room_id(ID) == C_ERR_BAD_RID);
      else if (is_valid_emf_values(EMF) == C_ERR_BAD_EMF);
      else{
        room_ids[i] = ID;
        emf_values[i] = EMF;
        i++;
      }
  }

  if (i == 16){
    printf("Arrays are full. Quitting program\n\n");
    return C_ERR_ARR_FULL;
  }

  return i;//return size of arr if user exits early

}


// Function gets the arrays and size of them to print out the data in a certain format
// It takes in the arrays used to store the users inputs and the size of those arrays to allow for 
//printing the intended values
int print_data(int room_ids[], float emf_values[], int size){
  if (size == C_ERR_ARR_FULL){//means arr are full, so it reached maxed size from error code
    size = MAX_SIZE;
  }

  printf("ROOM ID      EMF\n");
  printf("-------    -----\n");

  for (int i = 0; i < size; i++){
    printf("%-10d %5.2f\n", room_ids[i], emf_values[i]);
  }
  
  printf("-------    -----\n");

  printf("Total Entries: %i\n\n", size);

  return C_OK;
}

// Function moves down the contents of the arrays if the current index goes under
// the given threshold
// It takes in the threshold for cutting the arrays elements, the arrays with
// the contents of the user and the size of the array with the users intended inputs
int remove_values_under(float threshold, int room_ids[], float emf_values[], int size){
  int index = 0;//index to look at

  if (size == C_ERR_ARR_FULL){//means arr are full, so it reached maxed size from error code
    size = MAX_SIZE;
  }

  while(index < size){
    if(emf_values[index] < threshold){
      for(int i = index; i < size - 1; i++){
        emf_values[i] = emf_values[i + 1];//removes the index that's < threshold, then shifts everything down
        room_ids[i] = room_ids[i + 1];
      }
      size--;//to keep track of current size and to return
    }
    else{
      index++;
    }
  }

  return size;
}

int main(){
  int room_ids[MAX_SIZE];
  float emf_values[MAX_SIZE];
  int arr_size = 0;//size of data
  int size_new = 0;//new size after filter

  arr_size = get_data(room_ids, emf_values);

  if(arr_size == 0){//if no inputs say there weren't any then exit
    printf("\nThere were no entires entered to print");
    return C_OK;
  }
  
  print_data(room_ids, emf_values, arr_size);

  size_new = remove_values_under(4.50, room_ids, emf_values, arr_size);

  if(size_new == 0){
    printf("No entires after filtering under threshold. Exiting");
  }
  else{
    print_data(room_ids, emf_values, size_new);
  }

  return C_OK;
}

/*
  Function: example_function_documentation(int, int, float[])
  Purpose:  Displays example expected documentation for all functions except for main()
      in     var_name:    An in (or input) parameter is one that is read by the function but not modified
      out    var_name2:   An out (or output) parameter is one that is modified by the function but not read
      in/out var_name3:   An in/out parameter is one that is both read and modified by the function
       
  return:   the meaning of what's being returned, and any cases/conditions that would cause a different value to be returned
*/