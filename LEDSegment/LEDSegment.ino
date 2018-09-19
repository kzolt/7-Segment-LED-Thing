/*
 Name:		LEDSegment.ino
 Created:	19/09/18 11:26:58
 Author:	Kevin Zoltany
*/

#define BUTTON 13
#define MODE_SWITCH 7

#define PANEL_SIZE 7
#define AMOUNT_OF_SEGMENTS 10

typedef enum mode
{
	BUTTON_MODE = 0,
	LOOP_MODE = 1
} Mode;

int button_clicked = 0;
int button_history = 0;
int current_number = 0;
Mode program_mode = BUTTON_MODE;

// Panel Locations
int panel[PANEL_SIZE] = { 8, 9, 2, 3, 4, 6, 5 };

// List Of Directions to Display Numbers
int values[AMOUNT_OF_SEGMENTS][PANEL_SIZE] =
{
  { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, LOW  }, // 0
  { LOW , HIGH, HIGH, LOW , LOW , LOW , LOW  }, // 1
  { HIGH, HIGH, LOW , HIGH, HIGH, LOW , HIGH }, // 2
  { HIGH, HIGH, HIGH, HIGH, LOW , LOW , HIGH }, // 3
  { LOW , HIGH, HIGH, LOW , LOW , HIGH, HIGH }, // 4
  { HIGH, LOW , HIGH, HIGH, LOW , HIGH, HIGH }, // 5
  { HIGH, LOW , HIGH, HIGH, HIGH, HIGH, HIGH }, // 6
  { HIGH, HIGH, HIGH, LOW , LOW , LOW , LOW  }, // 7
  { HIGH, HIGH, HIGH, HIGH, HIGH, HIGH, HIGH }, // 8
  { HIGH, HIGH, HIGH, HIGH, LOW , HIGH, HIGH }  // 9
};

// Displays Current Number
void display_number(int num)
{
	for (int i = 0; i < PANEL_SIZE; i++)
		digitalWrite(panel[i], values[num][i]);
}

void check_mode_switch_button()
{
	if (digitalRead(MODE_SWITCH) == LOW && button_history == 0)
	{
		program_mode = program_mode == BUTTON_MODE ? LOOP_MODE : BUTTON_MODE;
		button_history = 1;
	}
	else if (digitalRead(MODE_SWITCH) == HIGH)
	{
		button_history = 0;
	}
}

// the setup function runs once when you press reset or power the board
void setup() {

	for (int i = 0; i < PANEL_SIZE; i++)
		pinMode(panel[i], OUTPUT);

	pinMode(BUTTON, INPUT);
	pinMode(MODE_SWITCH, INPUT);

	Serial.begin(9600);
}

// the loop function runs over and over again until power down or reset
void loop() {
	check_mode_switch_button();

	if (program_mode == BUTTON_MODE)
	{

		if (digitalRead(BUTTON) == LOW && button_history == 0)
		{
			if (button_clicked >= 10)
				button_clicked = 0;

			display_number(button_clicked);
			button_clicked++;
			button_history = 1;
		}
		else if (digitalRead(BUTTON) == HIGH)
		{
			button_history = 0;
		}

	}
	else if (program_mode == LOOP_MODE)
	{

		for (int i = 0; i < 10; i++)
		{
			display_number(current_number);
			delay(1000);
			current_number++;
		}

		current_number = 0;
	}
}
