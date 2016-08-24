#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10000


int * gen_array() {

    srand(time(NULL));

    int * arr = (int *) malloc(SIZE * sizeof(int));
    int i;
    for (i = 0; i < SIZE; i++) { arr[i] = rand() % (2 * SIZE) - SIZE; }
    return arr;
}

void * print_array(int arr[], int size) {

    int i = 0;
    for (i = 0; i < size; i++) { printf("%d ", arr[i]); }
    printf("\n");
}

int * find_max_crossing(int arr[], int low, int mid, int high) {

    int left_sum = -4 * SIZE;
    int max_left;
    int sum = 0;
    int i;

    for (i = mid; i >= low; i--) {
        sum += arr[i];
        if (sum > left_sum) {
            left_sum = sum;
            max_left = i;
        }
    }

    int right_sum = -4 * SIZE;
    int max_right;
    sum = 0;

    for (i = mid + 1; i <= high; i++) {
        sum += arr[i];
        if (sum > right_sum) {
            right_sum = sum;
            max_right = i;
        }
    }

    int * tuple = (int *) malloc(3 * sizeof(int));
    tuple[0] = max_left;
    tuple[1] = max_right;
    tuple[2] = left_sum + right_sum;
    return tuple;
}

int * find_max_subarray(int arr[], int low, int high) {

    if (high == low) { 
        int * tuple = (int *) malloc(3 * sizeof(int));
        tuple[0] = low;
        tuple[1] = high;
        tuple[2] = arr[low];
        return tuple;
    } else {
        int mid = (low + high) / 2;
        int * left_subarray = find_max_subarray(arr, low, mid);
        int * right_subarray = find_max_subarray(arr, mid + 1, high);
        int * cross_subarray = find_max_crossing(arr, low, mid, high);

        if ((left_subarray[2] >= right_subarray[2]) && (left_subarray[2] >= cross_subarray[2])) {
            return left_subarray;
        } else if ((right_subarray[2] >= left_subarray[2]) && (right_subarray[2] >= cross_subarray[2])) {
            return right_subarray;
        } else {
            return cross_subarray;
        }
    }
}

int * kadane_subarray(int arr[]) {

    int cur_sum = 0;
    int max_sum = 0;
    int best_left = 0;
    int best_left_now = 0;
    int best_right = 0;
    int value = 0;
    int i;

    for (i = 0; i < SIZE; i++) {
        value = cur_sum + arr[i];
        if (value > 0) {
            if (cur_sum == 0) {
                best_left_now = i;
            }
            cur_sum = value;
        } else {
            cur_sum = 0;
        }

        if (cur_sum > max_sum) {
            max_sum = cur_sum;
            best_right = i;
            best_left = best_left_now;
        }
    }

    int * tuple = (int *) malloc(3 * sizeof(int));
    tuple[0] = best_left;
    tuple[1] = best_right;
    tuple[2] = max_sum;
    return tuple;
}


int main() {

    int * int_arr = gen_array();
    //print_array(int_arr, SIZE);

    int * nlgn_time_arr = find_max_subarray(int_arr, 0, SIZE - 1);
    print_array(nlgn_time_arr, 3);

    int * lin_time_arr = kadane_subarray(int_arr);
    print_array(lin_time_arr, 3);

}
