#include <stdio.h>          // Including stdio gives us access to printf() and scanf()
#include <stdlib.h>			//Gives access to exit()

#define MAX_SIZE  16        // Maximum number of elements in any array

#define C_OK             0	// Success flag
#define C_ERR_ARR_FULL  -1	// Error code for array is full
#define C_ERR_BAD_EMF   -2	// Error code for an invalid emf_values value
#define C_ERR_BAD_RID   -3	// Error code for an invalid Room ID value

// Tip: You should likely include some more definitions to avoid "magic numbers"
#define RID_MIN  350000   	// Lowest possible room number
#define RID_MAX  400000   	// Highest possible room number

#define EMF_MIN     0.00    // Lowest possible EMF Value
#define EMF_MAX     5.00    // Highest possible EMF Value
#define EMF_FILTER  4.50    // Desired EMF threshold to filter and keep values only above 4.50 

// Note: These are "Forward Declarations". They tell the compiler that these functions exist, 
// but that they will be defined later. You can **not** change any of these lines, but you 
// may add additional "helper" functions if you wish and change the parameter names (not types).
// You MAY remove all of the comments you were provided with.
int get_data(int room_ids[], float emf_values[]);
int is_valid_room_id(int room_ids);
int is_valid_emf_values(float emf_values);
int print_data(int room_ids[], float emf_values[], int size);
int remove_values_under(float threshold, int room_ids[], float emf_values[], int size);

int main() {
	int room_ids[MAX_SIZE] = {0};
	float emf_values[MAX_SIZE] = {0};
	int size = 0;
	
	size = get_data(room_ids, emf_values);
	
	if (size == 0) {
		printf("No entries entered to print. Exiting.");
		exit(EXIT_FAILURE);
	} else {
		print_data(room_ids, emf_values, size); 
		size = remove_values_under(EMF_FILTER, room_ids, emf_values, size);
		if (size == 0) {
			printf("\nNo entries left after removing values under threshold. Exiting.");
			exit(EXIT_FAILURE);
		} else {
			print_data(room_ids, emf_values, size);
		}
	}
	
	
	
	return 0;
}

/*
  Function: get_data(int* room_ids, float* emf_values)
  Purpose:  Prompts user for valid Room IDs and EMF Values with a max of 16. If any errors occur, the respective feedback message will be printed. When '-1 -1' is input, the function stops. 
      in     n/a
      out    n/a
      in/out room_ids, emf_values
       
  return:   the size, or number of entries in each array. 
*/
int get_data(int* room_ids, float* emf_values) {
	int i = 0;
	int room_id;
	float emf_value;
	
	while (1) {
		printf("Enter a Room ID and EMF (-1 -1 to quit): ");
		scanf("%d %f", &room_id, &emf_value);
		
		if (room_id == -1 && emf_value == -1) {
			break;
		} else if (is_valid_room_id(room_id) == C_ERR_BAD_RID) {
			printf("Invalid Room ID: %d\n", room_id);
		} else if  (is_valid_emf_values(emf_value) == C_ERR_BAD_EMF) {
			printf("Invalid EMF value: %f\n", emf_value);
		} else if (i > MAX_SIZE-1) {
			printf("Error code: %d. Reached maximum number of entries for arrays. Quitting the program.", C_ERR_ARR_FULL);
			exit(EXIT_FAILURE); 
		} else {
			room_ids[i] = room_id;
			emf_values[i] = emf_value;
			i++;
		}
	}
	
	return i;
}

/*
  Function: print_data(int room_ids[], float emf_values[], int size)
  Purpose:  Prints all of the Room IDs and their corresponding EMF Values in a table (all of which were inputted by the user). Also prints total entries.
      in     room_ids[], emf_values[], size
      out    n/a
      in/out n/a
       
  return:    Was made to be an int function as part of the assignment but there is no use for the return value. Unable to change the type, but type could be changed to void.
*/
int print_data(int room_ids[], float emf_values[], int size) {	
	printf("\n%-10s%5s\n", "Room ID", "EMF");
	printf("%-10s%5s\n", "-------", "-----");
	for (int i=0; i<size; i++) {
		printf("%-10d%5.2f\n", room_ids[i], emf_values[i]); 
	}
	printf("%-10s%5s\n", "-------", "-----");
	printf("%-14s%2d\n", "Total Entries: ", size);
	return 0;
}

/*
  Function: is_valid_room_id(int room_ids)
  Purpose:  Checks if the parameter value passed into the function - a supposed room ID - is valid, meaning if it is above 350000 and below 400000, inclusive.
      in     room_ids
      out    n/a
      in/out n/a
       
  return:    If the passed room ID is valid, then C_OK (success flag) is returned. If invalid, then C_ERR_BAD_RID (error flag for invalid room ID) is returned.
*/
int is_valid_room_id(int room_ids) {
	if (room_ids >= RID_MIN && room_ids <= RID_MAX) {
		return C_OK;
	} else {
		return C_ERR_BAD_RID;
	}
}

/*
  Function: is_valid_emf_values(float emf_values)
  Purpose:  Checks if the parameter value passed into the function - a supposed EMF value - is valid, meaning if it is above 0.00 and below 5.00, inclusive.
      in     emf_values
      out    n/a
      in/out n/a
       
  return:    If the passed EMF value is valid, then C_OK (success flag) is returned. If invalid, then C_ERR_BAD_EMF (error flag for invalid EMF value) is returned.
*/
int is_valid_emf_values(float emf_values) {
	if (emf_values >= EMF_MIN && emf_values <= EMF_MAX) {
		return C_OK;
	} else {
		return C_ERR_BAD_EMF;
	}
}

/*
  Function: remove_values_under(float threshold, int room_ids[], float emf_values[], int size)
  Purpose:  Using the threshold parameter, modifies the room_ids array and the emf_values array to only contain room IDs with the corresponding EMF values that are above the passed threshold. 
      in     threshold, size
      out    n/a
      in/out room_ids[], emf_values[]
       
  return:    The size, as in the number of entries, for how many Room IDs exist with the corresponding EMF values above the used threshold.
*/
int remove_values_under(float threshold, int room_ids[], float emf_values[], int size) {
	int j = 0;
	for (int i=0; i<size; i++) {
		if (emf_values[i] > threshold) {
			emf_values[j] =  emf_values[i];
			room_ids[j] = room_ids[i];
			j++;
		}
	} 
	
	return j;
}




/*
  Function: example_function_documentation(int, int, float[])
  Purpose:  Displays example expected documentation for all functions except for main()
      in     var_name:    An in (or input) parameter is one that is read by the function but not modified
      out    var_name2:   An out (or output) parameter is one that is modified by the function but not read
      in/out var_name3:   An in/out parameter is one that is both read and modified by the function
       
  return:   the meaning of what's being returned, and any cases/conditions that would cause a different value to be returned
*/

