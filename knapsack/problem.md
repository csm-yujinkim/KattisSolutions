# Knapsack

## Definition

Implement a solution to the classic knapsack problem.
You are given a knapsack that can hold up to a certain weight
(its capacity), and several items you may choose to put in the knapsack.
Each item has a weight and a value.
Choose a subset of the items
(which could be all of them, or none of them)
having the greatest value that fit into the knapsack
(i.e. the sum of the weights of the items you choose must be less than or equal to the knapsack capacity).

## Input

The input consists of between 1 and 30 test cases.
Each test begins with an integer 1 <= C <= 2000, giving the capacity of the knapsack,
and an integer 1 <= n <= 2000, giving the number of objects.
Then follow n lines, each giving the value and weight of the n objects.
Both values and weights are integers between 1 and 10000.

## Output

For each test case, output a line containing the number of items chosen,
followed by a line containing the indices of the chosen items
(the first item has index 0, the second index 1, and so on).
The indices can be given in any order.

## Sample Input 1

```
5 3
1 5
10 5
100 5
6 4
5 4
4 3
3 2
2 1
```

### Sample Output

```
1
2
3
1 2 3
```

## Analysis

To solve the 0-1 Knapsack Problem given weights w_0, ..., w_n and values v_0, ..., v_n and a maximum weight W.

The following recursive solution is applicable:

1. If n = 0, then do not take anything.
2. If w_n > W, then solve the 0-1 Knapsack Problem given weights w_0, ..., w_{n-1} and values v_0, ..., v_{n-1}
and a maximum weight W. (That is, exclude the last item)
3. Do the two things:
a. Solve the 0-1 Knapsack Problem with weights w_0, ..., w_{n-1} and values v_0, ..., v_{n-1} and a maximum weight W.
b. Solve the 0-1 Knapsack Problem with weights w_0, ..., w_{n-1} and values v_0, ..., v_{n-1} and a maximum weight
W - w_n. The value added is v_n.
c. Compare the values. If the value on the left is higher, than use the combination on the right.
