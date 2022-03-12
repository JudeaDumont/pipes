// chef.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include "pipes.h"

//todo: it is going to be a problem that finding a sink always adds 1 to the cells filled with water
// especially when a cross leads directly to a sink

void initializeVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited)
{
    for (int i = 0; i < state.size(); i++)
    {
        std::vector<int> row = {};
        for (int ii = 0; ii < state[0].size(); ii++)
        {
            row.push_back(0);
        }
        visited.push_back(row);
    }
}


bool pipeStart(std::vector<std::string>& state, const int& i, const int& ii)
{
    return state[i][ii] > 96 && state[i][ii] < 123;
}

std::vector<int> checkWest(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC)
{
    //left/west
    if (fcStep != 0) {
        //check for left and horizontal pipes.
        if (state[frStep][fcStep - 1] == '2' ||
            state[frStep][fcStep - 1] == '3' ||
            state[frStep][fcStep - 1] == '6' ||
            state[frStep][fcStep - 1] == '7') {
            nextSteps.push_back(frStep);
            nextSteps.push_back(fcStep - 1);
            return { frStep, fcStep - 1 };
        }
    }
    return {};
}

std::vector<int> checkSouth(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC)
{
    //below/south
    if (frStep + 1 != state.size()) {
        //check for vertical and down pipes.
        if (state[frStep + 1][fcStep] == '1' ||
            state[frStep + 1][fcStep] == '5' ||
            state[frStep + 1][fcStep] == '6' ||
            state[frStep + 1][fcStep] == '7') {
            nextSteps.push_back(frStep + 1);
            nextSteps.push_back(fcStep);
            return { frStep + 1, fcStep };
        }
    }
    return {};
}

std::vector<int> checkEast(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC)
{
    //right/east
    if (fcStep + 1 != state[0].size()) {

        //check for left and horizontal pipes.
        if (state[frStep][fcStep + 1] == '2' ||
            state[frStep][fcStep + 1] == '4' ||
            state[frStep][fcStep + 1] == '5' ||
            state[frStep][fcStep + 1] == '7') {

            nextSteps.push_back(frStep);
            nextSteps.push_back(fcStep + 1);
            return { frStep, fcStep + 1 };
        }
    }
    return {};
}

std::vector<int> checkNorth(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC)
{
    //above/north
    if (frStep != 0) {
        //check for vertical and down pipes.
        if (state[frStep - 1][fcStep] == '1' ||
            state[frStep - 1][fcStep] == '3' ||
            state[frStep - 1][fcStep] == '4' ||
            state[frStep - 1][fcStep] == '7') {
            nextSteps.push_back(frStep - 1);
            nextSteps.push_back(fcStep);
            return { frStep - 1, fcStep };
        }
    }
    return {};
}

//anyhting that isn't 0 counts as visited or not visitable, with no distinction between 'visited' and 'not visitable' necessary
int checkNorthVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep)
{
    if (frStep == 0) {
        //off of state matrix
        return -2;
    }
    else if (state[frStep-1][fcStep] == 0) {
        //dead end
        return -1;
    }
    else if (visited[frStep - 1][fcStep] == 0) {
        return 0;
    }
    else {
        if (state[frStep - 1][fcStep] == '7') {
            if (visited[frStep - 1][fcStep] == 1) {
                return 1;
            }
            else if (visited[frStep - 1][fcStep] == 2) {
                return 0;
            }
            else if (visited[frStep - 1][fcStep] == 3) {
                return 1;
            }
            else {
                //this should be impossible
            }
        }
        else {
            return 1;
        }
    }
}

int checkSouthVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep)
{
    if (frStep == state.size()) {
        //off of state matrix
        return -2;
    }
    if (state[frStep + 1][fcStep] == 0) {
        //dead end
        return -1;
    }
    if (visited[frStep + 1][fcStep] == 0) {
        return 0;
    }
    else {
        if (state[frStep + 1][fcStep] == '7') {
            if (visited[frStep + 1][fcStep] == 1) {
                return 1;
            }
            else if (visited[frStep + 1][fcStep] == 2) {
                return 0;
            }
            else if (visited[frStep + 1][fcStep] == 3) {
                return 1;
            }
            else {
                //this should be impossible
            }
        }
        else {
            return 1;
        }
    }
}

int checkWestVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep)
{
    if (fcStep == 0) {
        //off of state matrix
        return -2;
    }
    if (state[frStep][fcStep - 1] == 0) {
        //dead end
        return -1;
    }
    if (visited[frStep][fcStep-1] == 0) {
        return 0;
    }
    else {
        if (state[frStep][fcStep-1] == '7') {
            if (visited[frStep][fcStep - 1] == 1) {
                return 0;
            }
            else if (visited[frStep][fcStep - 1] == 2) {
                return 1;
            }
            else if (visited[frStep][fcStep - 1] == 3) {
                return 1;
            }
            else {
                //this should be impossible
            }
        }
        else {
            return 1;
        }
    }
}

int checkEastVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep)
{
    if (fcStep == 0) {
        //off of state matrix
        return -2;
    }
    if (state[frStep][fcStep + 1] == 0) {
        //dead end
        return -1;
    }
    if (visited[frStep][fcStep + 1] == 0) {
        return 0;
    }
    else {
        if (state[frStep][fcStep + 1] == '7') {
            if (visited[frStep][fcStep + 1] == 1) {
                return 0;
            }
            else if (visited[frStep][fcStep + 1] == 2) {
                return 1;
            }
            else if (visited[frStep][fcStep + 1] == 3) {
                return 1;
            }
            else {
                //this should be impossible
            }
        }
        else {
            return 1;
        }
    }
}

int pipeSink(std::vector<std::string>& state, const int& i, const int& ii, const char& source)
{
    const char& s = state[i][ii];
    bool sink = s > 64 && s < 91;
    if (sink) {
        if (s + 32 == source) {
            return 2;
        }
        else {
            return - 1;
        }
    }
    else{
        return 0;
    }
}

void print(std::vector<std::vector<int>>&foo) {
    std::cout.put('\n\n');
    for (int row{}; row < foo.size(); ++row) {
        std::cout << ' ';
        for (int col{}; col < foo[row].size(); ++col) {
            std::cout << foo[row][col] << ' ';
        }
        std::cout.put('\n');
    }
    std::cout.put('\n');
}

void print(const std::vector<std::string>& foo) {
    std::cout.put('\n\n');
    for (int row{}; row < foo.size(); ++row) {
        std::cout << ' ';
        for (int col{}; col < foo[row].size(); ++col) {
            std::cout << foo[row][col] << ' ';
        }
        std::cout.put('\n');
    }
    std::cout.put('\n');
}

//Rules for visited:
//-7 = horizontal cycle
//-6 = vertical cycle
//-5 = cycle
//-4 = dead end
//-3 = dead end horizontal and vertical
//-2 = dead end horizontal
//-1 = dead end vertical
//0 = not visited
//1 = cross visited vertically
//2 = cross visited horizontally
//3 = cross visited both vertically and horizontally
//4 = visited 
//5 = source visited
//6 = sink visited
int solution(std::vector<std::string>state) {

    std::vector<std::vector<int>> visited = {};
    initializeVisited(state, visited);

    std::vector<std::vector<int>> sourcesRC = {};
    std::vector<char> sourceCodes = {};
    std::vector<int> cellCount = {};

    std::vector<int> finishedSteps = {};
    std::vector<int> leakedSteps = {};
    std::vector<int> cycledSteps = {};
    getPipeSources(state, sourcesRC, sourceCodes, cellCount, finishedSteps, leakedSteps, cycledSteps);

    int sourcesCount = sourcesRC.size();
    std::vector<std::vector<int>> nextSteps = {}; //any place where nextSteps is updated, sourcesRC is updated
    getInitialSteps(sourcesRC, nextSteps, state, visited);

    bool bContinue = true;
    int sourcesPropogating = sourcesRC.size();
    while (sourcesPropogating > 0 && bContinue) {
        for (int ii = 0; ii < nextSteps.size(); ii++)//nextSteps for each source
        {
            for (int i = 0; i < int(nextSteps[ii].size()) - 1; i += 2)//next steps are stored like [(r,c),(r,c)]
            {
                print(visited);
                char cell = state[nextSteps[ii][i]][nextSteps[ii][i + 1]];
                if (cell == '1') { //Vertical
                    int northVisited = checkNorthVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    int southVisited = checkSouthVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    if (northVisited == 1 && southVisited == 1) {
                        //cycle
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -5;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        cycledSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (northVisited == 1 && southVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (southVisited == 1 && northVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (southVisited == 1 && northVisited == 0) {
                        //add north to nextSteps, flow is north
                        int sink = pipeSink(state, nextSteps[ii][i]-1, nextSteps[ii][i + 1], sourceCodes[ii]);
                        if (sink == 0) {
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = nextSteps[ii][i] - 1; //row-1 for north
                            nextSteps[ii][i + 1] = nextSteps[ii][i + 1]; //column
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i]-1][nextSteps[ii][i + 1]] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if(sink == -1){
                            //wrong sink
                            leakedSteps[ii] = cellCount[ii];
                            bContinue = false;
                        }
                    }
                    else if (southVisited == 0 && northVisited == 1) {
                        //add south to nextSteps, flow is south
                        int sink = pipeSink(state, nextSteps[ii][i]+1, nextSteps[ii][i + 1], sourceCodes[ii]);
                        if (sink == 0) {
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i] + 1); //row+1 for south
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i] + 1][nextSteps[ii][i + 1]] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else {
                        //visited is messed up
                        //no idea, this should be impossible
                        return -666;
                    }

                }
                else if (cell == '2') {//Horizontal
                    int westVisited = checkWestVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    int eastVisited = checkEastVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    if (westVisited == 1 && eastVisited == 1) {
                        //cycle
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -5;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        cycledSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (westVisited == 1 && eastVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (eastVisited == 1 && westVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (eastVisited == 1 && westVisited == 0) {
                        int sink = pipeSink(state, nextSteps[ii][i], nextSteps[ii][i + 1]-1, sourceCodes[ii]);
                        if (sink == 0) {
                            //add west to nextSteps, flow is west
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i]); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] - 1); //column - 1 for west
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]-1] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else if (eastVisited == 0 && westVisited == 1) {
                        int sink = pipeSink(state, nextSteps[ii][i], nextSteps[ii][i + 1]+1, sourceCodes[ii]);
                        if (sink == 0) {
                            //add east to nextSteps, flow is east
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i]); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] + 1); //column + 1 for east
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]+1] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else {
                        //visited broken
                        //no idea, this should be impossible
                        return -3;
                    }
                }
                else if (cell == '3') {//Right to Down
                    int southVisited = checkSouthVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    int eastVisited = checkEastVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    if (southVisited == 1 && eastVisited == 1) {
                        //cycle
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -5;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        cycledSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (southVisited == 1 && eastVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (eastVisited == 1 && southVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (eastVisited == 1 && southVisited == 0) {
                        int sink = pipeSink(state, nextSteps[ii][i]+1, nextSteps[ii][i + 1], sourceCodes[ii]);
                        if (sink == 0) {
                            //add south to nextSteps, flow is south
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i] + 1); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i] + 1][nextSteps[ii][i + 1]] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else if (eastVisited == 0 && southVisited == 1) {
                        int sink = pipeSink(state, nextSteps[ii][i], nextSteps[ii][i + 1]+1, sourceCodes[ii]);
                        if (sink == 0) {
                            //add east to nextSteps, flow is east
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i]); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] + 1); //column + 1 for east
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]+1] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else {
                        //no idea, this should be impossible
                        return -3;
                    }
                }
                else if (cell == '4') {//Left to down
                    int southVisited = checkSouthVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    int westVisited = checkWestVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    if (southVisited == 1 && westVisited == 1) {
                        //cycle
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -5;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        cycledSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (southVisited == 1 && westVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (westVisited == 1 && southVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (westVisited == 1 && southVisited == 0) {
                        int sink = pipeSink(state, nextSteps[ii][i]+1, nextSteps[ii][i + 1], sourceCodes[ii]);
                        if (sink == 0) {
                            //add south to nextSteps, flow is south
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i] + 1); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i] + 1][nextSteps[ii][i + 1]] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else if (westVisited == 0 && southVisited == 1) {
                        int sink = pipeSink(state, nextSteps[ii][i], nextSteps[ii][i + 1]-1, sourceCodes[ii]);
                        if (sink == 0) {
                            //add west to nextSteps, flow is west
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i]); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] - 1); //column + 1 for east
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]-1] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else {
                        //visited broken
                        //no idea, this should be impossible
                        return -3;
                    }
                }
                else if (cell == '5') {//Up to left
                    int northVisited = checkNorthVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    int westVisited = checkWestVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    if (northVisited == 1 && westVisited == 1) {
                        //cycle
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -5;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        cycledSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (northVisited == 1 && westVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (westVisited == 1 && northVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (westVisited == 1 && northVisited == 0) {
                        int sink = pipeSink(state, nextSteps[ii][i]-1, nextSteps[ii][i + 1], sourceCodes[ii]);
                        if (sink == 0) {
                            //add north to nextSteps, flow is north
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i] - 1); //row-1 for north
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i] - 1][nextSteps[ii][i + 1]] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else if (westVisited == 0 && northVisited == 1) {
                        int sink = pipeSink(state, nextSteps[ii][i], nextSteps[ii][i + 1]-1, sourceCodes[ii]);
                        if (sink == 0) {
                            //add west to nextSteps, flow is west
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i]); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] - 1); //column -1
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]-1] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else {
                        //visited broken
                        //no idea, this should be impossible
                        return -3;
                    }

                }
                else if (cell == '6') {//Up to Right
                    int northVisited = checkNorthVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    int eastVisited = checkEastVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                    if (northVisited == 1 && eastVisited == 1) {
                        //cycle
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -5;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        cycledSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (northVisited == 1 && eastVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (eastVisited == 1 && northVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        leakedSteps[ii] = cellCount[ii];
                        bContinue = false;
                    }
                    else if (eastVisited == 1 && northVisited == 0) {
                        int sink = pipeSink(state, nextSteps[ii][i]-1, nextSteps[ii][i + 1], sourceCodes[ii]);
                        if (sink == 0) {
                            //add north to nextSteps, flow is north
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i] - 1); //row-1 for north
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i] - 1][nextSteps[ii][i + 1]] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else if (eastVisited == 0 && northVisited == 1) {
                        int sink = pipeSink(state, nextSteps[ii][i], nextSteps[ii][i + 1]+1, sourceCodes[ii]);
                        if (sink == 0) {
                            //add east to nextSteps, flow is east
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i]); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] + 1); //column -1
                        }
                        else if (sink == 2) {
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]+1] = 6;
                            finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                        }
                        else if (sink == -1) {

                        }
                    }
                    else {
                        //visited broken
                        //no idea, this should be impossible
                        return -3;
                    }
                }
                else if (cell == '7') {//Cross
                    if (sourcesRC[ii][i] - 1 == nextSteps[ii][i] && sourcesRC[ii][i + 1] == nextSteps[ii][i + 1]) { //north
                        int northVisited = checkNorthVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                        if (northVisited < 0) {
                            //dead end
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -1;
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            i -= 2;
                        }
                        else if (northVisited == 1) {
                            //cycle
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -6;
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            i -= 2;
                        }
                        else if (northVisited == 0) {
                            int sink = pipeSink(state, nextSteps[ii][i]-1, nextSteps[ii][i + 1], sourceCodes[ii]);
                            if (sink == 0) {
                                //add north to nextSteps, flow is north
                                if (visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] == 0)
                                {
                                    ++cellCount[ii];
                                }
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 1;
                                sourcesRC[ii][i] = nextSteps[ii][i];
                                sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                                nextSteps[ii][i] = (nextSteps[ii][i] - 1); //row-1 for north
                                nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                            }
                            else if (sink == 2) {
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 1;
                                visited[nextSteps[ii][i] - 1][nextSteps[ii][i + 1]] = 6;
                                finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                            }
                            else if (sink == -1) {

                            }
                        }
                        else {
                            //visited broken
                            //no idea, this should be impossible
                            return -3;
                        }
                    }
                    else if (sourcesRC[ii][i] + 1 == nextSteps[ii][i] && sourcesRC[ii][i + 1] == nextSteps[ii][i + 1]) { //south
                        int southVisited = checkSouthVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                        if (southVisited < 0) {
                            //dead end
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -1;
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            i -= 2;
                        }
                        else if (southVisited == 1) {
                            //cycle
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -6;
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            i -= 2;
                        }
                        else if (southVisited == 0) {
                            int sink = pipeSink(state, nextSteps[ii][i]+1, nextSteps[ii][i + 1], sourceCodes[ii]);
                            if (sink == 0) {
                                if (visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] == 0)
                                {
                                    ++cellCount[ii];
                                }
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 1;
                                //add south to nextSteps, flow is south
                                sourcesRC[ii][i] = nextSteps[ii][i];
                                sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                                nextSteps[ii][i] = (nextSteps[ii][i] + 1); //row
                                nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                            }
                            else if (sink == 2) {
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 1;
                                visited[nextSteps[ii][i] + 1][nextSteps[ii][i + 1]] = 6;
                                finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                            }
                            else if (sink == -1) {

                            }
                        }
                        else {
                            //no idea, this should be impossible
                            return -3;
                        }
                    }
                    else if (sourcesRC[ii][i] == nextSteps[ii][i] && sourcesRC[ii][i + 1] - 1 == nextSteps[ii][i + 1]) { //west
                        int westVisited = checkWestVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                        if (westVisited < 0) {
                            //dead end
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -2;
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            i -= 2;
                        }
                        else if (westVisited == 1) {
                            //cycle
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -7;
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            i -= 2;
                        }
                        else if (westVisited == 0) {
                            int sink = pipeSink(state, nextSteps[ii][i], nextSteps[ii][i + 1]-1, sourceCodes[ii]);
                            if (sink == 0) {
                                //add west to nextSteps, flow is west
                                if (visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] == 0)
                                {
                                    ++cellCount[ii];
                                }
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 2;
                                sourcesRC[ii][i] = nextSteps[ii][i];
                                sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                                nextSteps[ii][i] = (nextSteps[ii][i]); //row
                                nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] - 1); //column - 1 for west
                            }
                            else if (sink == 2) {
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 2;
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1]-1] = 6;
                                finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                            }
                            else if (sink == -1) {

                            }
                        }
                        else {
                            //no idea, this should be impossible
                            return -3;
                        }
                    }
                    else if (sourcesRC[ii][i] == nextSteps[ii][i] && sourcesRC[ii][i + 1] + 1 == nextSteps[ii][i + 1]) { //east
                        int eastVisited = checkEastVisited(state, visited, nextSteps[ii][i], nextSteps[ii][i + 1]);
                        if (eastVisited < 0) {
                            //dead end
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -2;
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            i -= 2;
                        }
                        else if (eastVisited == 1) {
                            //cycle
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -7;
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            nextSteps[ii].erase(nextSteps[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                            i -= 2;
                        }
                        else if (eastVisited == 0) {
                            int sink = pipeSink(state, nextSteps[ii][i], nextSteps[ii][i + 1]+1, sourceCodes[ii]);
                            if (sink == 0) {
                                //add east to nextSteps, flow is east
                                if (visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] == 0)
                                {
                                    ++cellCount[ii];
                                }
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 2;
                                sourcesRC[ii][i] = nextSteps[ii][i];
                                sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                                nextSteps[ii][i] = (nextSteps[ii][i]); //row
                                nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] + 1); //column -1
                            }
                            else if (sink == 2) {
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 2;
                                visited[nextSteps[ii][i]][nextSteps[ii][i + 1] + 1] = 6;
                                finishPath(finishedSteps, ii, cellCount, sourcesRC, nextSteps);
                            }
                            else if (sink == -1) {

                            }
                        }
                        else {
                            //no idea, this should be impossible
                            return -3;
                        }
                    }
                }
                else if (cell == '0') {
                    //no idea, this should be impossible
                    return -3;
                }
                else {
                    //no idea, this should be impossible
                    return -3;
                }
            }
        }

        sourcesPropogating = 0;
        for (size_t i = 0; i < sourcesRC.size(); i++)
        {
            sourcesPropogating += sourcesRC[i].size();
        }
        int cycles = 0;
        for (size_t i = 0; i < cycledSteps.size(); i++)
        {
            cycles += cycledSteps[i];
        }
        int leaks = 0;
        for (size_t i = 0; i < leakedSteps.size(); i++)
        {
            leaks += leakedSteps[i];
        }
        int nextStepsLeft = 0;
        for (size_t i = 0; i < nextSteps.size(); i++)
        {
            nextStepsLeft += (nextSteps[i].size() / 2);
        }

        if ((sourcesPropogating == 0 || nextStepsLeft == 0) && cycles == 0 && leaks == 0) {
            int totalstepsfinished = 0;
            for (size_t i = 0; i < finishedSteps.size(); i++)
            {
                totalstepsfinished += finishedSteps[i];
            }
            return totalstepsfinished;
        }
        else if (cycles > 0 || leaks > 0) {
            return -leaks - cycles;
        }
    }
    return 0; // this occurrs in the case where the state is just zeros
}

void finishPath(std::vector<int>& finishedSteps, int& ii, std::vector<int>& cellCount, std::vector<std::vector<int>>& sourcesRC, std::vector<std::vector<int>>& nextSteps)
{

    //finished path, add it to the respective finished steps vector
    //remove the path from being traversed
    finishedSteps[ii] = cellCount[ii]+=1;
    sourcesRC[ii].clear();
    nextSteps[ii].clear();
}

void getInitialSteps(std::vector<std::vector<int>>& sourcesRC, std::vector<std::vector<int>>& nextSteps, std::vector<std::string>& state, std::vector<std::vector<int>>& visited)
{
    for (int i = 0; i < sourcesRC.size(); i++)
    {
        nextSteps.push_back({});
        checkNorth(sourcesRC[i][0], sourcesRC[i][1], state, nextSteps[i], sourcesRC[i]);
        checkEast(sourcesRC[i][0], sourcesRC[i][1], state, nextSteps[i], sourcesRC[i]);
        checkSouth(sourcesRC[i][0], sourcesRC[i][1], state, nextSteps[i], sourcesRC[i]);
        checkWest(sourcesRC[i][0], sourcesRC[i][1], state, nextSteps[i], sourcesRC[i]);
        visited[sourcesRC[i][0]][sourcesRC[i][1]] = 5; //5 = source
    }
}

void getPipeSources(std::vector<std::string>& state, std::vector<std::vector<int>>& sourcesRC, std::vector<char>& sourceCodes, std::vector<int>& cellCount, std::vector<int>& finishedSteps, std::vector<int>& leakedSteps, std::vector<int>& cycledSteps)
{
    for (int i = 0; i < state.size(); i++)
    {
        for (int ii = 0; ii < state[0].size(); ii++)
        {
            if (pipeStart(state, i, ii)) {
                sourcesRC.push_back({});
                sourcesRC[sourcesRC.size()-1].push_back(i);
                sourcesRC[sourcesRC.size()-1].push_back(ii);
                sourceCodes.push_back(state[i][ii]);
                cellCount.push_back(0);
                finishedSteps.push_back(0);
                leakedSteps.push_back(0);
                cycledSteps.push_back(0);
            }
        }
    }
}

void test(const std::vector<std::string>& state, int test)
{
    print(state);
    int iSolution = solution(state);
    if (iSolution == test) {
        std::cout << "\ngave: " << iSolution << "\n\Success!\n\n";
    }
    else {
        std::cout << "\ngave: " << iSolution << "\n\nFail!\n\n\n\n";
    }
}

int main()
{
    test({ //1
        "a224C22300000",
        "0001643722B00",
        "0b27275100000",
        "00c7256500000",
        "0006A45000000" 
        }, 19);

    test({//2
        "a000",
        "000A"
        }, 0);


    test({//3
        "a727272777A"
        }, 9);


    test({//4
        "a",
        "7",
        "1",
        "7",
        "7",
        "1",
        "1",
        "A"
        }, 6);

    test({//5
        "A0000b0000",
        "0000000000",
        "0000000000",
        "0000a00000",
        "0000000000",
        "0c00000000",
        "01000000B0",
        "0C00000000"
        }, 1);

    test({//6
        "0000000000",
        "0000000000",
        "0000000000",
        "0000000000",
        "0000000000",
        "0000000000",
        "0000000000",
        "0000000000"
        }, 0);
}
