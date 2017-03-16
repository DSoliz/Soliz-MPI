#include <iostream>
#include <fstream>
using namespace std;

string ** data;

void file_open(string file_name, string ** table){
    ifstream file (file_name);
    cout << "\033[1;31m" << file_name << ":\033[0m"<< endl;//display file name
    string value;
    int x = 0;
    int y = 0;
    while (file.good()){//while file hasnt reached EOF
        int c = file.peek();//Peek next character
        if(c == '\n'){
            y++;
            x = 0;
        }
        if(c == '"'){//if it is between quotes read until de next quote
            file.get();
            getline ( file, value, '"' );
            if(file.peek() == ','){
                file.get();
            }
        }else{//else read until the next comma
            getline ( file, value, ',' );
        }
        //cout << value << "  ";//string( value, 0, value.length() )
        table[y][x] = value;
        cout << table[y][x] << "  ";
        x++;
    }
    cout << endl;
}

int main(int argc, char *argv[]){
    int x, y;//y height, x length
    x = 85;//85 data fields
    y = 501;//1 row of descriptions and 500 cities

    //Initializing data array
    data = new string*[y];
    for(int i=0; i<y; i++)
        data[i] = new string[x];

    file_open("dummy.csv", data);
    return 0;
}
