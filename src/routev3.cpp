#include <iostream>
using namespace std;
#include <math.h>

#define DEBUG

#define MAX_IN 1024
#define MAX_STAGE 14
#define MAX_EXTRA 4

char MINA[MAX_IN][MAX_STAGE];
char MINB[MAX_IN][MAX_STAGE];
bool MINA_FREE[MAX_IN][MAX_STAGE];
bool MINB_FREE[MAX_IN][MAX_STAGE];

/*
radix 4
IN = 64, ST= 3, EX=1
*/
int ST; // stage number
int EX; // extra levels
int IN; // input number
int MASK;

int window(int word, int column) {
 return (word >> (2*(ST+EX)-2*(column+1))) & MASK;
}

int switch_code(int word, int column) {
 return (word >> (2*(2*ST+EX-1)-2*column)) & 3;
}

void clean(int st, int ex, int in) {
  for (int i=0; i < in ; i++) {
	for (int j=0; j<(st+ex); j++) {
		MINA_FREE[i][j] = true;
		MINB_FREE[i][j] = true;
	} // for j
  } // for
} // clean

void init_MIN(int st, int ex, int in) {
	ST = st;
	EX = ex;
	IN = in;
	MASK = IN-1;
	clean(st,ex,in);
} // init_MIN

// multicast, radix4, 2 networks

bool route_extra(int a, int b) {	

	bool result = true;
	int word;
	int line;
	int in_switch;

	// from out stage to in stage, j is the Column
	for (int extra=0; extra < pow(4,EX); extra++) {
		
		result = true;
		
		word = b | (a << (2*ST+2*EX)) | (extra << (2*ST)); 
		cout << "word " << word << endl;
		
		for (int j=0; j < ST+EX; j++) {
			line = window(word,j);
			//cout << "A line " << line << " col " << j <<endl;
			in_switch = switch_code(word,j);
				if (!MINA_FREE[line][j]) {
				//cout << "No free, check mux " << in_switch << endl;
				result = result && (MINA[line][j]==in_switch);
			} 	
		} 

		if (result) { // sucessful route in A
			for (int j=0; j < ST+EX; j++) {
				line = window(word,j);
				MINA_FREE[line][j] = false;
				in_switch = switch_code(word,j);
					MINA[line][j] = in_switch; 	
			} 

			cout << "OK A" << endl;
			return result;
		} 

		// result = true;
		
		// // from out stage to in stage, j is the Column  
		// for (int j=0; j < ST+EX; j++) {
		// 	line = window(word,j);
		// 	//cout << "B line " << line << " col " << j <<endl;
		// 	in_switch = switch_code(word,j);
		// 		if (!MINB_FREE[line][j]) {
		// 		//cout << "No free, check mux " << in_switch << endl;
		// 		result = result && (MINB[line][j]==in_switch); 
		// 	}	
		// }

		// if (result) { // sucessful route in A
		// 	for (int j=0; j < ST+EX; j++) {
		// 		line = window(word,j);
		// 		MINB_FREE[line][j] = false;
		// 		in_switch = switch_code(word,j);
		// 			MINB[line][j] = in_switch; 	
		// 	} // for
		// 	cout << "OK b" << endl;
		// 	return result;

		// } 

		// //cout << "fail B" << endl;
		// //cout << "extra " << extra << " fail" << endl;

	} 

  	return result;
} // route without extra




int main ()
{
	cout << "input = ";
	cin >> IN;
	cout << "stage = ";
	cin >> ST;
	cout << "extra = ";
	cin >> EX;

	init_MIN(ST, EX, IN);

	int a,b;

	cout << "a b = ";
	cin >> a >> b;
	bool r;
	while (a != -1) {

		r = route_extra(a,b);

		if ( !r ) {
			cout << "Fail" << endl;
			exit(1);
		}
		cout << "a b = ";
		cin >> a >> b;
	}

	return 0;
}




