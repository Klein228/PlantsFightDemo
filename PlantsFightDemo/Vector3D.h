#pragma once
class Vector3D {

public:
    double x, y, z;
    // ���캯��
    Vector3D(double x, double y, double z) : x(x), y(y), z(z) {}
    ~Vector3D() {}
    // �������
    Vector3D Cross(const Vector3D& other) const {
        return Vector3D(
            y * other.z - z * other.y,  // X ����
            z * other.x - x * other.z,  // Y ����
            x * other.y - y * other.x   // Z ����
        );
    }
private:
    
};