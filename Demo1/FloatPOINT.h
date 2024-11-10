#include<cmath>
#include<iostream>

using namespace std;
//��������,������������ģ,���������ŵ�����1
#pragma once
struct FloatPOINT {
	float x;
	float y;

	/// <summary>
	/// ���캯��,���еĳ�ʼ�����ڳ�ʼ���б������
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	FloatPOINT(float x = 0.0f, float y = 0.0f) :x(x), y(y) {}

	/// <summary>
	/// ��������ģ
	/// </summary>
	/// <returns></returns>
	float magnitude() const //const���α�ʾ���Խ�FloatPOINT����Ϊconst FloatPOINT֮����ø÷���
	{
		return sqrt(x * x + y * y);
	}

	/// <summary>
	/// ��λ������ֵ,����һ���µı���
	/// </summary>
	/// <returns></returns>
	FloatPOINT normalized() const
	{
		float mag = magnitude();
		return(mag > 0) ? FloatPOINT(x / mag, y / mag) : FloatPOINT(0, 0);
	}

	/// <summary>
	/// ���ص��,������ļн�,����ȷ��һ�������Ƿ�����һ������ķ�����
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	float dot(const FloatPOINT& other) const
	{
		return x * other.x + y * other.y;
	}

	/// <summary>
	/// ���� �ӷ������
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	FloatPOINT operator+(const FloatPOINT& other) const
	{
		return FloatPOINT(x + other.x, y + other.y);
	}

	/// <summary>
	/// ���� ���������
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	FloatPOINT operator-(const FloatPOINT& other) const
	{
		return FloatPOINT(x - other.x, y - other.y);
	}

	/// <summary>
	/// ���� �˷������
	/// </summary>
	/// <param name="scalar"></param>
	/// <returns></returns>
	FloatPOINT operator*(float scalar) const
	{
		return FloatPOINT(x * scalar, y * scalar);
	}

	/// <summary>
	/// ���� ���������
	/// </summary>
	/// <param name="scalar"></param>
	/// <returns></returns>
	FloatPOINT operator/(float scalar) const
	{
		return (scalar != 0) ? FloatPOINT(x / scalar, y / scalar) : FloatPOINT(0, 0);
	}

	/// <summary>
	/// ���� +=
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	FloatPOINT& operator+=(const FloatPOINT& other)
	{
		x += other.x;
		y += other.y;
		return *this;//��������,����ֵΪ�������Ϳ���֧����ʽ����,����˵:a+=b+=c
	}
	FloatPOINT& operator-=(const FloatPOINT& other)
	{
		x -= other.x;
		y -= other.y;
		return *this;
	}
	FloatPOINT& operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}
	FloatPOINT& operator/=(float scalar)
	{
		if (scalar != 0) {
			x *= scalar;
			y *= scalar;
		}
		return *this;
	}

	/// <summary>
	/// ������������֮��ľ���
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	static float distance(const FloatPOINT& a, const FloatPOINT& b)//ʹ��static�������Ǹ���̬��Ա����,���Բ�����ʵ��������,����Ϊ�������ͱ��ⲻ��Ҫ�Ŀ���
	{
		return (a - b).magnitude();
	}

	/// <summary>
	/// ���Բ�ֵ,������������֮��ƽ�����ȵĳ���
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	static FloatPOINT lerp(const FloatPOINT& a, const FloatPOINT& b, float t)//t=0��ʾ����a,t=1��ʾ����b,��0~1֮���ʾ����a~b֮���һ����
	{
		/*
			b-a ��ʾ�õ�������֮��ľ���ͷ���
			(b-a)*t ��ʾ����a~b֮���һ����,����t��ֵ����
			a+(b-a)*t ��ʾ���õ����µ�ӵ�a��,Ҳ����a����b�ƶ�һ�ξ���,������t������
		*/
		return a + (b - a) * t;
	}
};
