/*************************************************************************
   @ File Name: similarity.hpp
   @ Method: 
   @ Author: Jerry Shi
   @ Mail  : jerryshi0110@gmail.com 
   @ Created Time: 2015年08月16日 星期日 14时38分56秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class similarity
{
	public:
		similarity();
		~similarity();

		float PointDistance(vector<float>& P,vector<float>& Q,int p);
		int editDistance(const std::string& sstr,const std::string& tstr);
		bool isEnglish(const std::string& sstr);
};

similarity::similarity()
{
}

similarity::~similarity()
{
}

//@param sstr: source string
bool similarity::isEnglish(const std::string& sstr)
{
	const char* pos = sstr.c_str();
	bool ret = true;
	for(std::size_t i = 0; i < sstr.size(); ++i,++pos)
	{
		if(isblank(*pos) || isalpha(*pos))
			continue;
		else
		{
			ret = false;
			break;
		}
	}
	return ret;
}

// Minkowski distance 
// is no related with data distribution
// Formula: (sum((Xi - Yi)^p))^(1/p)
// Description: p = 2,thet is Euclidean istance
//				p = 1,that is Manhattan distance
//				p -> infinity,that is Chebyshev distance,formula: max|Xi - Yi|
// Note: if amplitude is bigger in x/y coordinate,now you need z-transform, 
//
// @param P: point p coordinate vector
// @param Q: ppint q coordinate vector
// @param p: decide which distance will you want to use
float similarity::PointDistance(vector<float>& P, vector<float>& Q, int p)
{
	if(P.size() != Q.size() || p < 0)
		return -1;
	float sum = 0.0;
	
   for(std::size_t i = 0; i < P.size(); ++i)
   {
	   float XY_Minus = (float)abs(P[i] - Q[i]);
	   float XY_square = 1;
	   for(int j = 0;j < p; ++j)
			XY_square *= XY_Minus;
	   sum += XY_square;
   }

   if(2 == p)
   {
	   std::cout << "Euclidean Distance: ";
	   return (float)sqrt(sum);
   }
   else if(1 == p)
   {
	   std::cout << "Manhattan Distance: ";
	   return sum;
   }
   else
   {
	   std::cout << "Minkowski Distance: ";
	   return (float)pow(sum,p);
   }
}

// @param sstr: source string
// @param tstr: target string
int similarity::editDistance(const std::string& sstr,const std::string& tstr)
{
	int n = sstr.length();
	int m = sstr.length();

	if(0 == n) return m;
	if(0 == m) return n;

	typedef std::vector<std::vector<int> > Tmatrix;

	Tmatrix matrix(n+1);

	//initial the matrix (n+1)*(m+1)
	for(int i = 0; i <= n; ++i) matrix[i].resize(m+1);
	
	//initial elements in matrix
	for(int i = 0; i <= n; ++i) matrix[i][0] = i;
	for(int i = 0; i <= m; ++i) matrix[0][i] = i;

	//caculate
	for(int i = 1; i <= n; ++i)
	{
		const char si = sstr[i-1];
		int cost; //penalty
		for(int j = 1; j <= m ; ++j)
		{
			const char sj = tstr[i-1];
			if(si == sj)
			{
				cost = 0;
			}
			else
			{
				cost = 1;
			}

			const int above = matrix[i-1][j] +1; //above (i,j),(i-1,j)
			const int left = matrix[i][j-1] + 1; //left (i,j),(i,j-1)
			const int diag = matrix[i-1][j-1] + cost;
			matrix[i][j] = std::min(above,std::min(left,diag));
		}
	}

	if(isEnglish(sstr) && isEnglish(tstr))
		return matrix[n][m];
	else
		return matrix[n][m] / 3; // return if string contain chinese
}
