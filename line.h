#ifndef LINE_H
#define LINE_H
#include "vector3.h"
struct Line
{
private:
	Vector3 begin, end;
	Vector3 orentation;
public:
	Line(const Vector3 &b, const Vector3 &e) :begin(b), end(e), orentation(e - b)
	{

	}
	float distancefrom(const Vector3 &v)const
	{
		return Vector3::crossproduct(end - begin, begin - v).length() / (end - begin).length();
	}
	Line(const Line &l) :begin(l.begin), end(l.end)
	{

	}
	Vector3 getBegin() const
	{
		return begin;
	}
	void setBegin(const Vector3 &value)
	{
		begin = value;
		orentation = end - begin;
	}

	Vector3 getEnd() const
	{
		return end;
	}
	void setEnd(const Vector3 &value)
	{
		end = value;
		orentation = end - begin;
	}
	Vector3 getOrentiation() const
	{
		return orentation;
	}
	/*static bool isperpendicular(const Line &l1,const Line &l2)
	{
	return Vector3::isperpendicular(l1.getOrentiation(),l2.getOrentiation());
	}
	static bool isparallel(const Line &l1,const Line &l2)
	{
	return Vector3::isparallel(l1.getOrentiation(),l2.getOrentiation());
	}
	static Vector3 *intersect(const Line &l1,const Line &l2)
	{

	}*/
};


#endif // LINE_H
