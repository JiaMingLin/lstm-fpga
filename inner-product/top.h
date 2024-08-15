#include<ap_int.h>
#include<hls_stream.h>

#define BUS_WIDTH 256
#define IN_DATA_WIDTH 4
#define OUT_DATA_WIDTH IN_DATA_WIDTH*2

typedef ap_int<IN_DATA_WIDTH> in_data_t;
typedef ap_int<OUT_DATA_WIDTH> out_data_t;
typedef ap_uint<BUS_WIDTH> axi_word_t;

typedef struct axi_in_data_bus
{
    axi_word_t data; // 64 elements in 
    bool last;

} axi_in_data_bus;

typedef struct axi_out_data_bus
{
    out_data_t data; // inner product result
    bool last;

} axi_out_data_bus;

typedef hls::stream<axi_in_data_bus> axi_in_data_stream_t;
typedef hls::stream<axi_out_data_bus> axi_out_data_stream_t;

extern "C" void inner_product_top(axi_in_data_stream_t &input, axi_out_data_stream_t &output);
void inner_product(axi_in_data_stream_t &input, axi_out_data_stream_t &output);
