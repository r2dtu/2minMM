const int nn=16;                //maximum size of array 
short int a[nn+1][nn+1]; 		    //array which stores values of cells in maze 
short int wall_stack[256][2]; 	//array for wallstack 
short int wall_counter; 		    //counter for knowing position of elements in stack 
short int check;			 	        //check short 
int ff_stack[256][2];           //main stack
int ff_count; 	                //main stack counter for knowing position 

void flood() {                  //function  
  int level=0,i;                //initialize level to 0
  clear_wstack(); 	            //function to clear wall stack 
  start: 
  // Err check
  if(ff_count<0)goto end; 
  
  /* Repeat until ff_stack is empty:
    1. Remove a cell from ff_stack
    2. If DistanceValue(cell) = 255 {
      Let DistanceValue(cell) = level
      Place all open neighbors of cell into wall stack
    }
  */
  while(ff_count>=0) {
    if(a[ff_stack[ff_count][0]][ff_stack[ff_count][1]]==255) { 
      // Let DistanceValue(cell) = level
      a[ff_stack[ff_count][0]][ff_stack[ff_count][1]]=level; 
      // Place all open neighbors of cell into wall stack
      nbor(ff_stack[ff_count][0],ff_stack[ff_count][1],nn); 
    } 
    ff_stack[ff_count][0]=ff_stack[ff_count][1]=0; 
    --ff_count; 
  } 

  getch();  // Get character
  
  // Check if wallstack is empty
  if(wall_counter!=0) { 
    // If not empty, incrementlevel
    level++; 
    while(wall_counter>0) { 
      // Increment ff_count (change position)
      ++ff_count; 

      // Let ff_stack = wall stack 
      {ff_stack[ff_count][0]=wall_stack[wall_counter-1][0]; 
      
      // Initialize ff_stack
      ff_stack[ff_count][1]=wall_stack[wall_counter-1][1]; 
      wall_counter--;} 
    }
    // Go back to beginning
    clrscr(); 
    clear_wstack();
    goto start; 
  } 
  end: 
  ; 
}			
   
