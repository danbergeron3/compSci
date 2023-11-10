#include <bits/stdc++.h>
#include <iostream>
#include <unordered_map>
#include <iomanip>
using namespace std;

/*
 * Complete the 'plusMinus' function below.
 *
 * The function accepts INTEGER_ARRAY arr as parameter.
 * outputs ratios of positive, negative and zero numbers
 */
void plusMinus(vector<int> arr) {
    double denominator = static_cast<double>(arr.size());
    vector<int>::iterator current_value;
    int keySet[] = {-1, 0, 1};
    
    // holds number and amount of times number appeared
    unordered_map<int, int> umap;
    umap[0] = 0;
    umap[1] = 0;
    umap[-1] = 0; 
    
    for(current_value = arr.begin(); current_value != arr.end(); current_value++) {
        // if element isn't present in the map insert it 
        if((*current_value) == 0) {
            umap[0] = umap[0] + 1;
        } else if ((*current_value) < 0) {
            umap[-1] = umap[-1] + 1;
        } else {
            umap[1] = umap[1] + 1;
        }
    }
        double numerator;
        
        numerator = static_cast<double>(umap[keySet[2]]);
        cout << fixed << setprecision(6) << (numerator / denominator) << endl;
        
        numerator = static_cast<double>(umap[keySet[0]]);
        cout << fixed << setprecision(6) << (numerator / denominator) << endl;
        
        numerator = static_cast<double>(umap[keySet[1]]);
        cout << fixed << setprecision(6) << (numerator / denominator) << endl;   
}
