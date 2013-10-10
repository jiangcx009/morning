#ifndef _BILATERAL_LERAN_H_
#define _BILATERAL_LEARN_H_

class Bilateral_Info
{
public:

	Bilateral_Info(int size, float dd, float dc){}
	~Bilateral_Info(){};

private:
	int filter_size; //ÂË²¨´°¿Ú
	float dirta_Dis;
	float dirta_Col;
};
#endif