#include <iostream>
#include <vector>

#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#if 0
class A
{
public:
	A(){printf("A init\n");}
	A(const A&){printf("A copy\n");}
	virtual A* clone() const = 0;
	virtual void Fun(){printf("A\n");}
};

A* new_clone(A const& other){
	return other.clone();
}

class B:public A
{
public:
	B(){printf("B init\n");}
	B(const B&){printf("B copy\n");}
	B* clone() const{ return new B(*this); }
	virtual void Fun(){printf("B");}
};

int main(int argc, char* argv[])
{
	boost::ptr_vector<A> ret;
	A* pl= new B;
	ret.push_back(pl);
	ret.at(0).Fun();
	//boost::ptr_vector<A> r2=ret;
	//r2.at(0).Fun();
	printf("\n");
}


class A
{
public:
	A(){ printf("A init\n"); }
	A(const A&){ printf("A copy\n"); }
	virtual ~A(){ printf("A delete\n"); }
	virtual void Fun(){ printf("A\n"); }
};

class B :public A
{
public:
	B(){ printf("B init\n"); }
	B(const B&){ printf("B copy\n"); }
	virtual ~B(){ printf("B delete\n"); }
	virtual void Fun(){ printf("B"); }
};


int main_ptr_vector(int argc, char* argv[])
{
	std::vector< boost::shared_ptr<A> > ret;
	boost::shared_ptr<A> p1(new B);
	ret.push_back(p1);
	ret.at(0)->Fun();
	//std::vector< boost::shared_ptr<A> > r2 = ret;
	//r2.at(0)->Fun();
	printf("\n");
}
#endif