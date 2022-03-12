int solution(std::vector<std::string> state);

void finishPath(std::vector<int>& finishedSteps, int& ii, std::vector<int>& cellCount, std::vector<std::vector<int>>& sourcesRC, std::vector<std::vector<int>>& nextSteps);

void getInitialSteps(std::vector<std::vector<int>>& sourcesRC, std::vector<std::vector<int>>& nextSteps, std::vector<std::string>& state, std::vector<std::vector<int>>& visited);

void getPipeSources(std::vector<std::string>& state, std::vector<std::vector<int>>& sourcesRC, std::vector<char>& sourceCodes, std::vector<int>& cellCount, std::vector<int>& finishedSteps, std::vector<int>& leakedSteps, std::vector<int>& cycledSteps);

void initializeVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited);

bool pipeStart(std::vector<std::string>& state, const int& i, const int& ii);

std::vector<int> checkWest(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC);

std::vector<int> checkSouth(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC);

std::vector<int> checkEast(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC);

std::vector<int> checkNorth(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC);

int checkNorthVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep);

int checkSouthVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep);

int checkWestVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep);

int checkEastVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep);

int pipeSink(std::vector<std::string>& state, const int& i, const int& ii, const char& source);

