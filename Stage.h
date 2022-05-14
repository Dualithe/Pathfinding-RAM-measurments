#include <vector>

class Stage
{
    public:

        // constructor and destructor
        Stage(int size);
        ~Stage();

        int** getBoard();
        void displayBoard();


    private:
<<<<<<< HEAD
        int size; 
        int generate(size);
        //std::vector<int> *obstacles;
=======
        int size;

        int** board;
        int** generateBoard();
>>>>>>> 29e8605 (Generate board)

};