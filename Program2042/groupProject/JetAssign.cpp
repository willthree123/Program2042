#include <iostream>
#include <string>
#include <unistd.h>
#include <fstream>
#include <vector>
using namespace std;
unsigned int microsecond = 1000000; 

class Cus_info {
    public:
    string name;
    string id;
    string location;
};

vector<string> all_cus_info;

void open_file(){
	bool check;
	fstream file;
	file.open("store.txt");
		check = file.is_open();
	file.close();
	if(!check){
		file.open("store.txt");
		file.close();
	}
}

void read_file(){
	fstream file;
	string input;
	all_cus_info.clear();
	file.open("store.txt", fstream :: in);
		while (getline(file,input)){
			all_cus_info.push_back(input);
		}
}

void write_file(string the_line){
	fstream file;
	string input;
	bool check;
	file.open("store.txt", fstream :: app);
		file << the_line << endl;
	file.close();
}

bool check_name(string b){
    int s_length = 0;
	s_length = b.length();
	char check[s_length];
	for (int i = 0; i < s_length; i++)
	{
		check[i] = b[i];
		if (((check[i] < 'A') || (check[i] > 'Z')) && ((check[i] < 'a') || (check[i] > 'z')) && (!(check[i] == ' ')) ){
			return 0;
		}
	}
	return 1;
}

string cap_name(string change){
    int s_length = 0;
    string combine;
    s_length = change.length();
	char to_cap[s_length];
	for (int i = 0; i < s_length; i++)
	{
		to_cap[i] = change[i];
        if ((i == 0) || (change[i-1] == ' ')){
            if ((to_cap[i] >= char(97)) && (to_cap[i] <= char(122))){
                to_cap[i] = char(int(to_cap[i]) - 32);
            }
        }
	}
    for (int i = 0; i < s_length; i++)
	{
		combine = combine + to_cap[i];
	}
    return combine;
}



string cap(string change){
    int s_length = 0;
    string combine;
    s_length = change.length();
	char to_cap[s_length];
	for (int i = 0; i < s_length; i++)
	{
		to_cap[i] = change[i];
		if ((to_cap[i] >= char(97)) && (to_cap[i] <= char(122))){
			to_cap[i] = char(int(to_cap[i]) - 32);
		}
	}
    for (int i = 0; i < s_length; i++)
	{
		combine = combine + to_cap[i];
	}
    return combine;
}

bool check_id(string change){
	int s_length = 0;
	s_length = change.length();
	char check[s_length];
	for (int i = 0; i < s_length; i++)
	{
		check[i] = change[i];
		if (((check[i] < '0') || (check[i] > '9')) && ((check[i] < 'A') || (check[i] > 'Z')) && ((check[i] < 'a') || (check[i] > 'z')) ){
			return 0;
		}
	}
	return 1;
	
}

bool check_location(string b){
    int s_length = 0;
	s_length = b.length();
	if((!((s_length == 2) || (s_length == 3)))){
		return 0;
	}
	if ((b[s_length -1] < 'A') || (b[s_length -1] > 'F')){
		return 0;
	}
	if(s_length == 2){
		if ((b[0]<'1') || (b[0]>'9')){
			return 0;
		}
	}
	else{
		if ((!(b[0]=='1'))||(b[1] < '0')||(b[1]>'3')){
			return 0;
		}
	}
	
	return 1;
}

bool check_dup_id (string id){
	int len;
	char a , b;
	bool check[id.length()];
	for (string temp : all_cus_info ){
		for(int i = 0; i < id.length() ; i++){
			a = id[i];
			b = temp[temp.length() - id.length() + i];
			if (a == b){
				check[i] = 1;
			}
			else {check[i] = 0;}
		}
		int count = 0;
		for (int j = 0 ; j < id.length() ; j++){
				if (check[j]){
					count ++ ;
				}
			}
		if (count == id.length()){
			return 0 ;
		}
	}
	return 1;
}

void write_whole_file(){
	fstream file;
	string input;
	bool check;
	file.open("store.txt", fstream :: out);
		for (string temp : all_cus_info){
			file << temp << endl;
		}
	file.close();
}

int find(string pk){
	int i = 0;
	string::size_type position;
	for (string temp : all_cus_info){
		i++;
		position = temp.find(pk);
		if (!(position == temp.npos)){
			return i;
		}
	}
	return 1000;
}


void add(){
    system("CLS");
    Cus_info add_new;
    bool check = 0;
    string all;
    open_file();
    read_file();
    cout << "This is the fuction of add assignment!"<< endl;
    do{
        cout << "Please type in your username" << endl;
        cout << "If this is not the fuction you want please type q instead : ";
        cin.ignore();
        getline(cin ,add_new.name );
        if (add_new.name == "q"){
            return;
        }
        check = check_name(add_new.name);
        if(!(check)){
            cout << "You typed in inappropriate letters, please type in again" << endl;
        }
    }while(!(check));
    check = 0;
    add_new.name = cap_name(add_new.name);
    do{
        cout << "Please enter your passport ID, it is ok if you input lower case characters : ";
        getline(cin , add_new.id);
        check = check_id(add_new.id);
        if(!(check)){
            cout << "You typed in inappropriate letters, please type in again" << endl;
        }
    } while(!(check));
    check = 0;
    add_new.id = cap(add_new.id);
    do
    {
        cout << "Please enter your seat location, it is ok if you input lower case characters : ";
        getline(cin , add_new.location);
        add_new.location = cap(add_new.location);
        check = check_location(add_new.location);
        if(!(check)){
            cout << "You does not type a valid seat location, please type again" << endl;
            goto skipcheck;
        }
        check = check_dup_id(add_new.location);
        if(!(check)){
            cout << "The seat location has been taken, please type another seat location" << endl;
        }
    skipcheck:
    cout << "";
    } while (!(check));
    all = add_new.name + "/" + add_new.id + "/" + add_new.location;
    write_file(all);
    cout << "input successful!"<< endl;

    system("pause");
}

void del(){
    system("CLS");
    Cus_info find_del;
    bool check = 0;
    string all;
    string sure;
    do{
        del_start:cout << ""; 
        do{
            cout << "Please type in your username" << endl;
            cout << "If this is not the fuction you want please type q instead : ";
            cin.ignore();
            getline(cin ,find_del.name );
            if (find_del.name == "q"){
                return;
            }
            check = check_name(find_del.name);
            if(!(check)){
                cout << "You typed in inappropriate letters, please type in again" << endl;
            }
        }while(!(check));
        check = 0;
        find_del.name = cap_name(find_del.name);
        do{
            cout << "Please enter your passport ID, it is ok if you input lower case characters : ";
            getline(cin , find_del.id);
            check = check_id(find_del.id);
            if(!(check)){
                cout << "You typed in inappropriate letters, please type in again" << endl;
            }
        } while(!(check));
        find_del.id = cap(find_del.id);
        all = find_del.name + "/" + find_del.id;
        open_file();
        read_file();
        if(find(all)==1000){
            cout << "Not found! Please check your input and type again" << endl;
        }else {cout << "Found!" << endl;}
    } while(find(all)==1000);
	if (!(find(all)==1000)){
        do{
            cout << "Are you sure that you want to delete this record?"<< endl;
            cout << "Type 1 for yes. Type 2 for no" << endl;
            cin >> sure;
            if (!(sure.length() == 1)){
                cout << "1 layer"<< endl;
                cout << "Invalid input"<<endl;
            }else{
                if((!(sure[0] == '1'))&&(!(sure[0] == '2'))){
                    cout << "Invalid input"<<endl;
                    cout << "2 layer"<< endl;
                }
            }
        } while((!(sure.length() == 1))||((!(sure[0] == '1'))&&(!(sure[0] == '2'))));
        if(sure[0] == '1'){
            all_cus_info.erase(all_cus_info.begin()+find(all)-1);
            write_whole_file();
            read_file();
            cout << all << " is successfully deleted"<<endl;
        } else {goto del_start;}
	}
    system ("pause");
}

void show_intro(){
    system("CLS");
    system("Color 03");
    cout << "*************************"<<endl;
    usleep(microsecond/5);
    cout << "*Welcome to HKCC Airline*"<<endl;
    usleep(microsecond/5);
    cout << "*************************"<<endl;
    usleep(microsecond);
    cout << R"(
,ggg,        gg ,ggg,        gg      ,gggg,       ,gggg,  
dP""Y8b       88dP""Y8b       dP    ,88"""Y8b,   ,88"""Y8b,
Yb, `88       88Yb, `88      d8'   d8"     `Y8  d8"     `Y8
`"  88       88 `"  88    ,dP'   d8'   8b  d8 d8'   8b  d8
     88aaaaaaa88     88aaad8"    ,8I    "Y88P',8I    "Y88P'
    88"""""""88     88""""Yb,   I8'          I8'          
    88       88     88     "8b  d8           d8           
     88       88     88      `8i Y8,          Y8,          
    88       Y8,    88       Yb,`Yba,,_____, `Yba,,_____, 
     88       `Y8    88        Y8  `"Y8888888   `"Y8888888        
        )" << '\n';
        usleep(1*microsecond);
    system("Color 07");


}

void loading_animation(){
        system("CLS");
        cout <<"Loading";
        usleep(microsecond/5);
        cout << "." ;
        usleep(microsecond/5);
        cout << "." ;
        usleep(microsecond/5);
        cout << "." << endl;
        usleep(microsecond/2);
}

void menu(){
    string user_input = "-1"; 
    char user_input_char ='p';
    do{
        system("CLS");
        cout << "Welcome to the HKCC Airline's Airplane seating assignment system" << endl;
        cout << "*** main menu ***" << endl;
        cout << "[1] Add an assignment" << endl;
        cout << "[2] Delete an assignment" << endl;
        cout << "[3] Add assignments in batch" << endl;
        cout << "[4] Show latest seating plan" << endl;
        cout << "[5] Show details" << endl;
        cout << "[6] Exit" << endl;
        cout << "*****************"<< endl;
        cout << "Option (1-6): ";
        cin >> user_input;
        if (!(user_input.length()== 1)){
            cout << "Invalid input, please input again"<< endl;
            usleep(microsecond);
        }
        else{
            user_input_char = user_input[0];
            switch (user_input_char) {
                case '1': add(); usleep(microsecond); break;
                case '2': del(); usleep(microsecond); break;
                case '3': cout << "show"; usleep(microsecond); break;
                case '4': cout << "this"; usleep(microsecond); break;
                case '5': cout << "shit";  usleep(microsecond);break;
                case '6': cout << "Thank you for using this system";               
                                  usleep(2*microsecond);
                                  system("CLS");
                                  break;
                default : cout << "Invalid input, please input again"<< endl;
                          usleep(microsecond); break;
            }
        }
    }while ((!(user_input.length()== 1))||(!(user_input_char=='6')));
}

int main(){ 
    show_intro();
    loading_animation();
    menu();
    return 0;
}