#include<bits/stdc++.h>
using namespace std;

#define pi 3.14159
typedef long double ll;

// r = tool radius
// t = actual sheet thickness
// to = initial sheet thickness
// h = step depth of the tool
// alpha = wall angle of part
// h1 = pressed amount of the forming tool
// h1_ = Sheet thickness thinning at the bottom of the sheet
// h1__ = Elastic deflection of sheet in vertical direction
// hs = Scallop height on the sheet surface

ll Forming_Force_SPIF(ll r, ll to, ll h, ll alpha_Degree, ll yield_stress, ll K, ll n) {
    ll alpha = alpha_Degree*pi/180;
    ll t = to*cos(alpha);                              // t = actual sheet thickness
    ll numerator = (t * (1-cos(alpha)));
    ll denomenator = (alpha*(3-(pi/2)))+1;

    ll h1_ = numerator/denomenator;                    // h1_ = Sheet thickness thinning at the bottom of the sheet

    ll h1__ = sqrt(2*h*t/r);                           // h1__ = Elastic deflection of sheet in vertical direction

    ll h1 = h1_ + h1__;                                // h1 = pressed amount of the forming tool

    ll slack1 = (r*r)-((h/(2*sin(alpha))) * (h/(2*sin(alpha))));
    ll hs = r - sqrt(slack1);                           // hs = Scallop height on the sheet surface

    ll l1 = r*acos((r-h1)/r);
    ll l2 = r*alpha;
    ll l3 = r*acos((r-hs)/r);

    ll slack2 = (r*(l2+l3)*(1-cos(alpha)))/l1; 
    ll S = (pi*r*(h1 + slack2))/2;                      // S = Surface area of ellipsoidal crown

    ll equi_strain = (2/sqrt(3))*log((2*r)/((2*r*cos(alpha))+(t*cos(alpha))));

    ll equi_stress = yield_stress + (K*(1-exp((-n)*equi_strain)));

    ll thickness_stress = (4*t*equi_stress)/(sqrt(3)*(r+2.5*t));

    ll Force_SPIF = thickness_stress * S;               // Force_SPIF = Analytical resultant force of SPIF
    return Force_SPIF;
}

ll Forming_Force_IHF(ll r, ll to, ll h, ll alpha_Degree, ll yield_stress, ll K, ll n) {
    ll Force_IHF = Forming_Force_SPIF(r, to, h, alpha_Degree, yield_stress, K, n);
    if(!isnan(Force_IHF)) {
        return Force_IHF/2;
    }
    else {
        return Force_IHF;
    }
}

int main() {
    ll r, to, h, alpha_Degree, yield_stress, K, n, Force_SPIF, Force_IHF;
    int option = 0;
    char choice = 'Y', s;
    while(choice == 'Y') {
        cout << "\n Select a option from the below list to proceed: ";
        cout << "\n 1.To calculate forming force of SPIF(Single Pass Incremental Forming)";
        cout << "\n 2.To calculate forming force of IHF(Incremental Hole Flanging)";
        cout << "\n 3.To exit from the program\n";
        cin >> option;

        if(option > 3) {
            cout << "\n Invalid option. Program terminates!";
        }
        if(option > 2) {
            break;
        }

        cout << "\n Enter data for calculation: ";
        cout << "\n Enter tool radius(r) in meter: ";
        cin >> r;
        cout << "\n Enter initial sheet thickness(to) in meter: ";
        cin >> to;
        cout << "\n Enter step depth of the tool(h) in meter: ";
        cin >> h;
        cout << "\n Enter wall angle of part(alpha) in degree: ";
        cin >> alpha_Degree;
        cout << "\n Enter yield stress of workpiece material in MPa: ";
        cin >> yield_stress;
        cout << "\n Enter the value of constant 'K' to calculate equivalent stress: ";
        cin >> K;
        cout << "\n Enter the value of constant 'n' to calculate equivalent stress: ";
        cin >> n;

        line:
        switch (option) {
            case 1: 
                Force_SPIF = Forming_Force_SPIF(r, to, h, alpha_Degree, yield_stress, K, n);
                if(isnan(Force_SPIF)) {
                    cout << "\n Some of the input values entered are not logically correct with the assumptions taken in this model!!";
                }
                else {
                    cout << "\n Analytical resultant forming force of SPIF is: " << Force_SPIF << " MN";
                }
                break;

            case 2: 
                Force_IHF = Forming_Force_IHF(r, to, h, alpha_Degree, yield_stress, K, n);
                if(isnan(Force_IHF)) {
                    cout << "\n Some of the input values entered are not logically correct with the assumptions taken in this model!!";
                }
                else {
                    cout << "\n Analytical resultant forming force of IHF is: " << Force_IHF << " MN";
                }
                break;
        }
        
        cout << "\n Do you want to calculate other forces using same input(Y/N): ";
        cin >> s;
        if(s == 'Y') {
            cout << "\n Select a option from the below list to proceed: ";
            cout << "\n 1.To calculate forming force of SPIF(Single Pass Incremental Forming)";
            cout << "\n 2.To calculate forming force of IHF(Incremental Hole Flanging)";
            cout << "\n 3.To exit from the program\n";
            cin >> option;

            if(option > 3) {
                cout << "\n Invalid option. Program terminates!";
            } 
            if(option > 2) {
                break;
            }
            
            goto line;
        }
        cout << "\n Do you want to calculate other forces using different input(Y/N): ";
        cin >> choice;
    }
    return 0;
}