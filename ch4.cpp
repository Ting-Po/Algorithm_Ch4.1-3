
#include<stdio.h>
#include<stdlib.h>
#include<windows.h>
#include<time.h>
#include<limits.h>
#include<iostream>

typedef struct{
    int low;
    int high;
    int sum;
}max_sub;




 max_sub Brute_force(int* A, int low, int high){

 max_sub ans = {0,0,A[0]};

 int i,j;
 for(i = low;i<high;i++){
    int current_sum = 0;
    for(j=i;j<high;j++){
        current_sum += A[j];
        if(current_sum >ans.sum){
            ans.low = i;
            ans.high = j;
            ans.sum = current_sum;
        }
    }
 }


   return  ans;

}

max_sub find_max_crossing_subarray(int* A,int  low,int  mid,int high)
{
      max_sub result = {-1, -1, 0};
    int sum = 0,
        left_sum = INT_MIN,
        right_sum = INT_MIN;

    for (int i = mid; i >=  low; i--) {
        sum += A[i];
        if (sum > left_sum) {
            left_sum = sum;
            result.low = i;
        }
    }

    sum = 0;

    for (int j = mid + 1; j <= high; j++) {
        sum += A[j];
        if (sum > right_sum) {
            right_sum = sum;
            result.high = j ;
        }
    }

    result.sum = left_sum + right_sum;
    return result;





}

max_sub find_maximum_subarray_mixed(int* A, int low,int high) {
    if (high - low < 29) {
        return Brute_force(A, low, high);
    } else {
        int mid = (low + high) / 2;
        max_sub left = find_maximum_subarray_mixed(A, low, mid);
        max_sub right = find_maximum_subarray_mixed(A, mid+1, high);
        max_sub cross = find_max_crossing_subarray(A, low, mid, high);

        if (left.sum >= right.sum && left.sum >= cross.sum) {
            return left;
        } else if (right.sum >= left.sum && right.sum >= cross.sum) {
            return right;
        } else {
            return cross;
        }
    }
}


max_sub find_maximum_subarray(int* A,int low,int high){

    int mid;
    if(high == low){
      max_sub result = {low, high, A[low]};
      return result;
    }else{
        mid = (low + high)/2;

        max_sub left = find_maximum_subarray(A, low, mid);
        max_sub right = find_maximum_subarray(A, mid+1, high);
        max_sub cross = find_max_crossing_subarray(A, low, mid, high);

        if (left.sum >= right.sum && left.sum >= cross.sum) {
            return left;
        } else if (right.sum >= left.sum && right.sum >= cross.sum) {
            return right;
        } else {
            return cross;
        }

    }



}

void Random_Input(int* a)
{
    int i;
    int x;
    int plusminus;
    srand(time(NULL));
    for(i=0;i<10000;i++){
        plusminus = (rand()%2);
        x = (rand()%100)+1;

        if(plusminus == 0){
            a[i] = x;
        }else{
            a[i] = x *(-1);
        }

    }




}





int main(void){


    int i;
    int input[10000];

    Random_Input(input);

     max_sub a = {1,1,1};
     max_sub b = {1,1,1};

    clock_t  clockBegin, clockEnd;
    clock_t  clockBr_begin, clockBr_end;


	for(i=0;;i++){
    LARGE_INTEGER clockBegin;
    LARGE_INTEGER clockEnd;
    LARGE_INTEGER clockBr_begin;
    LARGE_INTEGER clockBr_end;



        QueryPerformanceCounter(&clockBr_begin);
        a = Brute_force(input,0,i);
       QueryPerformanceCounter(&clockBr_end);
       QueryPerformanceCounter(&clockBegin);
       b = find_maximum_subarray(input ,0,i);
        QueryPerformanceCounter(&clockEnd);


        std::cout << clockBr_end.QuadPart-clockBr_begin.QuadPart << " " << clockEnd.QuadPart - clockBegin.QuadPart << std::endl;
        if(clockBr_end.QuadPart-clockBr_begin.QuadPart > clockEnd.QuadPart - clockBegin.QuadPart){
            break;
        }

	}

	printf("i = %d\n",i);

    /*
    LARGE_INTEGER m_nFreq;
    LARGE_INTEGER m_nBeginTime;
    LARGE_INTEGER nEndTime;
    QueryPerformanceFrequency(&m_nFreq); // 獲取時鐘週期
    QueryPerformanceCounter(&m_nBeginTime); // 獲取時鐘計數
    Sleep(100);
    QueryPerformanceCounter(&nEndTime);
    std::cout << (nEndTime.QuadPart-m_nBeginTime.QuadPart)*1000/m_nFreq.QuadPart << std::endl;
    */
/*
for(i=0;;i++){
        clockBr_begin = clock();
        a = Brute_force(input,0,i);
        clockBr_end = clock();
        clockBegin = clock();
        b = find_maximum_subarray_mixed(input ,0,i);
        clockEnd = clock();


        if(clockBr_end-clockBr_begin > clockEnd - clockBegin){
            break;
        }

	}

	printf("i = %d\n",i);

*/








    return 0;
}
