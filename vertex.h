/**
 * @file vertex.h
 * Definition and implementation of a vertex class.
 */

#pragma once

class Vertex {
    public:
        Vertex() {}
        Vertex(int idx, double x, double y) : index(idx), x_(x), y_(y) {}
        Vertex(Vertex& other) : index(other.index), x_(other.x_), y_(other.y_) {}
        
        bool operator!=(Vertex& other) const {
            return index != other.index || x_ != other.x_ || y_ != other.y_;
        }
    private:
        int index;
        double x_;
        double y_;
};
