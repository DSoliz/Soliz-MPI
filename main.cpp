#include <iostream>
#include <fstream>
#include <string.h>
using namespace std;

char * data;

void file_open(string file_name, char * table, int str_length, int x_axisLen){
    ifstream file (file_name);
    cout << "\033[1;31m" << file_name << ":\033[0m"<< endl;//display file name
    string value;
    int x = 0;
    int y = 0;
    while (file.good()){//while file hasnt reached EOF
		//&& y*8 + x < 56
        int c = file.peek();//Peek next character
		if( c == EOF){//if next char is EOF return
			return;
		}
        if(c == '"'){//if it is between quotes read until de next quote
            file.get();
            getline ( file, value, '"' );
            if(file.peek() == ','){
                file.get();
            }
			strncpy(&table[ ( y*x_axisLen*str_length ) + x*str_length ], value.c_str(), 31);
			x++;
        }else{//else read until the next comma or newline
			if(x < x_axisLen -1){//check if x is not the last value
				getline ( file, value, ',' );
				strncpy(&table[ ( y*x_axisLen*str_length ) + x*str_length ], value.c_str(), 31);
				x++;
			}else{//The last value on the row.
				getline ( file, value);
				if(value != "")//check if value is an empty string
					strncpy(&table[ ( y*x_axisLen*str_length ) + x*str_length ], value.c_str(), 31);
				y++;
	            x = 0;
			}
        }
		//cout << "at" << value << endl;
    }
    cout << endl;
}

void print(char * table, int str_length, int buf_len){
	cout << buf_len << endl;
	for(int i = 0; i < buf_len; i++){
		if(i%8 == 0)
			printf("\033[0m\n");
		printf("\033[1;4%dm%s \033[0m", i%8,&table[ (str_length*i) ]);
		//printf("%d\n", str_length*i );
	}
	printf("\033[0m\n");
}

int main(int argc, char *argv[]){
    int x, y;//y height, x length
    x = 8;//85 data fields
    y = 7;//1 row of descriptions and 500 cities total =501
    int str_length = 32;//Length of the longest string in the table

    //Initializing data array, array apparently needs to be 1D and stored as chars, array should be new char[85*501*32]
    data = new char[x*y*str_length];

    file_open("dummy.csv", data, str_length, x);
    cout << "\033[1;31mPrinting Data from array: \033[0m" << endl;
    print(data, str_length, x*y);
    return 0;
}
