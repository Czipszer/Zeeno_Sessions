#include <iostream>
#include <string>


using namespace std;

bool digit_checker(string str){

    for (int i = 0; i < str.length(); i++){

        if (isdigit(str[i]) == false){
            return false;
        }
    }
    return true;
}

bool operator_checker(string oprt, bool check_rov){
    if (oprt.length() != 1){
        return false;
    }

    if (oprt == "+" || oprt == "-" || oprt == "*" || oprt == "/"){
        return true;
    }else if (check_rov && oprt == "="){
        return true; 
    }else{
        return false;
    }
}

int main()
{
    
    string just_input;

    int first_num = ('\0');

    char operat;

    int second_num;

    

    while (1){

        if (first_num == ('\0')){
        
            while(1){
                cout << "Input first number: " << endl;
                cin >> just_input;

                if (digit_checker(just_input) == false){
                    cout << "Not a number!" << endl;
                }else{
                    first_num = stoi(just_input);
                    break;
                }
            }
            
            while(1){
                
            
            cout << " Input operator (+,-,*,/): ";
            cin >> just_input;

            if (operator_checker(just_input, false) == false){
                cout << "Invalid input!" << endl;
             }else{
                    operat = just_input[0];
                    break;
            }
            }

            
        }
        
        while(1){
            cout << "Input second number: " << endl;
            cin >> just_input;

            if (digit_checker(just_input) == false){
                    cout << "Not a number!" << endl;
                }else{
                    second_num = stoi(just_input);
                    break;
                }

        }
        

        if (operat == '+'){
            first_num = first_num + second_num;

        } else if (operat == '-'){

            first_num = first_num - second_num;
        } else if (operat == '*'){

            first_num = first_num*second_num;
        } else if (operat == '/'){

            first_num = first_num/second_num;
        }

        
        while(1){
            cout << "Actural result is "<< first_num << ". Continue with next operator (+,-,*,/) of put (=) to finish"<< endl;
            cin >> just_input;
                
            if (operator_checker(just_input, true) == false){
                cout << "Invalid input!" << endl;
             }else{
                    operat = just_input[0];
                    break;
            }
            }
        

        if (operat == '='){
            cout << "The result is: " << first_num << endl;
            break;
        }else{

        }
        


    }
    

}