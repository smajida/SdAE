#include <iostream>
#include <omp.h>
#include <time.h>

#include <Eigen/Eigen>

#include "Param.h"
#include "DataSet.h"
#include "SdAE.h"

using namespace std;

void init()
{
	srand(time(NULL));
	Eigen::initParallel();
	Eigen::setNbThreads(10);
	#ifdef _OPENMP
		omp_set_num_threads(10);
		omp_set_nested(10);
	#endif
}

void test(Param &param)
{
	DataSet	data("TRAIN");
	data.set("TRAIN");
	data.normalize();

	SdAE		sdae(param);
	sdae.pretrain(data.X,data.Y);
	sdae.finetune(data.X,data.Y);
	
	data.set("TEST");
	data.normalize();

	sdae.test(data.X,data.Y);
}

void test2(Param &param)
{
	if(param.Layer_Size == 0)
		return;
	
	DataSet	data("TRAIN");
	data.set("TRAIN");
	data.normalize();

	dAE dae(param);
	dae.train(data.X,param.Node_Sizes[0]);
	
	dae.dump_param();
	dae.dump_reconstruct(data.X);
	
}

void test3()
{
	uIO::make_directory("test_dir");
}

int main(int argc, char* argv[])
{
	init();
	Param param(argc, argv);
	test2(param);
//	test3();
}

