
//  Neural Networking Assignment 3
//  Created by Yukun Liang(N14194314) on 9/28/14.
//  Contact through yl2662@nyu.edu

#include <iostream>
using namespace std;

//initialize given inputs and outputs
int input[4][3] = {{1,1,1},{1,1,-1},{1,-1,1},{-1,1,1}};
int output[4] = {1,-1,-1,-1};

//initialize weights and bias
float weight [3] = {0,0,0};
float bias = 0;

//customize threshold and alpha
float theta = 0.1;
float a = 1;

int main()
{
    int step=0;  //step counter
    int break_counter=0;    //consequtive correct classification counter
    int iterator = 0;
    
    cout << "step input yin output weight  bias" << endl;
    
    //calculating weights and bias
    while(break_counter!=4)
    {
        step++;
        
        //Theta Modification Method
        //theta=theta/step;
        //
        
        float yin = weight[0] * input[iterator][0]
                    + weight[1] * input[iterator][1]
                    + weight[2] * input[iterator][2]
                    + bias;
        
        if (((yin > theta) && output[iterator]==1)||((yin < (-theta)) && output[iterator]==-1)) {
            break_counter++;
            }
        else {  //update w & b
            break_counter = 0;
            weight[0] += a * output[iterator] * input[iterator][0];
            weight[1] += a * output[iterator] * input[iterator][1];
            weight[2] += a * output[iterator] * input[iterator][2];
            bias += a * output[iterator];
                }
       
        //print message
         cout<< step << "\t "
            << input[iterator][0] << input[iterator][1] << input[iterator][2] <<"\t"
            << yin << "\t "
            << output[iterator]<< "\t  "
            << weight[0]<<" "<< weight[1]<<" "<< weight[2] <<"    "
            << bias <<endl;
        
        if (iterator == 3)
            iterator = 0;
        else
            iterator++;
        
    }
    cout<<"The final weights are w["
    << weight[0]<<" "<< weight[1]<<" "<< weight[2]
    <<"], the bias is "<< bias
    <<"and it takes "<<step<<"steps to convergence."
    <<endl;

    return 0;
}


//Below is the expected output
//step input yin output weight  bias
//1	 111	0	 1	  1 1 1    1
//2	 11-1	2	 -1	  0 0 2    0
//3	 1-11	2	 -1	  -1 1 1    -1
//4	 -111	2	 -1	  0 0 0    -2
//5	 111	-2	 1	  1 1 1    -1
//6	 11-1	0	 -1	  0 0 2    -2
//7	 1-11	0	 -1	  -1 1 1    -3
//8	 -111	0	 -1	  0 0 0    -4
//9	 111	-4	 1	  1 1 1    -3
//10	 11-1	-2	 -1	  1 1 1    -3
//11	 1-11	-2	 -1	  1 1 1    -3
//12	 -111	-2	 -1	  1 1 1    -3
//13	 111	0	 1	  2 2 2    -2
//14	 11-1	0	 -1	  1 1 3    -3
//15	 1-11	0	 -1	  0 2 2    -4
//16	 -111	0	 -1	  1 1 1    -5
//17	 111	-2	 1	  2 2 2    -4
//18	 11-1	-2	 -1	  2 2 2    -4
//19	 1-11	-2	 -1	  2 2 2    -4
//20	 -111	-2	 -1	  2 2 2    -4
//21	 111	2	 1	  2 2 2    -4
//The final weights are w[2 2 2], the bias is -4. It took 21 steps to convergence.
