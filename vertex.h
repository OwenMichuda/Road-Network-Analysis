/**
 * @file vertex.h
 * Definition and implementation of a vertex class.
 */

#pragma once

#include <iostream>

class Vertex {
    public:
        Vertex() {}
        Vertex(int idx) : index(idx), x_(-1), y_(-1) {}
        Vertex(int idx, double x, double y) : index(idx), x_(x), y_(y) {}
        Vertex(const Vertex& other) : index(other.index), x_(other.x_), y_(other.y_) {}

        int getIndex() const { return index; }
        int getX() const { return x_; }
        int getY() const { return y_; }
        

        Vertex& operator=(const Vertex& other) {
            this->index = other.index;
            this->x_ = other.x_;
            this->y_ = other.y_;
            return *this;
        }

        bool operator!=(const Vertex& other) const {
            return index != other.index || x_ != other.x_ || y_ != other.y_;
        }

        bool operator==(const Vertex& other) const {
            return !(*this != other);
        }

		bool operator<(const Vertex& other) const {
			return index < other.index;
		}

		friend std::ostream& operator<<(std::ostream& os, const Vertex& obj) {
			os << obj.getIndex();
			return os;
		}

    private:
        int index;
        double x_;
        double y_;
};

template<>
struct std::hash<Vertex> {
	size_t operator()(const Vertex & v) const {
		return std::hash<int>{}(v.getIndex()); 
	}	
};

