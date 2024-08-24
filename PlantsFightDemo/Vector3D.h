#pragma once
class Vector3D {

public:
    double x, y, z;
    // 构造函数
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
    ~Vector3D() {}
    // 叉乘运算
    Vector3D Cross(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,  // X 坐标
            z * other.x - x * other.z,  // Y 坐标
            x * other.y - y * other.x   // Z 坐标
        );
    }
private:
    
};