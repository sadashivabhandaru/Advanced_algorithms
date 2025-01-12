#include <iostream>
#include <vector>

//Function to get the indeces of vector vaules equal to tareget.
std::vector<int> getAddUpto(std::vector<int> input, int target) {
    for(int i = 0; i < input.size(); i++) {
        for(int j = i+1; j < input.size(); j++) {
            if (input[i] + input[j] == target) {
                return {i, j};
            }
        }
    }
    return {};
}

int main()
{
    //Example 1
    std::vector<int> input1 = {2,7,11,15};
    int target1  = 9;
    std::vector<int> output1 = getAddUpto(input1, target1);
    std::cout<<"Example 1 Output index " <<output1[0] << " " <<output1[1]<<std::endl;
    
    //Example 2
    std::vector<int> input2 = {3,2,4};
    int target2  = 6;
    std::vector<int> output2 = getAddUpto(input2, target2);
    std::cout<<"Example 2 Output index " <<output2[0] << " " <<output2[1]<<std::endl;

    //Example 3
    std::vector<int> input3 = {3,3};
    int target3  = 6;
    std::vector<int> output3 = getAddUpto(input3, target3);
    std::cout<<"Example 3 Output index " <<output3[0] << " " <<output3[1]<<std::endl;
    
    //Example 4
    std::vector<int> input4 = {10, 15, 3, 7};
    int target4 = 17;
    std::vector<int> output4 = getAddUpto(input4, target4);
    std::cout<<"Example 4 Output index " <<output4[0] << " " <<output4[1]<<std::endl;
        
    return 0;
}