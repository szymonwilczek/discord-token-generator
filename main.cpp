#include <iostream>
#include<cstdlib>
#include <chrono>
#include <ctime>
#include <random>

static const std::string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

using namespace std;

int uid() {
    random_device rd; // obtain a random number from hardware
    mt19937 gen(rd()); // seed the generator
    uniform_int_distribution<> distr(12300000000000000000, 9999999999999999999); // define the range
    return distr(gen);
}

const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    // Visit http://en.cppreference.com/w/cpp/chrono/c/strftime
    // for more information about date/time format
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}


//decode current date time to base64
string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
    string ret;
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (in_len--) {
        char_array_3[i++] = *(bytes_to_encode++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++)
                ret += base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            ret += base64_chars[char_array_4[j]];

        while((i++ < 3))
            ret += '=';

    }

    return ret;

}

//generate random hmac
string hmac() {
    string hmac;
    for (int i = 0; i < 32; i++) {
        int r = rand() % 16;
        char c = (char) (r < 10 ? '0' + r : 'a' + r - 10);
        hmac += c;
    }
    return hmac;
}

void Write()
{
    cout << "| ---------------------------------------------------------------------------------------- |" << endl;
    cout << "|\t\t\t\t   Discord Token Generator                                 |" << endl;
    cout << "| ---------------------------------------------------------------------------------------- |" << endl;
    cout << "| Token: " << base64_encode((unsigned char*)currentDateTime().c_str(), currentDateTime().length()) << "." << uid() << "." << hmac() << "           |" <<endl;
    cout << "| ---------------------------------------------------------------------------------------  |" << endl;

}





int main() {
    Write();
    return 0;
}
