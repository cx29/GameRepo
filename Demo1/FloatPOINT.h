#include<cmath>
#include<iostream>

using namespace std;
//向量基类,求两个向量的模,将向量缩放到长度1
#pragma once
struct FloatPOINT {
	float x;
	float y;

	/// <summary>
	/// 构造函数,所有的初始化都在初始化列表中完成
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	FloatPOINT(float x = 0.0f, float y = 0.0f) :x(x), y(y) {}

	/// <summary>
	/// 求向量的模
	/// </summary>
	/// <returns></returns>
	float magnitude() const //const修饰表示可以将FloatPOINT申明为const FloatPOINT之后调用该方法
	{
		return sqrt(x * x + y * y);
	}

	/// <summary>
	/// 求单位向量的值,返回一个新的变量
	/// </summary>
	/// <returns></returns>
	FloatPOINT normalized() const
	{
		float mag = magnitude();
		return(mag > 0) ? FloatPOINT(x / mag, y / mag) : FloatPOINT(0, 0);
	}

	/// <summary>
	/// 返回点积,向量间的夹角,可以确认一个物体是否在另一个物体的方向上
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	float dot(const FloatPOINT& other) const
	{
		return x * other.x + y * other.y;
	}

	/// <summary>
	/// 重载 加法运算符
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	FloatPOINT operator+(const FloatPOINT& other) const
	{
		return FloatPOINT(x + other.x, y + other.y);
	}

	/// <summary>
	/// 重载 减法运算符
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	FloatPOINT operator-(const FloatPOINT& other) const
	{
		return FloatPOINT(x - other.x, y - other.y);
	}

	/// <summary>
	/// 重载 乘法运算符
	/// </summary>
	/// <param name="scalar"></param>
	/// <returns></returns>
	FloatPOINT operator*(float scalar) const
	{
		return FloatPOINT(x * scalar, y * scalar);
	}

	/// <summary>
	/// 重载 除法运算符
	/// </summary>
	/// <param name="scalar"></param>
	/// <returns></returns>
	FloatPOINT operator/(float scalar) const
	{
		return (scalar != 0) ? FloatPOINT(x / scalar, y / scalar) : FloatPOINT(0, 0);
	}

	/// <summary>
	/// 重载 +=
	/// </summary>
	/// <param name="other"></param>
	/// <returns></returns>
	FloatPOINT& operator+=(const FloatPOINT& other)
	{
		x += other.x;
		y += other.y;
		return *this;//返回引用,返回值为引用类型可以支持链式调用,比如说:a+=b+=c
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
	/// 计算两个向量之间的距离
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	static float distance(const FloatPOINT& a, const FloatPOINT& b)//使用static代表这是个静态成员函数,可以不依赖实例来调用,参数为引用类型避免不必要的拷贝
	{
		return (a - b).magnitude();
	}

	/// <summary>
	/// 线性插值,常用于两个点之间平滑过度的场景
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <param name="t"></param>
	/// <returns></returns>
	static FloatPOINT lerp(const FloatPOINT& a, const FloatPOINT& b, float t)//t=0表示返回a,t=1表示返回b,在0~1之间表示返回a~b之间的一个点
	{
		/*
			b-a 表示得到两个点之间的距离和方向
			(b-a)*t 表示计算a~b之间的一个点,根据t的值来定
			a+(b-a)*t 表示将得到的新点加到a上,也就是a朝着b移动一段距离,距离由t来决定
		*/
		return a + (b - a) * t;
	}
};
