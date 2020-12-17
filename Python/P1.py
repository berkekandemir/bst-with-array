#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Nov 14 14:07:05 2020

@author: berke
"""

import time

# File Reading into a List
file = open("numbers_500.txt", 'r')
array_str = []
array = []
for line in file:
    array_str = line.split(" ")    
for i in array_str:
    array.append(int(i))
file.close()

# Tree
tree = [None] * 100000 # 10000 for 50; 100000 for 100, 500;
                       # because there is so many empty spaces in tree.  


# Function Definitions
index = 0
def insert(tree, number):
    global index
    if tree[index] != None: # there won't be any duplicate number.
        if number > tree[index]:
            index = index * 2 + 2
            insert(tree, number)
        elif number < tree[index]:
            index = index * 2 + 1
            insert(tree, number)
    else:
        tree[index] = number
        index = 0
        return
    
def traverse(tree, index):
    if index > (len(tree) - 1):
        return
    traverse(tree, (index * 2) + 1)
    if tree[index] != None:
        file.write(str(tree[index]))
        file.write(" ")
    traverse(tree, (index * 2) + 2)
            
# Tree Building            
#######################################    
start = time.time()
for i in array:
    insert(tree, i)
end = time.time()
#######################################


# File Writing by Inorder Traversing the Tree
elapsed_time = end - start
print("\nTotal time:", elapsed_time, "seconds")
file = open("numbers_500_sorted.txt", 'a')
file.write("Total time: " + str(elapsed_time) + " seconds\n")
traverse(tree, index)
file.close()
