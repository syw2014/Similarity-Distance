/*************************************************************************
   @ File Name: similarity.hpp
   @ Method: 
   @ Author: Jerry Shi
   @ Mail: jerryshi0110@gmail.com 
   @ Created Time: 2015年08月16日 星期日 14时38分56秒
 ************************************************************************/

#include <iostream>
#include <vector>
#include <string>

class similarity
{
	public:
		similarity();
		~similarity();

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
//
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
		return matrix[n][m] / 3; //
}
