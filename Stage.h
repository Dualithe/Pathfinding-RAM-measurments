#include <vector>
#include <string>

class Stage
{
    public:

        // constructor and destructor
        Stage(int size);
        ~Stage();
        Stage();
        Stage(int** board);

        int** getBoard();
        int getSize();
        void displayBoard();
        void setBoard(int** value);
        void displayPath();

        void saveCurrentMap();
        void loadMap(int mapNum);
        bool fileExists(std::string filename);


    private:
        int size;

        int** board;
        int** generateBoard();

};

