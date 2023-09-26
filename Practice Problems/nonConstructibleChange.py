def nonConstructibleChange(coins):
    # list must be sorted
    coins.sort()
    # Write your code here.
    currChange = 0
    for change in coins:
        if currChange + 1 < change:
            return currChange + 1
        else:
            currChange += change
            
    return currChange + 1