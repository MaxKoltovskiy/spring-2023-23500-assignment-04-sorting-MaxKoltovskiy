#include <iostream>
#include <vector>
#include <time.h>
#include <unistd.h>
#include <sys/time.h>
#include <math.h>
#include <algorithm>


void print_vector(std::vector<int> a) {
    for(auto item:a) {
        std::cout<< item << ",";
    }
    std::cout<< "\n";
}

int find_min_index(std::vector<int> a, int start_index, int stop_index) {
    int min_index = start_index;
    int i;
    for(i = start_index; i < stop_index; i++) {
        if(a[i] < a[min_index]) {
            min_index = i;
        }

    }
    return min_index;
}

std::vector<int> ssort(std::vector<int> a) {
    int i, min_index, tmp;
    int len = a.size();
    for(i = 0; i<len; i++) {
        min_index = find_min_index(a,i, len);

        tmp = a[i];
        a[i] = a[min_index];
        a[min_index] = tmp;
    }
    return a; 
}

std::vector<int> merge(std::vector<int> left, std::vector<int> right) {

    std::vector<int> merged;
    int l = 0,r = 0; // indices to left and right

    while(l< left.size() && r < right.size()) {
        if(left[l] < right[r]) {
            merged.push_back(left[l]);
            l++;
        }
        else {
            merged.push_back(right[r]);
            r++;
        }
    }

    while(l < left.size()) {
        merged.push_back(left[l]);
        l++;
    }
    while(r < right.size()) {
        merged.push_back(right[r]);
        r++;
    }

    return merged;
}

std::vector<int> msort(std::vector<int> data) {
    std::vector<int> result;

    if(data.size() <= 1) {
        return data;
    }

    std::vector<int> a,b;
    int i;
    int mid = data.size()/2;
    for(i=0; i<mid; i++) {
        a.push_back(data[i]);
    }
    for(;i<data.size(); i++) {
        b.push_back(data[i]);
    }

    a = msort(a);
    b = msort(b);
    result = merge(a,b);

    return result;
}

std::vector<int> qsort(std::vector<int> list) {
    int i,j;

    //base case
    if(list.size() <= 1) {
        return list;
    }

    //select pivot value
    //for now we will just pick list[0]
    int pivot = list[0];

    //make 2 new vectors
    std::vector<int> lower,higher;

    //copy all values <= pivot to lower
    //copy all values > pivot to higher
    for(i = 1; i< list.size(); i++) {
        if(list[i] < pivot) {
            lower.push_back(list[i]);
        } else {
            higher.push_back(list[i]);
        }
    }

    //make our recursive calls
    lower = qsort(lower);
    higher = qsort(higher);

    //copy everything back
    for(i = 0; i< lower.size(); i++) {
        list[i] = lower[i];
    }
    list[i] = pivot;
    i++;
    for(j = 0; j< higher.size(); j++) {
        list[i] = higher[j];
        i++;
    }

    //return list
    return list;
    
    
}

std::vector<int> qsort2(std::vector<int>& v, int low, int high) {
   
    if(low<high) {
        int i,j;

        int pivot = v[high];

        i= (low);
        for(j=low; j<=high-1; j++) {
            if(v[j] < pivot) {
                  
                int temp = v[j];
                v[j] = v[i];
                v[i] = temp;
                i++;

            }
        }
        
        int temp = v[high];
        v[high] = v[i];
        v[i] = temp;

        qsort2(v,low,i-1);
        qsort2(v,i+1,high);
        
        
    }
    return v;
}

int main() {
    int size = 50000;
    int max_val = 100;

    srand(time(nullptr));
    std::vector<int> a(size);
    for(int i = 0; i < size; i++) {
        a[i] = rand()%max_val;
    }

    //std::cout<< "Unsorted vector: ";
    //print_vector(a);
    
    struct timeval tp;
    gettimeofday(&tp, NULL);
    long start_time = tp.tv_sec *1000 + tp.tv_usec / 1000;

    std::vector<int> q = qsort2(a,0,size-1);

    gettimeofday(&tp, NULL);
    long current_time = tp.tv_sec *1000 + tp.tv_usec / 1000;
    long elapsed_time = current_time - start_time;

    //std::cout<< "Sorted with quicksort: ";
    //print_vector(q);

    std::cout<< "qsort time elapsed: "<< elapsed_time << "\n";



    //std::cout<< "Unsorted vector: ";
    //print_vector(a);
    
    gettimeofday(&tp, NULL);
    start_time = tp.tv_sec *1000 + tp.tv_usec / 1000;

    std::vector<int> s = ssort(a);

    gettimeofday(&tp, NULL);
    current_time = tp.tv_sec *1000 + tp.tv_usec / 1000;
    elapsed_time = current_time - start_time;

    //std::cout<< "Sorted with selectionsort: ";
    //print_vector(s);

    std::cout<< "ssort time elapsed: "<< elapsed_time << "\n";



    //std::cout<< "Unsorted vector: ";
    //print_vector(a);
    
    gettimeofday(&tp, NULL);
    start_time = tp.tv_sec *1000 + tp.tv_usec / 1000;

    std::vector<int> m = msort(a);

    gettimeofday(&tp, NULL);
    current_time = tp.tv_sec *1000 + tp.tv_usec / 1000;
    elapsed_time = current_time - start_time;

    //std::cout<< "Sorted with mergesort: ";
    //print_vector(b);

    std::cout<< "msort time elapsed: "<< elapsed_time << "\n";


    //std::cout<< "Unsorted vector: ";
    //print_vector(a);

    gettimeofday(&tp, NULL);
    start_time = tp.tv_sec *1000 + tp.tv_usec / 1000;

    std::vector<int> c = a;
    std::sort(c.begin(), c.end());

    gettimeofday(&tp, NULL);
    current_time = tp.tv_sec *1000 + tp.tv_usec / 1000;
    elapsed_time = current_time - start_time;

    //std::cout<< "Sorted with c++ sort: ";
    //print_vector(c);

    std::cout<< "c++ sort time elapsed: "<< elapsed_time << "\n";
}
