///////////////////////////////////
//      Abdelrahman 2100347      //
///////////////////////////////////
#include<bits/stdc++.h>

#define ee <<" "<<
#define nn <<"\n"
using namespace std;

//"$GPGGA,202530.00,5109.0262,N,11401.8407,W,1,40,0.5,1097.36,M,-17.00,M,18,TSTR*61"
string Correct_start = "$GPGGA,";
int n = Correct_start.size();
string lat, lon;

bool chk_fix(string s){
    int i = n;
    int HowManyComma = 0;
    while (s[i]!='*')
    {
        if (s[i] == ',')
            HowManyComma++;
        if(HowManyComma == 5) {
            if (s[i+1]=='1')
                return 1;
            else 
                return 0;
        }
        i++;
    }
    return 0;
}

bool solve(string s) {
    if (!chk_fix(s))
        return 0;
        
    int i;
    string a = "";
    for (i = 0; i < n; i++)
        if (s[i]!=Correct_start[i])
           return 0; 

    while (s[i++]!=',');
    
    while (s[i]!=',')
        a+=s[i++];

    lon = a; i+=3; // ",N,"
    a = "";
    while (s[i]!=',')
        a+=s[i++];

    lat = a;
    return 1;
}

int main()
{
    vector<pair<string, string>> pairs;
    pair<string, string> p[100];

    ofstream output("cordenates.txt"); // open a file to perform write operation
    ifstream input("input.txt"); // open a file to perform read operation

    if (input.is_open() && output.is_open()) {
        string line;

        while (getline(input, line)) {
            if (solve(line))
                pairs.emplace_back(lon, lat);
        }

        for (auto& pair : pairs) {
            output<<pair.first ee pair.second nn;
            cout << "(" << pair.first << ", " << pair.second << ")" nn;
        }

        // Close files
        input.close();
        output.close();
    } else {
        cout << "Unable to open file" << endl;
    }

    cout<< "Correct Cordinates: "<< pairs.size() <<endl;
    cout<<"Start Point: " << pairs[0].first ee pairs[0].second nn;
    cout<<"End Point:   " << pairs.back().first ee pairs.back().second nn;

//////////////////// Run python code ////////////////////////
    string command = "python drawing_in_maps.py";
    system(command.c_str());
}
