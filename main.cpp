#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;

void createPoly(int arr[], string str){
    int coe = 0;
    int power = 0;
    //s = 0 is for coe and s = 1 is for power
    int s = 0;
    string num = "";
    for (auto x : str)
    {
        if (x == ' ')
        {
            if(s == 0){
                coe = stoi(num);
                s = 1;
                num = "";
            }
            else{
                power = stoi(num);
                arr[power]+=coe;
                s=0;
                coe = 0;
                power = 0;
                num = "";
            }
        }
        else
        {
            num = num + x;
        }
    }
}

void printPoly(int arr[], int size){
    int x = 0;
    int printed = 0;
    for (int i=size; i>=0; i--){
        if(arr[i] == 0) x = 1;
        else if(i == size && arr[i] == 1) x = 2;
        else if(i == size && arr[i] == -1) x = 3;
        else if((i == size && arr[i] > 1) || (i != size && arr[i] < 1)) x =4;
        else if(i != size && arr[i] > 1) x = 5;
         switch (x){
               case 1:
                   //skip if coe = 0
                   break;
               case 2:
                   //it's the first term and the coe = 1
                   cout<<"X";
                   if(i!=1) cout<<"^"<<i;
                   printed = 1;
                   break;
               case 3:
                   //its the first term and the coe = -1
                   cout<<"-X";
                   if(i!=1) cout<<"^"<<i;
                   printed = 1;
                   break;
               case 4:
                    //its the first term and the coe is > 1
                    //its a middle term and coe is < 1
                    if(i!=size) cout<<" ";
                    cout<<arr[i]<<"X";
                    if(i!=1) cout<<"^"<<i;
                    printed = 1;
                    break;
               case 5:
                    //its a middle term and coe is > 1
                    if(printed == 1){
                        cout<<" + ";
                    }
                    cout<<arr[i]<<"X";
                    if(i!=1) cout<<"^"<<i;
                    printed = 1;
                    break;
               default:
                   break;
           }
    }
    cout<<endl;
}
           
    
void add(int arr1[], int arr2[], int m1, int m2){
    int tot = 0;
    if(m1>=m2){
        tot = m1;
    }
    else tot = m2;
    int sum[tot];
    for(int l = 0; l <= tot; l++){
        sum[l]=0;
    }
    for(int l = 0; l <= m1; l++){
        sum[l] += arr1[l];
    }
    for(int l = 0; l <= m2; l++){
        sum[l] += arr2[l];
    }
    printPoly(sum, tot);
}

void subtract(int arr1[], int arr2[], int m1, int m2){
    int tot = 0;
    if(m1>=m2){
        tot = m1;
    }
    else tot = m2;
    int dif[tot];
    for(int l = 0; l <= tot; l++){
        dif[l]=0;
    }
    for(int l = 0; l <= m1; l++){
        dif[l] += arr1[l];
    }
    for(int l = 0; l <= m2; l++){
        dif[l] -= arr2[l];
    }
    printPoly(dif, tot);
}

void multiply(int arr1[], int arr2[], int m1, int m2){
    int prod[m1+m2-1];
    for (int i = 0; i<m1+m2-1; i++){
        prod[i] = 0;
    }
    for (int i=0; i<m1; i++){
        for (int j=0; j<m2; j++){
          prod[i+j] += arr1[i]*arr2[j];
        }
    }
    printPoly(prod,m1+m2-1);
}

int main(){
    const char* filename = "/Users/albertrodriguez/Documents/VS/poly/poly/input.txt";
    ifstream infile(filename);
    int i;
    int c = 1;
    int max1 = 0;
    int max2 = 0;
    int p = 1;
    string first = "";
    string second = "";
    string s;
    while(infile){
        getline(infile,s);
        stringstream t(s);
        if(p == 1){
            while(t>>i){
                first += to_string(i)+" ";
                if(c % 2 == 0 && i > max1)max1 = i;
                c++;
            }
            c = 1;
            p++;
        }
        else if(p == 2){
            while(t>>i){
                second += to_string(i)+" ";
                if(c % 2 == 0 && i > max2)max2 = i;
                c++;
            }
        }
    }
    int p1[max1+1];
    for(int k = 0; k<=max1; k++){
        p1[k] = 0;
    }
    createPoly(p1, first);
    
    int p2[max2+1];
    for(int k = 0; k<=max1; k++){
        p2[k] = 0;
    }
    createPoly(p2, second);
    cout<<"The inputs:"<<endl;
    printPoly(p1, max1);
    printPoly(p2, max2);
    cout<<endl;
    cout<<"The outputs:"<<endl;
    cout<<"Sum: ";
    add(p1, p2, max1, max2);
    cout<<"Difference: ";
    subtract(p1, p2, max1, max2);
    cout<<"Product: ";
    int m = sizeof(p1)/sizeof(p1[0]);
    int n = sizeof(p2)/sizeof(p2[0]);
    multiply(p1, p2, m, n);
    cout<<endl;
}
