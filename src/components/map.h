#ifndef MAP_H
#define MAP_H


class Map {
public:
    Map();
    Map(int width, int height);
    ~Map();
    int getWidth();
    int getHeight();
    void Print();
private:
    int width;
    int height;
};


#endif //MAP_H
