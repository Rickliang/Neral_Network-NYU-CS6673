
//  Neural Networking Assignment 7
//  Created by Yukun Liang(N14194314) on 11/18/14.
//  Contact through rickliang@nyu.edu

//I desgnated three corrupted input signals to test the roubusty of the Network. All three of them is put in the main() but annotated

#include <iostream>
#include<iomanip>

#define IN_ROW 15
#define OUT_ROW 3   
using namespace std;

//initialize given inputs and outputs
int Cin[IN_ROW] = {-1,1,1,1,-1,-1,1,-1,-1,1,-1,-1,-1,1,1};
int Din[IN_ROW] = {1,1,-1,1,-1,1,1,-1,1,1,-1,1,1,1,-1};
int Xin[IN_ROW] = {1,-1,1,1,-1,1,-1,1,-1,1,-1,1,1,-1,1};

int Cout[OUT_ROW] = {-1,1,1};
int Dout[OUT_ROW] = {1,-1,1};
int Xout[OUT_ROW] = {1,1,-1};


//initialize weights and bias
float weight [3][IN_ROW] = {0,};
float biasx [IN_ROW] = {0,};
float biasy [OUT_ROW] = {0,};
//float bias = 0;

//define corrupted input signals
int Cin_missing[IN_ROW] = {-1,1,0,1,0,0,1,-1,-1,1,0,0,0,1,0}; //this C' input blurs at 3rd, 5th, 6th, 11th, 12th,13th and last element.
int Din_mistaking[IN_ROW] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};    //this X' input flipped every -1 into 1 except last two rows.
int Xin_missing_and_mistaking[IN_ROW] = {0,1,1,0,0,0,0,1,0,0,0,0,0,-1,0};   //this D' input not only blurs at 5th and 9th, but also flipped every -1 into 1.

//function definition
void Calculate_weight_bias(const int[],const int[],const int[]);    //get weight with raw inputs
//void BAM(const int[]);  //run neural network bidirectionally, and visually print the outcome
void XtoY(int [], int[], int );   //give input ,output and a indicator of bias as parameters
void YtoX(int [], int[], int );
int printer(int []);  //visualize the character
int trans_func(int);  //transfer function


int main()
{
    int *y = new int [OUT_ROW]; //to store outcome of right side
    int *x = new int [IN_ROW];  //to store outcome of left side
    int noisy_Xout[OUT_ROW] = {0,1,-1};
    int mistook_CX[OUT_ROW] = {-1,1,-1};
    
    Calculate_weight_bias(Cin,Din,Xin);  //calculate weight
    
    cout<<"!!!!!ORDINARY CASE"<<endl;
    cout<<"===========================\nWhen x = C, yin = ";
    XtoY(Cin, y, 0);
    cout<<"\n\tSequentially, on opposite direction, xin = ";
    YtoX(y, x, 0);
    
    cout<<"\n===========================\nWhen x = D, yin = ";
    XtoY(Din, y, 0);
    cout<<"\n\tSequentially, on opposite direction, xin = ";
    YtoX(y, x, 0);
    
    cout<<"\n===========================\nWhen x = X, yin = ";
    XtoY(Xin, y, 0);
    cout<<"\n\tSequentially, on opposite direction, xin = ";
    YtoX(y, x, 0);
    
    cout<<"\n!!!!!NOISY CASE from right to left"<<endl;
    cout<<"===========================\nWhen activation of Y become similar but not exact X: "<< noisy_Xout[0]<<noisy_Xout[1]<<noisy_Xout[2] <<" xin = ";
    YtoX(noisy_Xout, x, 0);
    cout<<"\n\tSequentially, on opposite direction, yin = ";
    XtoY(x, y, 0);
    
    
    cout<<"\n\n!!!!!MISTOOK CASE from right to left"<<endl;
    cout<<"===========================\nWhen activation of Y have characteristic of both X and C, xin = ";
    YtoX(mistook_CX, x, 0);
    cout<<"\n\tSequentially, on opposite direction, yin = ";
    XtoY(x, y, 0);
    
    
    cout<<"\n\n!!!!!MISTOOK CASE from right to left WITH bias"<<endl;
    cout<<"===========================\nWhen activation of Y have characteristic of both X and C, xin = ";
    YtoX(mistook_CX, x, 1);
    cout<<"\n\tSequentially, on opposite direction, yin = ";
    XtoY(x, y, 1);

    cout<<"\n\n===========================\nWhen x = C', yin = ";
    XtoY(Cin_missing, y, 0);
    cout<<"\n\tSequentially, on opposite direction, xin = ";
    YtoX(y, x, 0);

    cout<<"\n===========================\nWhen x = D', yin = ";
    XtoY(Din_mistaking, y, 0);
    cout<<"\n\tSequentially, on opposite direction, xin = ";
    YtoX(y, x, 0);
    
    cout<<"\n===========================\nWhen x = X', yin = ";
    XtoY(Xin_missing_and_mistaking, y, 0);
    cout<<"\n\tSequentially, on opposite direction, xin = ";
    YtoX(y, x, 0);
    cout<<"And we input into round 2:"<<endl;
    XtoY(x, y, 0);
    cout<<"\n\tSequentially, on opposite direction, xin = ";
    YtoX(y, x, 0);


    
    cout<<"\n===========================\nWhen x = D' but works WITH bias, yin = ";
    XtoY(Xin_missing_and_mistaking, y, 1);
    cout<<"\n\tSequentially, on opposite direction, xin = ";
    YtoX(y, x, 1);


//    BAM(Cin);
////    BAM(Cin_missing);
//    cout<<"===========================\nWhen x = D, yin = ";
//    BAM(Din);
////    BAM(Din_mistaking);
//    cout<<"===========================\nWhen x = X, yin = ";
//    BAM(Xin);
////    BAM(Xin_missing_and_mistaking);
    
    delete [] y;    delete [] x;
    return 0;
}

void Calculate_weight_bias(const int c[],const int d[],const int x[]){
    cout<<"At first we get the transfer of weight matrix"<<endl;
    for (int i=0; i<3; i++) {
        for (int j=0; j<IN_ROW; j++) {
            weight[i][j] += Cout[i] * c[j];
            weight[i][j] += Dout[i] * d[j];
            weight[i][j] += Xout[i] * x[j];
            
            cout<<weight[i][j]<<" ";
        }
        cout << endl;
    }
    
    cout<<"and the bias on right side are"<<endl;
    for (int i=0; i<OUT_ROW; i++) {
        biasy[i] = Cout[i] + Xout[i] + Dout[i];
        cout<<biasy[i]<<" ";
    }
    cout<<endl;
    
    cout<<"and the bias on left side are"<<endl;
    for (int i=0; i<IN_ROW; i++) {
        biasx[i] = Cin[i] + Xin[i] + Din[i];
        cout<<biasx[i]<<" ";
    }
    cout<<endl;
}



int trans_func(const int x){
    if (x>0)
        return 1;
    else if(x<0)
        return -1;
    else
        return 0;
}

void XtoY( int in[] , int y[], int bias_flag){
    
    int yin[OUT_ROW] = {0,};
    
    //Left--->>Right
    for (int i=0; i<OUT_ROW; i++) {
        for (int j=0; j<IN_ROW; j++) {
            yin[i] += weight[i][j] * in[j];
            
        }
        //if bias counts
        if (bias_flag) {
            yin[i] += biasy[i];
        }
        
        cout<<yin[i]<<" ";
    }
    
    cout<<"\n\tthus, y = ";
    for (int i=0; i<OUT_ROW; i++) {
        y[i] = trans_func(yin[i]);
        cout<< y[i] <<" ";
    }

}


void YtoX(int in[], int x[], int bias_flag){
    
    int xin[IN_ROW] = {0,};
    
    //Left<<---Right
    for (int i = 0; i<IN_ROW; i++) {
        for (int j=0; j<OUT_ROW; j++) {
            xin[i] += weight[j][i] * in[j];
        }
        //if bias counts
        if (bias_flag) {
            xin[i] += biasx[i];
        }
        
        cout<<xin[i]<<" ";
    }
    
    cout<<"\n\tthus, x = ";
    for (int i=0; i<IN_ROW; i++) {
        x[i] = trans_func(xin[i]);
        cout<< x[i] <<" ";
    }
    
    printer(x);

}

int printer(int digit[]){
    cout<<"\n\tIf we print it out, it will be like:\n\t";
    
    for (int i = 0; i<IN_ROW; i++) {
        if(digit[i]==1)
            cout<<"# ";
        else if(digit[i]==-1)
            cout<<". ";
        else
            cout<<"* ";
        
        if ((i%3)==2)
            cout<<"\n\t";
    }
    return 0;
}

/*
 
 At first we get weight matrix
 3 -1 -1 1 -1 3 -1 1 1 1 -1 3 3 -1 -1
 -1 -1 3 1 -1 -1 -1 1 -3 1 -1 -1 -1 -1 3
 -1 3 -1 1 -1 -1 3 -3 1 1 -1 -1 -1 3 -1
 and the bias on right side are
 1 1 1
 and the bias on left side are
 1 1 1 3 -3 1 1 -1 -1 3 -3 1 1 1 1
 !!!!!ORDINARY CASE
 ===========================
 When x = C, yin = -15 13 17
	thus, y = -1 1 1
	Sequentially, on opposite direction, xin = -5 3 3 1 -1 -5 3 -3 -3 1 -1 -5 -5 3 3
	thus, x = -1 1 1 1 -1 -1 1 -1 -1 1 -1 -1 -1 1 1
	If we print it out, it will be like:
	. # #
	# . .
	# . .
	# . .
	. # #
	
 ===========================
 When x = D, yin = 15 -13 15
	thus, y = 1 -1 1
	Sequentially, on opposite direction, xin = 3 3 -5 1 -1 3 3 -3 5 1 -1 3 3 3 -5
	thus, x = 1 1 -1 1 -1 1 1 -1 1 1 -1 1 1 1 -1
	If we print it out, it will be like:
	# # .
	# . #
	# . #
	# . #
	# # .
	
 ===========================
 When x = X, yin = 17 13 -15
	thus, y = 1 1 -1
	Sequentially, on opposite direction, xin = 3 -5 3 1 -1 3 -5 5 -3 1 -1 3 3 -5 3
	thus, x = 1 -1 1 1 -1 1 -1 1 -1 1 -1 1 1 -1 1
	If we print it out, it will be like:
	# . #
	# . #
	. # .
	# . #
	# . #
	
 !!!!!NOISY CASE from right to left
 ===========================
 When activation of Y become similar but not exact X: 01-1 xin = 0 -4 4 0 0 0 -4 4 -4 0 0 0 0 -4 4
	thus, x = 0 -1 1 0 0 0 -1 1 -1 0 0 0 0 -1 1
	If we print it out, it will be like:
	* . #
	* * *
	. # .
	* * *
	* . #
	
	Sequentially, on opposite direction, yin = 1 13 -15
	thus, y = 1 1 -1
 
 !!!!!MISTOOK CASE from right to left
 ===========================
 When activation of Y have characteristic of both X and C, xin = -3 -3 5 -1 1 -3 -3 3 -5 -1 1 -3 -3 -3 5
	thus, x = -1 -1 1 -1 1 -1 -1 1 -1 -1 1 -1 -1 -1 1
	If we print it out, it will be like:
	. . #
	. # .
	. # .
	. # .
	. . #
	
	Sequentially, on opposite direction, yin = -15 13 -15
	thus, y = -1 1 -1
 
 !!!!!MISTOOK CASE from right to left WITH bias
 ===========================
 When activation of Y have characteristic of both X and C, xin = -2 -2 6 2 -2 -2 -2 2 -6 2 -2 -2 -2 -2 6
	thus, x = -1 -1 1 1 -1 -1 -1 1 -1 1 -1 -1 -1 -1 1
	If we print it out, it will be like:
	. . #
	# . .
	. # .
	# . .
	. . #
	
	Sequentially, on opposite direction, yin = -6 22 -6
	thus, y = -1 1 -1
 
 ===========================
 When x = C', yin = -6 2 14
	thus, y = -1 1 1
	Sequentially, on opposite direction, xin = -5 3 3 1 -1 -5 3 -3 -3 1 -1 -5 -5 3 3
	thus, x = -1 1 1 1 -1 -1 1 -1 -1 1 -1 -1 -1 1 1
	If we print it out, it will be like:
	. # #
	# . .
	# . .
	# . .
	. # #
	
 ===========================
 When x = D', yin = 9 -3 1
	thus, y = 1 -1 1
	Sequentially, on opposite direction, xin = 3 3 -5 1 -1 3 3 -3 5 1 -1 3 3 3 -5
	thus, x = 1 1 -1 1 -1 1 1 -1 1 1 -1 1 1 1 -1
	If we print it out, it will be like:
	# # .
	# . #
	# . #
	# . #
	# # .
	
 ===========================
 When x = X', yin = 0 4 -4
	thus, y = 0 1 -1
	Sequentially, on opposite direction, xin = 0 -4 4 0 0 0 -4 4 -4 0 0 0 0 -4 4
	thus, x = 0 -1 1 0 0 0 -1 1 -1 0 0 0 0 -1 1
	If we print it out, it will be like:
	* . #
	* * *
	. # .
	* * *
	* . #
	And we input into round 2:
 1 13 -15
	thus, y = 1 1 -1
	Sequentially, on opposite direction, xin = 3 -5 3 1 -1 3 -5 5 -3 1 -1 3 3 -5 3
	thus, x = 1 -1 1 1 -1 1 -1 1 -1 1 -1 1 1 -1 1
	If we print it out, it will be like:
	# . #
	# . #
	. # .
	# . #
	# . #
	
 ===========================
 When x = D' but works WITH bias, yin = 1 5 -3
	thus, y = 1 1 -1
	Sequentially, on opposite direction, xin = 4 -4 4 4 -4 4 -4 4 -4 4 -4 4 4 -4 4
	thus, x = 1 -1 1 1 -1 1 -1 1 -1 1 -1 1 1 -1 1
	If we print it out, it will be like:
	# . #
	# . # 
	. # . 
	# . # 
	# . # 
 */