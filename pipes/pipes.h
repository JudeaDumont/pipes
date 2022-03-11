int solution(std::vector<std::string> state);

void getInitialSteps(std::vector<std::vector<int>>& sourcesRC, std::vector<std::vector<int>>& nextSteps, std::vector<std::string>& state, std::vector<std::vector<int>>& visited);

void getPipeSources(std::vector<std::string>& state, std::vector<std::vector<int>>& sourcesRC);

void initializeVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited);

bool pipeStart(std::vector<std::string>& state, const size_t& i, const size_t& ii);

std::vector<int> checkWest(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC);

std::vector<int> checkSouth(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC);

std::vector<int> checkEast(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC);

std::vector<int> checkNorth(int frStep, int fcStep, std::vector<std::string>& state, std::vector<int>& nextSteps, std::vector<int>& sourcesRC);

int checkNorthVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep);

int checkSouthVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep);

int checkWestVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep);

int checkEastVisited(std::vector<std::string>& state, std::vector<std::vector<int>>& visited, int frStep, int fcStep);

bool pipeSink(std::vector<std::string>& state, const size_t& i);
