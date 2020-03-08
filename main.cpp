#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
/*
 Takes an array and a string and breaks the string up accroding to white space as the delimiter.
 places all the ints in the string into an array
 */
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
        else num = num + x;
    }
}

/*
 a helper function that prints an array as a cononical form polynomial
 */
void printPoly(int arr[], int size, ofstream &output){
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
                   output<<"X";
                   if(i!=1){
                       cout<<"^"<<i;
                       output<<"^"<<i;
                 
                   }
                   printed = 1;
                   break;
               case 3:
                   //its the first term and the coe = -1
                   cout<<"-X";
                   output<<"-X";
                   if(i!=1){
                       cout<<"^"<<i;
                       output<<"^"<<i;
                   }
                   printed = 1;
                   break;
               case 4:
                    //its the first term and the coe is > 1
                    //its a middle term and coe is < 1
                    if(i!=size){
                        cout<<" ";
                        output<<" ";
                    }
                    cout<<arr[i]<<"X";
                    output<<arr[i]<<"X";
                    if(i!=1){
                         cout<<"^"<<i;
                        output<<"^"<<i;
                    }
                    printed = 1;
                    break;
               case 5:
                    //its a middle term and coe is > 1
                    if(printed == 1){
                        cout<<" + ";
                        output<<" + ";
                    }
                    cout<<arr[i]<<"X";
                    output<<arr[i]<<"X";
                    if(i!=1){
                        cout<<"^"<<i;
                        output<<"^"<<i;
                    }
                    printed = 1;
                    break;
               default:
                   break;
           }
    }
    cout<<endl;
}
           
    
void add(int arr1[], int arr2[], int m1, int m2, ofstream &output){
    int tot = 0;
    if(m1>=m2){
        tot = m1;
    }
    else tot = m2;
    int sum[tot];
    for(int l = 0; l <= tot; l++)
        sum[l]=0;
    for(int l = 0; l <= m1; l++)
        sum[l] += arr1[l];
    for(int l = 0; l <= m2; l++)
        sum[l] += arr2[l];
    printPoly(sum, tot, output);
}

void subtract(int arr1[], int arr2[], int m1, int m2, ofstream &output){
    int tot = 0;
    if(m1>=m2) tot = m1;
    else tot = m2;
    int dif[tot];
    for(int l = 0; l <= tot; l++)
        dif[l]=0;
    for(int l = 0; l <= m1; l++)
        dif[l] += arr1[l];
    
    for(int l = 0; l <= m2; l++)
        dif[l] -= arr2[l];
    printPoly(dif, tot, output);
}

void multiply(int arr1[], int arr2[], int m1, int m2, ofstream &output){
    int prod[m1+m2-1];
    for (int i = 0; i<m1+m2-1; i++)
        prod[i] = 0;
    for (int i=0; i<m1; i++){
        for (int j=0; j<m2; j++){
          prod[i+j] += arr1[i]*arr2[j];
        }
    }
    printPoly(prod,m1+m2-1, output);
}

int main(){
    const char* filename = "/Users/albertrodriguez/Documents/VS/poly/poly/input.txt";
    ifstream infile(filename);
    ofstream output;
    output.open("output.txt");
    int i;
    int c = 1;
    int max1 = 0;
    int max2 = 0;
    int p = 1;
    string first = "";
    string second = "";
    string s;
    //turns each line of ints into a string of ints and finds largest exponent to figure out
    //the size of the array that we need to create
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
                if(c % 2 == 0 && i > max2) max2 = i;
                c++;
            }
        }
    }
    //creates the first polynomial array and initializes it
    int p1[max1+1];
    for(int k = 0; k<=max1; k++)
        p1[k] = 0;
    
    createPoly(p1, first);
    
    //creates the second polynomial array and initializes it
    int p2[max2+1];
    for(int k = 0; k<=max1; k++)
        p2[k] = 0;
    
    createPoly(p2, second);
    
    //print the outputs 
    cout<<"The inputs:"<<endl;
    output<<"The inputs:"<<endl;
    printPoly(p1, max1, output);
    printPoly(p2, max2, output);
    cout<<endl;
    output<<"\n";
    cout<<"The outputs:"<<endl;
    cout<<"Sum: ";
    output<<"The outputs:"<<endl;
    output<<"Sum: ";
    add(p1, p2, max1, max2, output);
    cout<<"Difference: ";
    output<<"Difference: ";
    subtract(p1, p2, max1, max2, output);
    cout<<"Product: ";
    output<<"Product: ";
    int m = sizeof(p1)/sizeof(p1[0]);
    int n = sizeof(p2)/sizeof(p2[0]);
    multiply(p1, p2, m, n, output);
    cout<<endl;
    output<<endl;
    output.close();
}
