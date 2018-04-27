#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>
#include <cfloat>

class Point{
public:
    Point() {}

    Point(double x, double y) : x(x), y(y) {}

    Point operator /(const double scalar){
        return Point(x / scalar,y / scalar);
    }
    Point operator +(const Point point_){
        return Point(x + point_.x,y + point_.y);
    }
    Point operator -(const Point point_){
        return Point(x - point_.x,y - point_.y);
    }
    Point operator *(const int scalar){
        return Point(x * scalar , y * scalar);
    }
    static double distance(Point point1,Point point2){
        return std::sqrt(std::pow( (point1.x - point2.x),2 ) + std::pow( (point1.y - point2.y),2 ));
    }
    //也就是向量的长度的平方
    double norm(){
        return   std::pow(x,2) + std::pow(y,2) ;
    }
    double x,y;
};
struct Node{
    Node* parent;    //父节点，只有一个
    std::vector<Node*> child;    //子节点，可以有很多
    Point position; //当前节点的位置
};
const int step_size = 10;
const int max_iterations = 1000;
const int width = 40;
const int height = 40;
const Point start_pos(10.0,10.0);
const Point end_pos(15.0,15.0);
//在多大距离内可以判定为达到终点
const double tolerance = 1.50;
std::vector<Node*> nodes;
std::vector<Node*> path;
Node* getRandomNode(){
    srand((unsigned)time( NULL));
    Node* ret = new Node;
    Point position(rand() % width,rand() % height);
    ret->position = position;
    return ret;
}
Node* getNearest(const Point& point){
    double min_distance = DBL_MAX;
    Node* closest = new Node;
    for (int i = 0; i < nodes.size(); ++i) {
        double distance = Point::distance(point,nodes[i]->position);
        if (distance < min_distance){
            min_distance = distance;
            closest = nodes[i];
        }
    }
    return closest;
}
//意思就是把nodes表中的距离随机点最近的那个点向随机点的方向走一步
Point conf(const Node* node,Node* nearest){
    Point from = nearest->position;
    Point to = node->position;
    Point medium = to - from;
    //向量归一化，产生方向和单位长度
    medium = medium / (medium.norm());

    return from + medium * step_size;
}
int main() {
    //初始化
    Node* root = new Node;
    Node* last_node;
    root->parent = NULL;
    root->position = start_pos;
    last_node = root;
    nodes.push_back(root);


    //开始
    for (int i = 0; i < max_iterations; ++i) {
        //在地图内生成一个随机点，并计算整个Nodes表中距离随机点最近的点nearest，注意这个nearest是在我们的nodes表中的
        Node* random_node = getRandomNode();
        Node* nearest = getNearest(random_node->position);
        if (Point::distance(nearest->position,random_node->position) > step_size){
            Point new_point = conf(random_node,nearest);
            Node* new_node = new Node;
            new_node->position = new_point;

            new_node->parent = nearest;
            nearest->child.push_back(new_node);
            nodes.push_back(new_node);
            last_node = new_node;
        }
        if (Point::distance(last_node->position,end_pos) < tolerance){
            printf("goal reached\n");
            break;
        }
    }
    //已经达到了最大迭代数
    Node* n;
    if (Point::distance(last_node->position,end_pos) < tolerance){
        n = last_node;
    }
    else {
        n = getNearest(end_pos);
        printf("out of iterations\n");
    }

    while(n != NULL){
        path.push_back(n);
        n = n->parent;
    }
    printf("start = (%lf,%lf),end = (%lf,%lf)\n",start_pos.x,start_pos.y,end_pos.x,end_pos.y);
    for (int j = 0; j < path.size(); ++j) {
        printf("(%lf,%lf)\n",path[j]->position.x,path[j]->position.y);
    }
    std::cout << "Hello, World!" << std::endl;
    return 0;
}