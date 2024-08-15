#include "top.h"

extern "C" void inner_product_top(axi_hidden_data_stream_t &hidden_input_stream, axi_acc_data_stream_t &acc_stream){
    #pragma HLS INTERFACE mode=axis port=hidden_input_stream
    #pragma HLS INTERFACE mode=axis port=acc_stream
    #pragma HLS INTERFACE ap_ctrl_none port=return
    #pragma HLS DATAFLOW

    static wgt_data_vec_t wgt_vec;

    inner_product(hidden_input_stream, wgt_vec, acc_stream);
}


void inner_product(axi_hidden_data_stream_t &hidden_input_stream, wgt_data_vec_t wgt_vec, axi_acc_data_stream_t &acc_stream){
    #pragma HLS PIPELINE II=1 style=flp

    hidden_data_vec_t hidden_data_vec;
    accumulation_data_t accumulation_data = 0;
    accumulation_data_bus acc_data_bus;

    if(!hidden_input_stream.empty()){
        act_data_vec_bus<hidden_data_vec_t> hidden_data_bus = hidden_input_stream.read();
        hidden_data_vec = hidden_data_bus.data;
        for(int i = 0; i < HIDDEN_SIZE; i++){
            #pragma HLS UNROLL
            accumulation_data += wgt_vec.range((i+1)*WGT_DATA_WIDTH-1, i*WGT_DATA_WIDTH) * 
                                 hidden_data_vec.range((i+1)*INPUT_DATA_WIDTH-1, i*INPUT_DATA_WIDTH);
        }
        acc_data_bus.data = accumulation_data;
        acc_data_bus.last = hidden_data_bus.last;
        acc_stream.write(acc_data_bus);
    }
    
    return;
}