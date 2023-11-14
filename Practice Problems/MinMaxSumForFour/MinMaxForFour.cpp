void miniMaxSum(vector<int> arr) {
    sort(arr.begin(), arr.end());
    // need longs if numbers are to big it will overflow when added
    long lastNumber = static_cast<long>(arr[arr.size()-1]);
    long sum = 0;
     
    arr.pop_back();
    vector<int>::iterator m = arr.begin();
    for (; m != arr.end(); m++) {
        sum = sum + static_cast<long>(*m);
    }
    
    cout << sum << " ";
    sum += lastNumber;
    sum -= arr[0];
    cout << sum << endl;
}