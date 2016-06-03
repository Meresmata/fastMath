#include <fstream>
#include <iomanip>
#include <cstdint>
#include <climits>
#include <cmath>


int main()
{
	const double PI = 3.141592653589793238462643383279502884197169399375105820974;
	
	std::ofstream cosX_file("cosX.txt");
	
	if(cosX_file.is_open()){
		for(int i = 0; i <= 90; ++i){
			if(i!=90)
				cosX_file << std::setw(6)<<std::fixed <<std::setprecision (0)<<cos(i*PI/180)*UINT16_MAX << ",";
			else
				cosX_file << std::setw(6)<<std::fixed <<std::setprecision (0) << cos(i*PI/180)*UINT16_MAX;
			if(!(i%5))
				cosX_file <<std::endl;
		}
	}
	cosX_file.close();
	return 0;
}

