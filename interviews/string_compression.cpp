#include <iostream>
#include <string>

using namespace std;

string stringCompression(string inputString)
{
    if (inputString.length() == 0)
    {
        return "";
    }
    string output = "";
    output += inputString[0];
    int count = 1;
    for (int i = 1; i < inputString.length(); i++)
    {
        if (inputString[i] == inputString[i - 1])
        {
            count++;

            if (i == inputString.length() - 1)
            {
                output += to_string(count);
            }
        }
        else
        {
            if (count > 1)
            {
                output += to_string(count);
                output += inputString[i];
            }
            else
            {
                output += inputString[i];
            }
            count = 1;
        }
    }
    return output;
}

int main(){
    cout << stringCompression("aaaaaaaaaaaaaaaabbbccd") << endl;
    return 0;
}