#include <stdio.h> /* printf */
#include <stdlib.h> /* system */

#define ARR_SIZE 256

typedef void(*lut_ptr_char_t)(void);


static void Initialize_LuT_Table(lut_ptr_char_t *, size_t );
static void IfElse(char );
static void MsgAPressed();
static void MsgTPressed();
static void MsgESCPressed();	
static void dummy();

/* func in LuT for pressed 'A' */
static void MsgAPressed()
{
	printf("\n A is pressed using in  LUT table\n");
}

/* func in LuT for pressed 'T' */
static void MsgTPressed()
{
	printf("\n T is pressed using in  LUT table\n");
}

/* func in LuT for pressed 'ESC' */
static void MsgESCPressed()
{
	printf("\n ESC is pressed using in  LUT table\n");
}

/* was pressed anything but A/T/ESC */
static void dummy()
{
	printf("\n Wrong Input Dummy Func \n");	
}

static void Initialize_LuT_Table(lut_ptr_char_t * lut_arr, size_t size_arr)
{
	size_t i = 0;

	for(; i < size_arr; i++)
	{
		lut_arr[i] = dummy;
	}

	lut_arr[65] = MsgAPressed;
	lut_arr[84] = MsgTPressed;
	lut_arr[27] = MsgESCPressed;
}

/* check if A or T or ESC were pressed */ 
static void IfElse(char usr_char)
{
	/* check if A or T or ESC were pressed */ 
	/* check if A was pressed */
	if(usr_char == 0x41 || usr_char == 0x54)
	{
		printf("\n%c is pressed using in  if/else \n", usr_char);
	}

	/* check if B was pressed */
	else if(usr_char == 0x1B)
	{
		printf("\n ESC is pressed in if/else, process will be terminated \n");
	}
	else
	{
		printf("\n Wrong Input in if/else \n");
	}
}

/* check if A or T or ESC were pressed */ 
static void SwitchCase(char usr_inpt)
{
	switch(usr_inpt){
		/* A or T were pressed */
		case(0x41): case(0x54):
			printf("\n%c is pressed using in  switch case \n", usr_inpt);
			break;
		/* ESC was pressed */
		case(0x1B):
			printf("\n ESC is pressed in switch, process will be terminated \n");
			break;
		default:
			printf("\n Wrong Input in switch \n");
			break;
	}

}

int main()
{
	char usr_char_input = 0;
	lut_ptr_char_t lut_table[ARR_SIZE] = {NULL};

	/* init lut table */
	Initialize_LuT_Table(lut_table, ARR_SIZE);

	while(1)
	{
		system("stty -icanon -echo");
		usr_char_input = getchar();
		system("stty icanon echo");

		IfElse(usr_char_input);

		SwitchCase(usr_char_input);

		usr_int_input = (int)usr_char_input;
		(*lut_table[usr_int_input])();
		
		if(usr_char_input == 27)
		{
			exit(0);
		}
	
	}

	

	return 0;
}


