#ifndef PLAYINGFIELD_H_INCLUDED
#define PLAYINGFIELD_H_INCLUDED

#include <vector>

class Field{
private:
    bool visible;
    bool mine;
    bool marked;
    int  content;

public:
    Field(): visible(false), mine(false), marked(false), content(0){}
    ~Field(){}

    const bool isVisible()  const  { return visible; }
    const bool isMine()     const  { return mine; }
    const bool isMarked()   const  { return marked; }
    const int  getContent() const  { return content; }

    void makeMine()             { mine = true; }
    void makeVisible()          { visible = true; }
    void switchMarked()         { marked ? marked = false : marked = true; }
    void setContent(int con)    { content = con; }
};

class PlayingField{
private:
    int piece;
    int mines;
    std::vector< std::vector<Field> > field_vec;

    void mineMaker();
    int  countMarkedFields();
    void statusBar();
    void showDown(int row, int column);

public:
    PlayingField(int  piece);
    ~PlayingField(){};

    int  getMines() { return mines; }

    void newMove(int row, int column, bool& fail_move);
    void newMark(int row, int column);
    int  countValidMoves();

    void nextToMine(int row, int column);
    void zeroSpaces(int row, int column);
    void showFields(bool fail_move = false, int row = 0, int column = 0);
};
#endif // PLAYINGFIELD_H_INCLUDED
