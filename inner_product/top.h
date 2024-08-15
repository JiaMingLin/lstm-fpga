#include<ap_int.h>
#include<hls_stream.h>

#define INPUT_SIZE 20
#define HIDDEN_SIZE 64

#define WGT_DATA_WIDTH 4
#define INPUT_DATA_WIDTH 8
#define ACCUMULATION_DATA_WIDTH 16

#define WGT_DATA_VEC_WIDTH (WGT_DATA_WIDTH * HIDDEN_SIZE)
#define INPUT_DATA_VEC_WIDTH (INPUT_DATA_WIDTH * INPUT_SIZE)
#define HIDDEN_DATA_VEC_WIDTH (INPUT_DATA_WIDTH * HIDDEN_SIZE)

typedef ap_int<WGT_DATA_WIDTH> wgt_data_t;
typedef ap_int<INPUT_DATA_WIDTH> input_data_t;
typedef ap_int<ACCUMULATION_DATA_WIDTH> accumulation_data_t;

typedef ap_uint<INPUT_DATA_VEC_WIDTH> input_data_vec_t;
typedef ap_uint<HIDDEN_DATA_VEC_WIDTH> hidden_data_vec_t;
typedef ap_uint<WGT_DATA_VEC_WIDTH> wgt_data_vec_t;

template<typename DATA_TYPE>
struct act_data_vec_bus
{
    DATA_TYPE data; 
    bool last;

};

struct accumulation_data_bus
{
    accumulation_data_t data; // inner product result
    bool last;

};

typedef hls::stream<act_data_vec_bus<input_data_vec_t>> axi_input_data_stream_t;
typedef hls::stream<act_data_vec_bus<hidden_data_vec_t>> axi_hidden_data_stream_t;
typedef hls::stream<accumulation_data_bus> axi_acc_data_stream_t;

extern "C" void inner_product_top(axi_hidden_data_stream_t &hidden_input_stream, axi_acc_data_stream_t &acc_stream);
void inner_product(axi_hidden_data_stream_t &hidden_input_stream, wgt_data_vec_t wgt_vec, axi_acc_data_stream_t &acc_stream);
