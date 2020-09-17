#!/usr/intel/bin/python

def binarySearch(arr,low,high,x) :
    #base case
    if high >= low:
        mid = (high+low)/2
        #print "low = " + str(low) + " high = " + str(high) + " mid = " + str(mid) + " arr[mid] = " + str(arr[mid])
        if(arr[mid]==x):
            return mid
        elif(arr[mid]>x):
            return binarySearch(arr,low,mid-1,x)
        else:
            return binarySearch(arr,low+1,high,x)
    else:
        return -1


def main():
    arr = [2,3,4,10,40]
    x   = 10
    result = binarySearch(arr,0,len(arr)-1,2)
    print "arr = ",
    for x in range(len(arr)):
        print str(arr[x]) + " ",
    print ""
    print "Index of 2 in arr  = " + str(result)
    result = binarySearch(arr,0,len(arr)-1,3)
    print "Index of 3 in arr  = " + str(result)
    result = binarySearch(arr,0,len(arr)-1,4)
    print "Index of 4 in arr  = " + str(result)
    result = binarySearch(arr,0,len(arr)-1,5)
    print "Index of 5 in arr  = " + str(result)
    result = binarySearch(arr,0,len(arr)-1,10)
    print "Index of 10 in arr = " + str(result)
    result = binarySearch(arr,0,len(arr)-1,40)
    print "Index of 40 in arr = " + str(result)
    

if __name__ == "__main__":
    main()
            
