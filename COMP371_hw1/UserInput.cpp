#include "stdafx.h"
#include "UserInput.h"


UserInput::UserInput()
{
	multiplier = 1;
	header();
	titleScreen();
}

UserInput::~UserInput()
{
}

double UserInput::getMultiplier() {

	return multiplier;
}

void UserInput::titleScreen() {

	while (!submitForest) {

		cout << "\nSelect which forest you'd like" << endl;
		cout << "\n1. Default forest" << endl;
		cout << "2. Customized forest" << endl;

		cin >> forestChoice;

		if (forestChoice == "1") {
			submitForest = true;
			cout << "You picked default forest\n" << endl;
		}

		else if (forestChoice == "2") {

			while (!submitObject) {

				cout << "\nSelect the amount of objects you want the world to generate" << endl;
				cout << "\n1. Small amount" << endl;
				cout << "2. Medium amount" << endl;
				cout << "3. Large amount" << endl;

				cin >> numChoice;

				if (numChoice == "1" || numChoice == "2" || numChoice == "3") {
					submitObject = true;
				}
				else {
					submitObject = false;
					cout << "\nInvalid choice. Please try again." << endl;
				}

				if (numChoice == "1") {
					multiplier = 1.0;
					cout << "You selected small\n" << endl;
				}
				else if (numChoice == "2") {
					multiplier = 1.25;
					cout << "You selected medium\n" << endl;
				}
				else if (numChoice == "3") {
					multiplier = 1.5;
					cout << "You selected large\n" << endl;
				}
			}
		}

		if (forestChoice == "1" || forestChoice == "2") {
			submitForest = true;
		}
		else {
			submitForest = false;
			cout << "\nInvalid choice. Please try again.\n" << endl;
		}
	}	
}


void UserInput::header() {

	cout << "         ; ; ; " << endl;
	cout << "       ;        ;  ;     ;;    ; " << endl;
	cout << "    ;                 ;         ;  ; " << endl;
	cout << "                    ;                          " << endl;
	cout << "                   ;                ;;		 _____             _      ______                  _" << endl;
	cout << "   ;          ;            ;              ;	|  __ \\           | |    |  ____|                | |" << endl;
	cout << "    ;            ';,        ;               ;	| |  | | __ _ _ __| | __ | |__ ___  _ __ ___  ___| |" << endl;
	cout << "   ;              'b      *		        | |  | |/ _` | '__| |/ / |  __/ _ \\| '__/ _ \\/ __| __|" << endl;
	cout << "    ;              '$    ;;                ;;	| |__| | (_| | |  |   <  | | | (_) | | |  __/\\__ \\ |_" << endl;
	cout << "    ;    ;           $:   ;:               ;	|_____/ \\__,_|_|  |_|\\_\\ |_|  \\___/|_|  \\___||___/\\__|" << endl;
	cout << "  ;;      ;  ;;      *;  @):        ;   ; ; " << endl;
	cout << "               ;     :@,@):   ,;**:'   ; " << endl;
	cout << "   ;      ;,         :@@*: ;;**'      ;   ; " << endl;
	cout << "            ';o;    ;:(@';@*\"'  ; " << endl;
	cout << "    ;  ;       'bq,;;:,@@*'   ,*      ;  ; " << endl;
	cout << "               ,p$q8,:@)'  ;p*'      ; " << endl;
	cout << "        ;     '  ; '@@Pp@@*'    ;  ; " << endl;
	cout << "         ;  ; ;;    Y7'.'     ;  ; " << endl;
	cout << "                   :@):. " << endl;
	cout << "                  .:@:'. " << endl;
	cout << "                .::(@:. " << endl;

	cout << "\n\n Project by Radu Saghin, Clement Hennebelle, Lori Brons, Ashley Lee\n" << endl;

}

void UserInput::executeOrder() {

	header();
	titleScreen();
}
