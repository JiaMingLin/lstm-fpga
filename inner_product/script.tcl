open_project hls_prj
add_files top.cpp
add_files top.h
# add_files -tb ./src/tb.cpp
open_solution -reset -flow_target vitis "inn_prod"
set_part {xcu50-fsvh2104-2-e}
create_clock -period 3.33 -name default
set_top inner_product_top
# csim_design
csynth_design
# cosim_design
# export_design -rtl verilog -format xo -output mm2s.xo
exit