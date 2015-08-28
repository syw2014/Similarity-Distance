/*************************************************************************
   @ File Name: t_similarity.cpp
   @ Method: 
   @ Author: Jerry Shi
   @ Mail: jerryshi0110@gmail.com 
   @ Created Time: 2015年08月16日 星期日 16时04分45秒
 ************************************************************************/

#include <iostream>
#include "../src/similarity.hpp"

int main(int argc ,char* argv[])
{
	std::string s1 = "abcd";
	std::string s2 = "accd";

	similarity m_sim;

	int ret = m_sim.editDistance(s1,s2);
	std::cout << "ret:" << ret <<std::endl;

	vector<float> v1;
	vector<float> v2;
	v1.push_back(2);
	v1.push_back(2);
	v2.push_back(4);
	v2.push_back(4);

	cout << m_sim.PointDistance(v1,v2,1);
	cout << m_sim.PointDistance(v1,v2,2);

	return 0;

}
