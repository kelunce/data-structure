#include <iostream>

using namespace std;


struct node{
    int value;
    int cur_min;
};

const int max_ele = 100;
node a[max_ele] = {};

int main()
{
    int input = 0;
    int idx = max_ele;
    while (cin >> input) {
        node *p = &a[--idx];
        p->value = input;

        if (idx == max_ele -  1){
            p->cur_min = input;
        }else{
            if (((node *)(p + 1))->cur_min <= input){
                p->cur_min = ((node*)(p + 1))->cur_min;
            }else{
                p->cur_min = input;
            }
        }
    }
    
    while(idx < max_ele){
        cout << a[idx].value << " " << a[idx].cur_min <<endl;
        idx++;
    }
    return 0;
}

