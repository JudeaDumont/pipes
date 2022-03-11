// chef.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <vector>
#include "pipes.h"


void initializeVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited)
{
    for (size_t i = 0; i < state.size(); i++)
    {
        std::vector<int> row = {};
        for (size_t ii = 0; ii < state[0].size(); ii++)
        {
            row.push_back(0);
        }
        visited.push_back(row);
    }
}


bool pipeStart(std::vector<std::string>& state, const size_t& i, const size_t& ii)
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

        std::cout << "cum: " << state[frStep][fcStep + 1];

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
int checkNorthVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep, const char& source)
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

int checkSouthVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep, const char& source)
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

int checkWestVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep, const char& source)
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

int checkEastVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep, const char& source)
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

int pipeSink(std::vector<std::string>& state, const size_t& i, const size_t& ii, const char& source)
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
    return ;
}

void print(std::vector<std::vector<int>>&foo) {
    std::cout.put('\n\n');
    for (std::size_t row{}; row < foo.size(); ++row) {
        std::cout << ' ';
        for (std::size_t col{}; col < foo[row].size(); ++col) {
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
    std::vector<std::vector<char>> sourceCodes = {};
    std::vector<int> cellCount = {};

    getPipeSources(state, sourcesRC, sourceCodes, cellCount);

    std::vector<std::vector<int>> nextSteps = {}; //any place where nextSteps is updated, sourcesRC is updated
    getInitialSteps(sourcesRC, nextSteps, state, visited);

    bool stepsPropagating = true;
    int loopCount = 0;
    while (stepsPropagating && loopCount < INT16_MAX) {
        for (size_t ii = 0; ii < nextSteps.size(); ii++)//nextSteps for each source
        {
            for (size_t i = 0; i < nextSteps[ii].size() - 1; i += 2)//next steps are stored like [(r,c),(r,c)]
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
                        return -1;
                    }
                    else if (northVisited == 1 && southVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (southVisited == 1 && northVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (southVisited == 1 && northVisited == 0) {
                        //add north to nextSteps, flow is north
                        int sink = pipeSink(state, nextSteps[ii][i], nextSteps[ii][i + 1], sourceCodes[ii][i]);
                        if (sink == 0) {
                            ++cellCount[ii];
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = nextSteps[ii][i] - 1; //row-1 for north
                            nextSteps[ii][i + 1] = nextSteps[ii][i + 1]; //column
                        }
                        else if (sink == 2) {
                            //finished path

                        }
                    }
                    else if (southVisited == 0 && northVisited == 1) {
                        //add south to nextSteps, flow is south
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i] + 1); //row+1 for south
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                    }
                    else {
                        //no idea, this should be impossible
                        return -3;
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
                        return -1;
                    }
                    else if (westVisited == 1 && eastVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (eastVisited == 1 && westVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (eastVisited == 1 && westVisited == 0) {
                        //add west to nextSteps, flow is west
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i]); //row
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] - 1); //column - 1 for west
                    }
                    else if (eastVisited == 0 && westVisited == 1) {
                        //add east to nextSteps, flow is east
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i]); //row
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] + 1); //column + 1 for east
                    }
                    else {
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
                        return -1;
                    }
                    else if (southVisited == 1 && eastVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (eastVisited == 1 && southVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (eastVisited == 1 && southVisited == 0) {
                        //add south to nextSteps, flow is south
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i] + 1); //row
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                    }
                    else if (eastVisited == 0 && southVisited == 1) {
                        //add east to nextSteps, flow is east
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i]); //row
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] + 1); //column + 1 for east
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
                        return -1;
                    }
                    else if (southVisited == 1 && westVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (westVisited == 1 && southVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (westVisited == 1 && southVisited == 0) {
                        //add south to nextSteps, flow is south
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i] + 1); //row
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                    }
                    else if (westVisited == 0 && southVisited == 1) {
                        //add west to nextSteps, flow is west
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i]); //row
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] - 1); //column + 1 for east
                    }
                    else {
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
                        return -1;
                    }
                    else if (northVisited == 1 && westVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (westVisited == 1 && northVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (westVisited == 1 && northVisited == 0) {
                        //add north to nextSteps, flow is north
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i] - 1); //row-1 for north
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                    }
                    else if (westVisited == 0 && northVisited == 1) {
                        //add west to nextSteps, flow is west
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i]); //row
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] - 1); //column -1
                    }
                    else {
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
                        return -1;
                    }
                    else if (northVisited == 1 && eastVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (eastVisited == 1 && northVisited < 0) {
                        //dead end
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = -4;
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        nextSteps[ii].erase(nextSteps[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        sourcesRC[ii].erase(sourcesRC[ii].begin() + i);
                        i -= 2;
                        return -2;
                    }
                    else if (eastVisited == 1 && northVisited == 0) {
                        //add north to nextSteps, flow is north
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i] - 1); //row-1 for north
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                    }
                    else if (eastVisited == 0 && northVisited == 1) {
                        //add east to nextSteps, flow is east
                        visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] = 4;
                        sourcesRC[ii][i] = nextSteps[ii][i];
                        sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                        nextSteps[ii][i] = (nextSteps[ii][i]); //row
                        nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] + 1); //column -1
                    }
                    else {
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
                            //add north to nextSteps, flow is north
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 1;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i] - 1); //row-1 for north
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
                        }
                        else {
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
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 1;
                            //add south to nextSteps, flow is south
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i] + 1); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1]); //column
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
                            //add west to nextSteps, flow is west
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 2;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i]); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] - 1); //column - 1 for west
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
                            //add east to nextSteps, flow is east
                            visited[nextSteps[ii][i]][nextSteps[ii][i + 1]] += 2;
                            sourcesRC[ii][i] = nextSteps[ii][i];
                            sourcesRC[ii][i + 1] = nextSteps[ii][i + 1];
                            nextSteps[ii][i] = (nextSteps[ii][i]); //row
                            nextSteps[ii][i + 1] = (nextSteps[ii][i + 1] + 1); //column -1
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
    }
    return -7;
}

void getInitialSteps(std::vector<std::vector<int>>& sourcesRC, std::vector<std::vector<int>>& nextSteps, std::vector<std::string>& state, std::vector<std::vector<int>>& visited)
{
    for (size_t i = 0; i < sourcesRC.size(); i++)
    {
        nextSteps.push_back({});
        checkNorth(sourcesRC[i][0], sourcesRC[i][1], state, nextSteps[i], sourcesRC[i]);
        checkEast(sourcesRC[i][0], sourcesRC[i][1], state, nextSteps[i], sourcesRC[i]);
        checkSouth(sourcesRC[i][0], sourcesRC[i][1], state, nextSteps[i], sourcesRC[i]);
        checkWest(sourcesRC[i][0], sourcesRC[i][1], state, nextSteps[i], sourcesRC[i]);
        visited[sourcesRC[i][0]][sourcesRC[i][1]] = 5; //5 = source
    }
}

void getPipeSources(std::vector<std::string>& state, std::vector<std::vector<int>>& sourcesRC, std::vector<std::vector<char>>& sourceCodes, std::vector<int>& cellCount)
{
    for (size_t i = 0; i < state.size(); i++)
    {
        for (size_t ii = 0; ii < state[0].size(); ii++)
        {
            if (pipeStart(state, i, ii)) {
                sourcesRC.push_back({});
                sourceCodes.push_back({}); //source codes do not change
                sourcesRC[sourcesRC.size()-1].push_back(i);
                sourcesRC[sourcesRC.size()-1].push_back(ii);
                sourceCodes[sourceCodes.size() - 1].push_back(state[i][ii]);
                cellCount.push_back(0);
            }
        }
    }
}

int main()
{
    std::vector<std::string>state =
    { "a224C22300000",
        "0001643722B00",
        "0b27275100000",
        "00c7256500000",
        "0006A45000000" };

    if (solution(state) == 19) {
        std::cout << "\n\Success!\n\n";
        return 0;
    }
    std::cout << "\n\nFail!\n\n";
}
