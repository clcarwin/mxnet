#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "mxnet/c_predict_api.h"

using namespace std;


bool modelinit(const char * path);
void modelclear();
char * modelsymbol(const char * prefix);
char * modeldata(const char * prefix);
int modelsize(const char * prefix);


int main()
{
	if(!modelinit("model"))
	{
		printf("modelinit failed\n");
		return 0;
	}

	char * prefix = "mlp";
	int channels = 1;
	int width = 28;
	int height = 28;
    int image_size = width * height * channels;

    int dev_type = 1;             // 1: cpu, 2: gpu
    int dev_id = 0;               // arbitrary.
    mx_uint num_input_nodes = 1;  // 1 for feedforward
    const char* input_key[1] = {"data"};
    const char** input_keys = input_key;
    const mx_uint input_shape_indptr[2] = {0, 4};
    const mx_uint input_shape_data[4] = {1,(mx_uint)channels,(mx_uint)height,(mx_uint)width};

    if(NULL==modeldata(prefix))
    {
		printf("modeldata failed\n");
		return 0;
    }

    PredictorHandle handle = NULL;
    MXPredCreate((const char*)modelsymbol(prefix),
                (const char*)modeldata(prefix),
                (size_t)modelsize(prefix),
                dev_type,dev_id,num_input_nodes,input_keys,input_shape_indptr,input_shape_data,
                &handle);

    printf("PredictorHandle handle = %d\n",handle);


    std::vector<mx_float> image_data = std::vector<mx_float>(image_size);
    //set image num to 1
    for(int i=0;i<image_size;i++)
    {
    	if(14==i%28) image_data[i] = 255;
    	else image_data[i] = 0;
    }

    MXPredSetInput(handle, "data", image_data.data(), image_size);
    MXPredForward(handle);

    mx_uint output_index = 0;
    mx_uint *shape = 0;
    mx_uint shape_len;
    MXPredGetOutputShape(handle, output_index, &shape, &shape_len);

    size_t output_size = 1;
    for (mx_uint i = 0; i < shape_len; ++i) output_size *= shape[i];
    std::vector<float> data(output_size);
    MXPredGetOutput(handle, output_index, &(data[0]), output_size);

    for(int i=0;i<output_size;i++) printf("%f ",data[i]);
    printf("\n");

	return 0;
}








