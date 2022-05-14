#include <vector>
class Stage
{
    public:

        // constructor and destructor
        Stage(std::vector<int> *obstacles, int size);
        ~Stage();

        std::vector<int> getObstacles();


    private:
        int size;
        void generate();
        std::vector<int> *obstacles;

};