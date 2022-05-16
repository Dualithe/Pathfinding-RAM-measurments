#include <vector>

class Stage
{
    public:

        // constructor and destructor
        Stage(int size);
        ~Stage();

        Stage(int** board);

        int** getBoard();
        void displayBoard();
        void setBoard(int** value);

    private:
        int size;

        int** board;
        int** generateBoard();

};

