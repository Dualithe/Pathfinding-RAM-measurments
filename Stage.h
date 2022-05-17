#include <vector>

class Stage
{
    public:

        // constructor and destructor
        Stage(int size);
        ~Stage();

        Stage(int** board);

        int** getBoard();
        int getSize();
        void displayBoard();
        void setBoard(int** value);
        void displayPath();

    private:
        int size;

        int** board;
        int** generateBoard();

};

